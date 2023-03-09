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

#include "rbc.h"
#include "check.h"


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
    printf("Serveur a l'ecoute\n");


    /*----Creation du thread d'envoi-----*/

    // sem_init(&semEnvoiDispo, 0, 0);
    // sem_init(&semBuffResourceLib, 0, 0);

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
        printf ("> Thread created: %d\n", index-1);

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
    char *buffer;
    int errorHandler;
    int trainID;

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

    /* Start to read regular messages */
    /* Capture the header */


}

void ThreadTraiterBufferRequetes()
{

}


void ThreadEnvoyerMessages()
{

}
