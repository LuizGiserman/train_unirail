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
#define NUM_RESOURECS       20

#define OK                  0


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

#endif