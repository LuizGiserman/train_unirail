#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "evc.h"
#include "../../Libs_Unirail/CAN/canLinux.h"
// #include "../../Libs_Unirail/CAN/MESCAN1_ID&DLC_INFRA.h"

nodeDemande path[10];

/* Exemple de demande sur une balise */

// path[0].quantityDem = 2;
// path[0].resourcesDem = (int *) malloc(sizeof(int) * path[0].quantityDem);
// path[0].resourcesDem[0] = 2;
// path[0].resourcesDem[0] = GetAiguillage(2);

// path[0].quantityLib = 2;
// path[0].resourcesLib = (int *) malloc(sizeof(int) * path[0].quantityLib);
// path[0].resourcesLib[0] = 2;
// path[0].resourcesLib[0] = GetAiguillage(2);

/* Fin d'example */


canton 	currentCanton;
canton 	lastCantonAuthorised;
int 	currentBalise;


pthread_mutex_t mutexBalise;

sem_t semDemandeRes;

int main()
{
	/* Înit semaphores */
	sem_init(&semDemandeRes, 0, 1);


	ThreadTraiterBalise(NULL);

}

void ThreadTraiterBalise(void* arg) {

	uCAN1_MSG 	recCanMsg;
	int 		canPort;
	char 		*NomPort = "can0";

	struct can_filter rfilter; 
	
	// Get balise
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

void ThreadDemandeResources()
{
	static int currentIndex = 0;

	char 	*messageLib;
	char 	*messageDem;
	int 	messageSize;
	int		socket;
	int 	errorHandler;

	/* Connection to server */
	socket = EstablishConnection();

	for(;;)
	{
		sem_wait(&semDemandeRes);
		
		messageSize = CreateMessageLib(path[currentIndex], messageLib);
		if (messageSize > 0)
		{
			errorHandler = send(socket, messageLib, messageSize, 0);
			CHECK_NOT_LT(errorHandler, 0, "Erreur send");
		}

		messageSize = CreateMessageDem(path[currentIndex], messageDem);
		if (messageSize > 0)
		{
			errorHandler = send(socket, messageDem, messageSize, 0);
			CHECK_NOT_LT(errorHandler, 0, "Erreur send");
		}

		currentIndex++;
	}
}

int CreateMessageLib(nodeDemande demande, char *result)
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

	return messageSize;
}

int CreateMessageLib(nodeDemande demande, char *result)
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
