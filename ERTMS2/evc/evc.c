#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <stdarg.h>
#include <time.h>

#include "../check.h"
#include "evc.h"
#include "../../Libs_Unirail/CAN/canLinux.h"
#include "controlleur/CONTROLADOR.h"
#include "odometrie.h"

// #include "../../Libs_Unirail/CAN/MESCAN1_ID&DLC_INFRA.h"

nodeDemande path[PATH_SIZE] = {

	/* Demander aiguillages avant. Derniere Canton a la fin */
	[0] = { 
			2, (int[2]) {AIGUILLAGE + 2, 2}, 	/* Demander */
			0, NULL, 						 	/* Liberer */
		  },

	[1] = { 
			3, (int[3]) {AIGUILLAGE + 2, 2, 3}, /* Demander */
			2, (int[2]) {AIGUILLAGE + 2, 2}, 	/* Liberer */
		  }
};

cantonDistance pathCanton[CANTON_PATH_SIZE] = 
{
	C1, C2, C3, C12, C13, C7, C8, C9
};

int vitesseConsigne[CANTON_PATH_SIZE] = 
{
	25, 25, 25, 25, 25, 25, 25, 25
};
/* Fin d'example */

pthread_mutex_t writeScreen;

pthread_mutex_t statusTrain;
TrainInfo trainData;


cantonDistance 	currentCanton;
cantonDistance 	lastCantonAuthorised;
int 			currentBalise;
int				currentCantonIndex;

pthread_mutex_t mutexBalise;
pthread_mutex_t mutexLastAuthorised;
pthread_mutex_t mutexCurrentCanton;

sem_t semDemandeRes;
sem_t semEcouteRep;

pthread_t threadTraiterBalise;
pthread_t threadDemandeResources;
pthread_t threadEcouterResources;
pthread_t threadUpdateUContol;
pthread_t threadOdometrie;

int main()
{
	int errorHandler;
	/* Init semaphores */
	sem_init(&semDemandeRes, 0, 1);
	sem_init(&semEcouteRep, 0, 0);

	pthread_mutex_lock(&statusTrain);
	InitializeTrainInfo(&trainData);
	pthread_mutex_unlock(&statusTrain);

	pthread_mutex_lock(&mutexCurrentCanton);
	currentCantonIndex = 0;
	currentCanton = pathCanton[currentCantonIndex];
	pthread_mutex_unlock(&mutexCurrentCanton);

    errorHandler = pthread_create(&threadTraiterBalise, NULL, (pf_t) ThreadTraiterBalise, (void *) NULL);
    PTHREAD_CHECK(errorHandler, "Erreur pthread_create");

    errorHandler = pthread_create(&threadDemandeResources, NULL, (pf_t) ThreadDemandeResources, (void *) NULL);
    PTHREAD_CHECK(errorHandler, "Erreur pthread_create");

	errorHandler = pthread_create(&threadUpdateUContol, NULL, (pf_t) ThreadUpdateUControl, (void *) NULL);
    PTHREAD_CHECK(errorHandler, "Erreur pthread_create");

	errorHandler = pthread_create(&threadOdometrie, NULL, (pf_t) ThreadOdometrie, (void *) NULL);
    PTHREAD_CHECK(errorHandler, "Erreur pthread_create");


	pthread_join(threadTraiterBalise, NULL);
	pthread_join(threadDemandeResources, NULL);
	pthread_join(threadUpdateUContol, NULL);
	pthread_join(threadOdometrie, NULL);

	return OK;
}


void ThreadUpdateUControl(void *arg)
{

	static boolean_T OverrunFlag = false;
	CONTROLADOR_initialize();
  
	for (;;)
	{
		/* Faut faire sleep pour 17 ms */
		pthread_mutex_lock(&mutexCurrentCanton);
		pthread_mutex_lock(&mutexLastAuthorised);
		pthread_mutex_lock(&statusTrain);

		if (currentCantonIndex >= CANTON_PATH_SIZE)
		{
			break;
		}
  		
		/* Check for overrun */
		if (OverrunFlag) {
			rtmSetErrorStatus(CONTROLADOR_M, "Overrun");
			return;
		}

  		OverrunFlag = true;

		CONTROLADOR_U.Posiction_actuelle 	= (real_T) trainData.distance;
		CONTROLADOR_U.Posiciton_souhaite 	= (real_T) lastCantonAuthorised;
		CONTROLADOR_U.Vitesse_Reele 		= (real_T) trainData.vit_mesuree;
		CONTROLADOR_U.Vitesse_Consigne 		= (real_T) vitesseConsigne[currentCantonIndex];

		pthread_mutex_unlock(&mutexCurrentCanton);
		pthread_mutex_unlock(&mutexLastAuthorised);
		pthread_mutex_unlock(&statusTrain);
		
		CONTROLADOR_step();

		OverrunFlag = false;

		Display(NAME_CONTROLLEUR, "Vitesse consigne à envoyer: %f", (float) CONTROLADOR_Y.Vitesse_Envoyer);
		WriteVitesseLimite((float) CONTROLADOR_Y.Vitesse_Envoyer);

	}

	CONTROLADOR_terminate();
}

void ThreadTraiterBalise(void* arg) {

	uCAN1_MSG 	recCanMsg;
	int 		canPort;
	char 		*NomPort = "can0";

	struct can_filter rfilter; 

	/* Filter for balise */	
	rfilter.can_mask = CAN_SFF_MASK;
	rfilter.can_id   = MC_ID_EBTL2_RECEIVED;

    /* Start CAN bus connexion */
    canPort = canLinux_init_prio(NomPort);
	canLinux_initFilter(&rfilter, sizeof(rfilter));

    usleep(80000); //80ms
    
    for(;;)
    {
		if(canLinux_receive(&recCanMsg, 1))
		{
			pthread_mutex_lock(&mutexBalise);
			currentBalise = (int) recCanMsg.frame.data5;
			pthread_mutex_unlock(&mutexBalise);

			Display (NAME_TRAITER_BALISE, "Passé sur la balise %d\n", currentBalise);
			
			pthread_mutex_lock(&mutexCurrentCanton);
			currentCantonIndex++;
			currentCanton = pathCanton[currentCantonIndex];
			pthread_mutex_unlock(&mutexCurrentCanton);

			sem_post(&semDemandeRes);
		}
    	usleep(8000); //Sampling period ~= 17ms
	}
	// if exit stop train
	// WriteVitesseConsigne(0, 1);

    close(canPort);
	Display(NAME_TRAITER_BALISE, "EXIT CAN reading\n");
}

void ThreadDemandeResources(void *args)
{
	static int currentIndex = 0;

	char 	*messageLib;
	char 	*messageDem;
	int 	messageSize;
	int		socket;
	int 	errorHandler;

	/* Connection to server */
	socket = EstablishConnection();

	errorHandler = pthread_create(&threadEcouterResources, NULL, (pf_t) ThreadEcouterResources, (void *) &socket);
    PTHREAD_CHECK(errorHandler, "Erreur pthread_create");


	while(currentIndex < PATH_SIZE)
	{
		sem_wait(&semDemandeRes);
		
		messageSize = CreateMessageLib(path[currentIndex], &messageLib);
		if (messageSize > 0)
		{
			errorHandler = send(socket, messageLib, messageSize, 0);
			CHECK_NOT_LT(errorHandler, 0, "Erreur send");
		}

		messageSize = CreateMessageDem(path[currentIndex], &messageDem);
		if (messageSize > 0)
		{
			errorHandler = send(socket, messageDem, messageSize, 0);
			CHECK_NOT_LT(errorHandler, 0, "Erreur send");
			sem_post(&semEcouteRep);
			Display (NAME_DEMANDER_RESOURCE, "Message Envoyé\n");
		}

		currentIndex++;
	}

	pthread_join(threadEcouterResources, NULL);

}

void ThreadEcouterResources(void * args)
{
	int socket =  (int) *((int *) args);


	char 	*buffer;
	int 	errorHandler;
	int 	leftToRead;

	for(;;)
	{
		sem_wait(&semEcouteRep);
		/* Receive header */
		buffer = (char *) malloc(HEADER_SIZE-1);
		CHECK_NOT(buffer, NULL, "Erreur Malloc");

		do
		{
			errorHandler = recv(socket, buffer, HEADER_SIZE-1, MSG_PEEK);
		} while (errorHandler < HEADER_SIZE-1);
		errorHandler = recv(socket, buffer, HEADER_SIZE-1, 0);
		CHECK_NOT_LT(errorHandler, 0, "Erreur recv");

		leftToRead = buffer[1];

		free(buffer);
		buffer = (char *) malloc(leftToRead);
		CHECK_NOT(buffer, NULL, "Erreur Malloc");

		do
		{
			errorHandler = recv(socket, buffer, leftToRead, MSG_PEEK);
		} while (errorHandler < leftToRead);
		errorHandler = recv(socket, buffer, leftToRead, 0);
		CHECK_NOT_LT(errorHandler, 0, "Erreur recv");

		pthread_mutex_lock(&mutexLastAuthorised);
		lastCantonAuthorised = (cantonDistance) intToCantonDistance(buffer[leftToRead -1]);
		Display (NAME_ECOUTER_RESPONSE, "Permission granted. Last canton authorised: %d\n", buffer[leftToRead -1]);
		pthread_mutex_unlock(&mutexLastAuthorised);
		
		free(buffer);
	}
}


void ThreadOdometrie(void *arg)
{
	uCAN1_MSG 			recCanMsg;
	struct can_filter 	rfilter;
	int 				canPort;
	char 				*NomPort = "can0";

	rfilter.can_id   = MC_ID_SCHEDULEUR_MESURES;
	rfilter.can_mask = CAN_SFF_MASK;
	
	canPort = canLinux_init_prio(NomPort);
	canLinux_initFilter(&rfilter, sizeof(rfilter));

	for(;;)
	{
		if(canLinux_receive(&recCanMsg, 1)) 
		{
			pthread_mutex_lock(&statusTrain);

			TraitementDonnee(&recCanMsg, &trainData); 
			Display(NAME_ODOMETRIE, "Distance: %f, Speed %f", trainData.distance, trainData.vit_mesuree);

			pthread_mutex_unlock(&statusTrain);
		}
	}
	
}

int CreateMessageLib(nodeDemande demande, char **result)
{
	char	*buffer;
	int		messageSize;

	if(demande.quantityLib == 0)
	{
		return 0;
	}

	messageSize = demande.quantityLib + HEADER_SIZE + 1;
	buffer = (char *) malloc(messageSize);
	CHECK_NOT(buffer, NULL, "Erreur Malloc");
	
	buffer[0] = TRAIN_ID;
	buffer[1] = (purpose) PURPOSE_LIBERER_RESOURCE;
	buffer[2] = demande.quantityLib + 1;
	buffer[3] = demande.quantityLib;
	for (int i = 0; i < demande.quantityLib; i++)
	{
		buffer[4+i] = demande.resourcesLib[i];
	}

	*result = buffer;
	return messageSize;
}

int CreateMessageDem(nodeDemande demande, char **result)
{
	char	*buffer;
	int		messageSize;

	if(demande.quantityDem == 0)
	{
		return 0;
	}

	messageSize = demande.quantityDem + HEADER_SIZE + 1;
	buffer = (char *) malloc(messageSize);
	CHECK_NOT(buffer, NULL, "Erreur Malloc");
	
	buffer[0] = TRAIN_ID;
	buffer[1] = (purpose) PURPOSE_DEMANDE_RESOURCE;
	buffer[2] = demande.quantityDem + 1;
	buffer[3] = demande.quantityDem;
	for (int i = 0; i < demande.quantityDem; i++)
	{
		buffer[4+i] = demande.resourcesDem[i];
	}

	*result = buffer;
	return messageSize;
}

aiguillage GetAiguillage(int num)
{
	return (aiguillage) num + 29;
}

int EstablishConnection()
{

    struct sockaddr_in addrServ;

    int 	sd1;
    int 	adrlg;
	int		errorHandler;

	char 	*buffer;

    adrlg = sizeof(struct sockaddr_in);

    //Etape 1 - Creation de la socket
    sd1=socket(AF_INET, SOCK_STREAM, 0);
    CHECK_NOT(sd1,-1, "Creation fail !!!\n");

    //Etape2 - Adressage du destinataire
    addrServ.sin_family=AF_INET;
    addrServ.sin_port=htons(SERVER_PORT);
    addrServ.sin_addr.s_addr=inet_addr(SERVER_IP);

    //Etape 3 - demande d'ouverture de connexion
    CHECK_NOT(connect(sd1, (const struct sockaddr *)&addrServ, adrlg),-1, "Connexion fail !!!\n");
    Display (NAME_DEMANDER_RESOURCE, "socket connect\n");
    
	/* Send handshake */
	buffer = (char*) malloc(HANDSHAKE_SIZE);
	CHECK_NOT(buffer, NULL, "Erreur Malloc");

	buffer[0] = TRAIN_ID;

	errorHandler = send(sd1, buffer, HANDSHAKE_SIZE, 0);
    CHECK_NOT_LT(errorHandler, 0, "Erreur send");

    return sd1;

}

void printMessage(char *msg, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf ("%02hhX|", msg[i]);
    }
    printf("\n");
}


cantonDistance intToCantonDistance(int ca)
{
	// 1, 2, 3, 12, 13, 7, 8, 9
	cantonDistance result;
	switch(ca)
	{
		case 1:
			result = C1;
			break;
		case 2:
			result = C2;
			break;
		case 3:
			result = C3;
			break;
		case 12:
			result = C12;
			break;
		case 13:
			result = C13;
			break;
		case 7:
			result = C7;
			break;
		case 8:
			result = C8;
			break;
		case 9:
			result = C9;
			break;
	}
	return result;
}

void InitializeTrainInfo( TrainInfo *train)
{
	train->distance 		= 0;
	train->vit_consigne		= 0;
	train->vit_mesuree 		= 0;
	train->nb_impulsions	= 0;
}

void Display(const char *name, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	struct timespec now;

	clock_gettime(CLOCK_REALTIME, &now);

	pthread_mutex_lock(&writeScreen);
	printf("[%ld.%ld]", now.tv_sec, now.tv_nsec);
	printf("%s: ", name);
	vprintf(format, args);
	pthread_mutex_unlock(&writeScreen);

	va_end(args);
}
