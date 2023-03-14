#ifndef ODOMETRIE_H
#define ODOMETRIE_H

#include "../../Libs_Unirail/CAN/canLinux.h"

typedef struct TrainInfo
{
	float distance;  // en cm
	float vit_consigne;
	int vit_mesuree;
	int nb_impulsions;
}TrainInfo;

int WriteVitesseLimite(float vitesseLimite);
int WriteVitesseConsigne(unsigned int vitesse, unsigned char sense);
int WriteTrameStatusRUNRP1(unsigned char status, unsigned char varDebug1, unsigned char varDebug2);
void TraitementDonnee (uCAN1_MSG *recCanMsg, TrainInfo *infos);


#endif