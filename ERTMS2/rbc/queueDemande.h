#ifndef QUEUE_DEMANDE_H
#define QUEUE_DEMANDE_H

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

} nodeDemande;


nodeDemande *Demande_CreateNodeDemande(int trainID, int socket, int quantity, int *resources);
void Demande_AddElement(nodeDemande ** first, nodeDemande *element);
nodeDemande *Demande_PopElement(nodeDemande **first);
int RemoveWhereResourceEquals(nodeDemande **first, int resource, nodeDemande **retrieved);
void Demande_removeDemande(nodeDemande **first, nodeDemande demande);
bool Demande_CompareDemandes(nodeDemande a, nodeDemande b);

#endif