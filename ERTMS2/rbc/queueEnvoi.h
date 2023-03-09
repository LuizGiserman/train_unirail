#ifndef QUEUE_ENVOI_H
#define QUEUE_ENVOI_H

#include <stdio.h>
#include <stdlib.h>
#include "../check.h"

typedef struct 
{
    int trainID;
    int socket;
    int quantity;
    int *resources;
    void *next;

} nodeEnvoi;




nodeEnvoi *Envoi_CreateNodeDemande(int trainID, int socket, int quantity, int *resources);
void Envoi_AddElement(nodeEnvoi ** first, nodeEnvoi *element);
nodeEnvoi *Envoi_PopElement(nodeEnvoi **first);

#endif