#ifndef QUEUE_RESOURCE_H
#define QUEUE_RESOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include "queueDemande.h"
#include "../check.h"
typedef struct 
{
    int resource;
    void *next;

} nodeBusyResource;




void Resource_CreateAddAllNodeResources(nodeBusyResource **first, int quantity, int *resources);
nodeBusyResource *Resource_CreateNodeResource(int resource);
void Resource_AddElement(nodeBusyResource ** first, nodeBusyResource *element);

nodeBusyResource *Resource_PopElement(nodeBusyResource **first);

bool Resource_CheckAllNotInList(nodeBusyResource *first, nodeDemande node);
bool FindResourceInList(nodeBusyResource **first, int resource);

bool Resource_RemoveResourceFromList(nodeBusyResource **first, int resource);
bool Resource_RemoveResourcesOfListFromDemande(nodeBusyResource **first, nodeDemande demande);
bool Resource_RemoveResourcesOfListFromRes(nodeBusyResource **first, int quantity, int *resources);


#endif