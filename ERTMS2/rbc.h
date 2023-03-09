#ifndef RBC_H  
#define RBC_H


#define MAX_CONNECTIONS     4
#define HANDSHAKE_SIZE      1
#define LOCAL_PORT          3005
#define OK                  0


typedef struct {

    int newsock;
    int connIndex;

} arg_rbc_struct;

typedef void * (*pf_t)(void *);

void ThreadEcouterMessages(void * args);
void ThreadTraiterBufferRequetes();
void ThreadEnvoyerMessages();

#endif