#include <stdio.h>
#include <stdlib.h>
#include "queueBusyResource.h"


void Resource_CreateAddAllNodeResources(nodeBusyResource **first, int quantity, int *resources)
{
  int i;
  nodeBusyResource *aux;
  for(i = 0; i < quantity; i++)
  {
    aux = Resource_CreateNodeResource(resources[i]);
    Resource_AddElement(first, aux);
  }

}
nodeBusyResource *Resource_CreateNodeResource(int resource)
{
  nodeBusyResource *new;
  new = (nodeBusyResource*) malloc(sizeof(nodeBusyResource));
  CHECK_NOT(new, 0, "Erreur Malloc");

  new->resource = resource;
  new->next     = NULL;

  return new;
}

void Resource_AddElement(nodeBusyResource ** first, nodeBusyResource *element)
{
   nodeBusyResource *aux;
    if (*first == NULL)
    {
      *first = element;
      return;
    }

    aux = *first;
    while (aux->next != NULL)
    {
      aux = aux->next;
    }

    aux->next = element;
}

nodeBusyResource *Resource_PopElement(nodeBusyResource **first)
{
    nodeBusyResource *element;

    element = *first;
    *first  = ((nodeBusyResource*) element)->next;
    
    return element;
}

bool Resource_CheckAllNotInList(nodeBusyResource *first, nodeDemande node)
{
  bool CheckElementInList(int quantity, int *resources, int resource);
  
  
  nodeBusyResource *aux = first;
  while (aux != NULL)
  {
    if (CheckElementInList(node.quantity, node.resources, aux->resource) == TRUE)
    {
      return FALSE;
    }
    aux = aux->next;
  }

  return TRUE;

}
bool CheckElementInList(int quantity, int *resources, int resource)
{
  for (int i = 0; i < quantity; i++)
  {
    if (resources[i] == resource)
    {
      return TRUE;
    }
  }
  return FALSE;
}

bool FindResourceInList(nodeBusyResource **first, int resource)
{

  nodeBusyResource *aux = *first;
  while(aux != NULL)
  {
    if (aux->resource == resource)
    {
      return TRUE;
    }

    aux = aux->next;
  }

  return FALSE;

}

bool Resource_RemoveResourceFromList(nodeBusyResource **first, int resource)
{
  nodeBusyResource *before, *current;
  current = *first;
  
  if (*first == NULL)
  {
    return FALSE;
  }

  if (current->resource == resource)
  {
    *first = current->next;
    free(current);
    return TRUE;
  }
  
  before = current;
  current = current->next;
  while(current != NULL)
  {
    if (current->resource == resource)
    {
      before->next = current->next;
      free(current);
      return TRUE;
    }

    before = current;
    current = current->next;
  }

  return FALSE;
}

bool Resource_RemoveResourcesOfListFromDemande(nodeBusyResource **first, nodeDemande demande)
{

  bool result;
  for (int i = 0; i < demande.quantity; i++)
  {
    result = Resource_RemoveResourceFromList(first, demande.resources[i]);
    if (result == FALSE)
    {
      return FALSE;
    }
  }
  return TRUE;
}

bool Resource_RemoveResourcesOfListFromRes(nodeBusyResource **first, int quantity, int *resources)
{
  bool result;
  for (int i = 0; i < quantity; i++)
  {
    result = Resource_RemoveResourceFromList(first, resources[i]);
    if (result == FALSE)
    {
      return FALSE;
    }
  }
  return TRUE;
}