#ifndef EVC_H
#define EVC_H

#include "odometrie.h"
#include "../check.h"

#define GET_AIGUILLAGE(val) \
	return val+29;

#define HEADER_SIZE         3
#define TRAIN_ID            0

#define SERVER_PORT         3005
#define SERVER_IP           "192.168.1.41"

#define HANDSHAKE_SIZE      1

#define AIGUILLAGE	        29

#define OK                  0

#define PATH_SIZE           2
#define CANTON_PATH_SIZE    8

#define NAME_TRAITER_BALISE     "TraiterBalise"
#define NAME_ECOUTER_RESPONSE   "EcouterReponse"
#define NAME_DEMANDER_RESOURCE  "DemanderResource"
#define NAME_ODOMETRIE          "Odometrie"
#define NAME_CONTROLLEUR        "Controlleur"

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

typedef void * (*pf_t)(void *);

	// 1, 2, 3, 12, 13, 7, 8, 9
typedef enum
{
    C1,
    C2,
    C3,
    C12,
    C13,
    C7,
    C8,
    C9
} cantonDistance;

extern TrainInfo trainData;

void ThreadTraiterBalise(void* arg);
void ThreadUpdateUControl(void *arg);
void ThreadDemandeResources(void *arg);
void ThreadEcouterResources(void *args);
void ThreadOdometrie(void *arg);

int EstablishConnection();
int CreateMessageDem(nodeDemande demande, char **result);
int CreateMessageLib(nodeDemande demande, char **result);

aiguillage GetAiguillage(int num);
void printMessage(char *msg, int size);
cantonDistance intToCantonDistance(int ca);
void InitializeTrainInfo( TrainInfo *train);
void Display(const char * name, const char *format, ...);

#endif