#ifndef EVC_H
#define EVC_H

#include "../check.h"

#define HEADER_SIZE     3
#define TRAIN_ID        0

#define SERVER_PORT     3005
#define SERVER_IP       "127.0.0.1"

#define HANDSHAKE_SIZE  1

typedef int canton; /* 1-29 */
typedef int aiguillage; /* 30-47 */

typedef struct 
{
    int quantityDem;
    int *resourcesDem;
    int quantityLib;
    int *resourcesLib;

} nodeDemande;

typedef enum {
    PURPOSE_DEMANDE_RESOURCE,
    PURPOSE_LIBERER_RESOURCE
} purpose;

void ThreadTraiterBalise(void* arg);
char *CreateMessageGR();
void ThreadDemandeResources();
int CreateMessageLib(nodeDemande demande, char *result);
aiguillage GetAiguillage(int num);

#endif