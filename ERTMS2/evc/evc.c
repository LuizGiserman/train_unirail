#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "evc.h"
#include "../../Libs_Unirail/CAN/canLinux.h"
// #include "../../Libs_Unirail/CAN/MESCAN1_ID&DLC_INFRA.h"

nodeDemande path[PATH_SIZE] = {

	/* Demander aiguillages avant. Derniere Canton a la fin */
	[0] = { 
			2, (int[2]) {AIGUILLAGE + 2, 2}, /* Demander */
			2, (int[2]) {AIGUILLAGE + 2, 2}, /* Liberer */
		  }
};


/* Fin d'example */


canton 	currentCanton;
canton 	lastCantonAuthorised;
int 	currentBalise;

pthread_mutex_t mutexBalise;
pthread_mutex_t mutexLastAuthorised;

sem_t semDemandeRes;
sem_t semEcouteRep;

pthread_t threadTraiterBalise;
pthread_t threadDemandeResources;
pthread_t threadEcouterResources;

int main()
{
	int errorHandler;
	/* Init semaphores */
	sem_init(&semDemandeRes, 0, 1);
	sem_init(&semEcouteRep, 0, 0);


    errorHandler = pthread_create(&threadTraiterBalise, NULL, (pf_t) ThreadTraiterBalise, (void *) NULL);
    PTHREAD_CHECK(errorHandler, "Erreur pthread_create");

    errorHandler = pthread_create(&threadDemandeResources, NULL, (pf_t) ThreadDemandeResources, (void *) NULL);
    PTHREAD_CHECK(errorHandler, "Erreur pthread_create");

	pthread_join(threadTraiterBalise, NULL);
	pthread_join(threadDemandeResources, NULL);

	return OK;
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

			sem_post(&semDemandeRes);
		}
    	usleep(8000); //Sampling period ~= 17ms
	}
	// if exit stop train
	// WriteVitesseConsigne(0, 1);

    close(canPort);
	printf("EXIT CAN reading\n");
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
		}

		currentIndex++;
	}
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
		lastCantonAuthorised = (canton) buffer[leftToRead -1];
		pthread_mutex_unlock(&mutexLastAuthorised);
		
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
    printf ("socket connect\n");
    
	/* Send handshake */
	buffer = (char*) malloc(HANDSHAKE_SIZE);
	CHECK_NOT(buffer, NULL, "Erreur Malloc");

	buffer[0] = TRAIN_ID;

	errorHandler = send(sd1, buffer, HANDSHAKE_SIZE, 0);
    CHECK_NOT_LT(errorHandler, 0, "Erreur send");

    return sd1;

}

