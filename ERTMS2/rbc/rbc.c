#include <stdio.h>
#include <pthread.h>
#include <sys/select.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdarg.h>

#include "rbc.h"
#include "../check.h"
#include "queueDemande.h"
#include "queueEnvoi.h"
#include "queueBusyResource.h"


pthread_mutex_t     mutexResources[NUM_RESOURECS];
pthread_mutex_t     mutexBuffer;
pthread_mutex_t     mutexEnvoi;
pthread_mutex_t     mutexBusyRes;

pthread_mutex_t     writeScreen;

sem_t   semEnvoiAvailable;
sem_t   semBufferWake;


nodeDemande         *listDemande;
nodeEnvoi           *listEnvoi;
nodeBusyResource    *listBusyResource;

int main ()
{
    int                         serverSocket, newClientSocket;
    struct sockaddr_in          serverAddr;
    struct sockaddr_storage     clientAddr;
    socklen_t                   clientAddrLen;
    pthread_t                   threadEcouteID[MAX_CONNECTIONS];
    pthread_t                   threadEnvoi;
    pthread_t                   threadBuffer;
    int                         errorHolder;
    int                         index = 0; 

    arg_rbc_struct              *args;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family       = AF_INET;
    serverAddr.sin_port         = htons(LOCAL_PORT);
    serverAddr.sin_addr.s_addr  = INADDR_ANY;
    
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero)); /* Pourquoi pas? */

    errorHolder = bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    CHECK_NOT(errorHolder, -1, "Erreur bind");

    errorHolder = listen(serverSocket, MAX_CONNECTIONS);
    CHECK_NOT(errorHolder, -1, "Erreur listen");
    Display(NAME_MAIN, "Serveur a l'ecoute\n");


    /* Initializing semaphores */
    sem_init(&semEnvoiAvailable, 0, 0);
    sem_init(&semBufferWake, 0, 0);

    /*----Creation du thread d'envoi-----*/

    errorHolder = pthread_create(&threadEnvoi, NULL, (pf_t) ThreadEnvoyerMessages, (void *) NULL);
    PTHREAD_CHECK(errorHolder, "Erreur pthread_create");

    /*------------------------------------*/

    /*--Creation du thread de traitement du buffer--*/

    errorHolder = pthread_create(&threadBuffer, NULL, (pf_t) ThreadTraiterBufferRequetes, NULL);
    PTHREAD_CHECK(errorHolder, "Erreur pthread_create");

    /*------------------------------------*/
    for (;;)
    {
        clientAddrLen   = sizeof(clientAddr);

        newClientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &clientAddrLen);

        /* Params pour la fonction du thread */
        args = (arg_rbc_struct*) malloc(sizeof(arg_rbc_struct));
        CHECK_NOT(args, 0, "Erreur Malloc");

        args->newsock   = newClientSocket;
        args->connIndex = index;

        errorHolder = pthread_create(&threadEcouteID[index++], NULL, (pf_t) ThreadEcouterMessages, (void *) args);
        PTHREAD_CHECK(errorHolder, "Erreur pthread_create");
        Display (NAME_MAIN, "Thread created: %d\n", index-1);

        if (index == MAX_CONNECTIONS)
        {
            for (index = 0; index < MAX_CONNECTIONS; index++)
            {
                pthread_join(threadEcouteID[index], NULL);
            }
        }

    }

    return OK;

}

void ThreadEcouterMessages(void * args)
{
    arg_rbc_struct *ecouterArgs = (arg_rbc_struct*) args;

    char        *buffer;            /* To receive all incoming bytes */
    int         errorHandler;
    bool        boolEval;
    int         trainID; 
    int         bytesLeft;          /* To store how many bytes are left to read */
    int         *resources;         /* To store all of the resources concerning the request */
    int         quantityResources;  /* To store the quantity of resources incoming in the request */
    purpose     currentPurpose;


    nodeDemande         *newDemande;        /* Struct to encapsulate and bufferize the request */
    nodeEnvoi           *newEnvoi;          /* Struct to encapsulate the request so it can be sent */ 

    buffer = (char*) malloc(HANDSHAKE_SIZE);
    CHECK_NOT(buffer, 0, "Erreur Malloc");

    /* Receive the handshake which contains the trainID of the client*/
    do
    {
        errorHandler = recv(ecouterArgs->newsock, buffer, HANDSHAKE_SIZE, MSG_PEEK);
    } while (errorHandler < HANDSHAKE_SIZE);
    errorHandler = recv(ecouterArgs->newsock, buffer, HANDSHAKE_SIZE, 0);
    CHECK_NOT_LT(errorHandler, 0, "Erreur recv");

    /* Saving the train ID */
    trainID = buffer[0];
    free(buffer);

    /* Start to read regular messages */
    /* Capture the header */
    buffer = (char*) malloc(HEADER_SIZE);
    CHECK_NOT(buffer, 0, "Erreur Malloc");
    do
    {
        errorHandler = recv(ecouterArgs->newsock, buffer, HEADER_SIZE, MSG_PEEK);
    } while (errorHandler < HEADER_SIZE);
    errorHandler = recv(ecouterArgs->newsock, buffer, HEADER_SIZE, 0);
    CHECK_NOT_LT(errorHandler, 0, "Erreur recv");

    /* Capture the purpose of the message */
    currentPurpose = (purpose) buffer[1];
    bytesLeft = (int) buffer[2];
    free(buffer);

    /* Reading the rest of the message */
    buffer = (char*) malloc(bytesLeft);
    CHECK_NOT(buffer, 0, "Erreur Malloc");
    do
    {
        errorHandler = recv(ecouterArgs->newsock, buffer, bytesLeft, MSG_PEEK);
    } while (errorHandler < bytesLeft);
    errorHandler = recv(ecouterArgs->newsock, buffer, bytesLeft, 0);
    CHECK_NOT_LT(errorHandler, 0, "Erreur recv");

    quantityResources = (int) buffer[0];

    resources = (int *) malloc(sizeof(int) * quantityResources);
    CHECK_NOT(resources, 0, "Erreur Malloc");

    for (int i = 0; i < quantityResources; i++)
    {
        resources[i] = buffer[i+1];
    }

    switch (currentPurpose)
    {
        case PURPOSE_LIBERER_RESOURCE:
            /* Unlock resources, remove them from busy list, wake up buffer */
            UnlockResources(quantityResources, resources);

            pthread_mutex_lock(&mutexBusyRes);
            Resource_RemoveResourcesOfListFromRes(&listBusyResource, quantityResources, resources);
            pthread_mutex_unlock(&mutexBusyRes);

            sem_post(&semBufferWake);

            break;
        
        case PURPOSE_DEMANDE_RESOURCE:

               boolEval = TrylockResources(quantityResources, resources);

               if (boolEval == TRUE)
               {

                /* Add resources to the list of busy resources */
                pthread_mutex_lock(&mutexBusyRes);
                Resource_CreateAddAllNodeResources(&listBusyResource, quantityResources, resources);
                pthread_mutex_unlock(&mutexBusyRes);
                
                /* Encapsulate the request and awaken the send thread */
                newEnvoi = Envoi_CreateNodeDemande(trainID, ecouterArgs->newsock, 
                                          quantityResources, resources);
                pthread_mutex_lock(&mutexEnvoi);
                Envoi_AddElement(&listEnvoi, newEnvoi);
                pthread_mutex_unlock(&mutexEnvoi);
                
                sem_post(&semEnvoiAvailable);

               }
               else
               {
                /* Bufferize the request */
                newDemande = Demande_CreateNodeDemande(trainID, ecouterArgs->newsock, 
                                          quantityResources, resources);

                pthread_mutex_lock(&mutexBuffer);
                Demande_AddElement(&listDemande, newDemande);
                pthread_mutex_unlock(&mutexBuffer);

               }
            break;    
        
        default:
            break;
    }



}

/* 
    Tries to lock all of the requested mutex
    If any mutex is not acquired, release the others
    Returns: TRUE if all acquired; ELSE otherwise 
*/
bool TrylockResources(int quantity, int *resources)
{
    int     *statusMutex;
    int     i, j;

    statusMutex = (int *) malloc(sizeof(int) * quantity);
    CHECK_NOT(statusMutex, 0, "Erreur Malloc");

    for (j = 0; j < quantity; j++)
    {
        statusMutex[j] = pthread_mutex_trylock(&mutexResources[resources[j]]);
        if (statusMutex[j] != 0)
        {
            for (i = 0; i < j; i++)
            {
                if (statusMutex[i] == 0)
                {
                    pthread_mutex_unlock(&mutexResources[resources[i]]);
                }
            }
            return FALSE;
        }
    }
    return TRUE;

}

void UnlockResources(int quantity, int *resources)
{
    int i;
    for (i = 0; i < quantity; i++)
    {
        pthread_mutex_unlock(&mutexResources[resources[i]]); 
    }
}

void ThreadTraiterBufferRequetes()
{
    bool found;

    nodeDemande         *aux;
    nodeEnvoi           *newEnvoi;
    nodeBusyResource    *newResource;

    for(;;)
    {

        /* Semaphore */
        sem_wait(&semBufferWake);

        /* Iterer sur la liste de demandes et voir si les resources requises sont dans le buffRes */
        found = FALSE;

        aux = listDemande;
        pthread_mutex_lock(&mutexBuffer);
	
        while(aux != NULL)
        {
            
            pthread_mutex_lock(&mutexBusyRes);
            found = Resource_CheckAllNotInList(listBusyResource, *aux);
            pthread_mutex_unlock(&mutexBusyRes);

            if (found == TRUE)
            {
                break;
            }

            aux = aux->next;

        }
        if (found == TRUE)
        {            

            
            pthread_mutex_lock(&mutexBusyRes);
            for (int i = 0; i < aux->quantity; i++)
            {
                pthread_mutex_lock(&mutexResources[aux->resources[i]]);
                newResource = Resource_CreateNodeResource(aux->resources[i]);
                Resource_AddElement(&listBusyResource, newResource);
            }
            pthread_mutex_unlock(&mutexBusyRes);

            /* Je cree ça avant d'effacer aux */
            newEnvoi = Envoi_CreateNodeDemande(aux->trainID, aux->socket, aux->quantity, aux->resources);

            Demande_removeDemande(&listDemande, *aux);
            pthread_mutex_unlock(&mutexBuffer);
            
            /*  Je peux envoyer la message au client.
            * Je le met dans le buffer de la thread qui l'envoi */
            /* Efface la demande du buffer */
        
            pthread_mutex_lock(&mutexEnvoi);
            Envoi_AddElement(&listEnvoi, newEnvoi);
            pthread_mutex_unlock(&mutexEnvoi);

            /* Notification de qu'il y a une nouvelle demande a envoyer */
            sem_post(&semEnvoiAvailable);

        }
        else
        {
            pthread_mutex_unlock(&mutexBuffer);
        }

    }

}


void ThreadEnvoyerMessages()
{
    nodeEnvoi   *newEnvoi;
    char        *buffer;
    int         errorHandler;
    int         messageSize;
    
    for (;;)
    {
        sem_wait(&semEnvoiAvailable);

        pthread_mutex_lock(&mutexEnvoi);
        newEnvoi = Envoi_PopElement(&listEnvoi);
        pthread_mutex_unlock(&mutexEnvoi);


        messageSize = newEnvoi->quantity + HEADER_SIZE;
        buffer = (char *) malloc(messageSize);

        buffer[0] = newEnvoi->trainID;
        buffer[1] = newEnvoi->quantity + 1;
        buffer[2] = newEnvoi->quantity;
        for (int i = 0; i < newEnvoi->quantity; i++)
        {
            buffer[3 + i] = newEnvoi->resources[i];
        }

        errorHandler = send(newEnvoi->socket, buffer, messageSize, 0);
        CHECK_NOT_LT(errorHandler, 0, "Erreur send");

        free(newEnvoi);
        free(buffer);
    }

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
