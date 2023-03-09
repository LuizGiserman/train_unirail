#include <stdio.h>
#include <stdlib.h>
#include "queueDemande.h"

nodeDemande *Demande_CreateNodeDemande(int trainID, int socket, int quantity, int *resources)
{
  nodeDemande *new;
  new = (nodeDemande*) malloc(sizeof(nodeDemande));
  CHECK_NOT(new, 0, "Erreur Malloc");
 
  new->trainID = trainID;
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

void Demande_AddElement(nodeDemande ** first, nodeDemande *element)
{
    nodeDemande *aux;
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

nodeDemande *Demande_PopElement(nodeDemande **first)
{
    nodeDemande *element;
    element = *first;
    *first  = ((nodeDemande*) element)->next;
    return element;
}

int RemoveWhereResourceEquals(nodeDemande **first, int resource, nodeDemande **retrieved)
{

  nodeDemande *aux, *before;

  if (*first == NULL)
  {
    return 0;
  }


  aux = *first;

  /* Case it is the first one */
  if (aux->quantity == 1)
  {
    if(aux->resources[0] == resource)
    {
      *retrieved = aux;
      *first     = aux->next;
      return 1;
    }
  }

  /* Else, look for it in the rest of the list */
  before = aux;
  aux = aux->next;

  while(aux != NULL)
  {
    if (aux->quantity != 1)
    {
      before  = aux;
      aux     = aux->next;
      continue;
    }

    if (aux->resources[0] == resource)
    {
      before->next  = aux->next;
      *retrieved    = aux;
      return 1;
    }

    aux = aux->next;
  }

  return 0;

}

void Demande_removeDemande(nodeDemande **first, nodeDemande demande)
{
  bool        isIt;
  nodeDemande *before, *aux;

  aux = *first;
  if (Demande_CompareDemandes(*aux, demande) == TRUE)
  {
    *first = aux->next;
    free(*first);
    return;
  }

  before = aux;
  aux = aux->next;

  while (aux != NULL)
  {
    isIt = Demande_CompareDemandes(*aux, demande);
    if (isIt == TRUE)
    {
      before->next = aux->next;
      free(aux);
      return;
    }
    before = aux;
    aux = aux->next;
  }

}

bool Demande_CompareDemandes(nodeDemande a, nodeDemande b)
{
  if (a.next == b.next)
  {
    return TRUE;
  }
  return FALSE;
}
