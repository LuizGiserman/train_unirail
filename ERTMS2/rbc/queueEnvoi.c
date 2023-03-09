#include <stdio.h>
#include <stdlib.h>
#include "queueEnvoi.h"

nodeEnvoi *Envoi_CreateNodeDemande(int trainID, int socket, int quantity, int *resources)
{
  nodeEnvoi *new;

  new = (nodeEnvoi*) malloc(sizeof(nodeEnvoi));
  CHECK_NOT(new, 0, "Erreur Malloc");
  
  new->trainID  = trainID;
  new->socket   = socket;
  new->quantity = quantity;

  new->resources = (int*) malloc(sizeof(int)*quantity);
  CHECK_NOT(new->resources, 0, "Erreur Malloc");

  for (int i = 0; i < quantity; i++)
  {
    new->resources[i] = resources[i];
  }

  return new;
}

void Envoi_AddElement(nodeEnvoi ** first, nodeEnvoi *element)
{
    nodeEnvoi *aux;
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

nodeEnvoi *Envoi_PopElement(nodeEnvoi **first)
{
    nodeEnvoi *element;

    element = *first;
    *first  = ((nodeEnvoi*) element)->next;
    
    return element;
}