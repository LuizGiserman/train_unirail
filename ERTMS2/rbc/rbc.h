#ifndef RBC_H  
#define RBC_H

#include "../check.h"

/* Server MACROS */
#define MAX_CONNECTIONS     4
#define LOCAL_PORT          3005

/* Message MACROS */
#define HANDSHAKE_SIZE      1
#define HEADER_SIZE         3

/* Resources MACROS */
#define NUM_RESOURECS       47 + 1

#define OK                  0

#define NAME_ENVOYER_MESSAGES   "EnvoyerMessages"
#define NAME_ECOUTER_MESSAGES   "EcouterMessages"
#define NAME_MAIN               "Main"
#define NAME_TRAITER_BUFFER     "TraiterBuffer"


typedef struct {

    int newsock;
    int connIndex;

} arg_rbc_struct;

typedef enum {
    PURPOSE_DEMANDE_RESOURCE,
    PURPOSE_LIBERER_RESOURCE
} purpose;

typedef void * (*pf_t)(void *);

bool TrylockResources(int quantity, int *resources);
void ThreadEcouterMessages(void * args);
void ThreadTraiterBufferRequetes();
void ThreadEnvoyerMessages();
void UnlockResources(int quantity, int *resources);

void Display(const char *name, const char *format, ...);
#endif