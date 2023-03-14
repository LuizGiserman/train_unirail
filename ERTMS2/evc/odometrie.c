#include "odometrie.h"
#include "../../Libs_Unirail/CAN/loco_Parametres.h"
#include "../../Libs_Unirail/CAN/MESCAN1_VarTrain.h"

unsigned char status, varDebug1, varDebug2;
int WriteVitesseLimite(float vitesseLimite)
{

	uCAN1_MSG consigneUrgence;
	
	if(vitesseLimite > MAX_CONSIGNE_VITESSE_AUTORISEE) //vitesse supérieur à 50 cm/s
	vitesseLimite = MAX_CONSIGNE_VITESSE_AUTORISEE;                   
	
	consigneUrgence.frame.id  = MC_ID_CONSIGNE_VITESSE_LIMITE;
	consigneUrgence.frame.dlc = MC_DLC_CONSIGNE_VITESSE_LIMITE;
	MESCAN_SetData8(&consigneUrgence, cdmc_consigneVitesseLimite, vitesseLimite);
	
	return 	canLinux_transmit(CANLINUX_PRIORITY_HIGH, &consigneUrgence);
}

int WriteVitesseConsigne(unsigned int vitesse, unsigned char sense)
{
	
	uCAN1_MSG consigneVitesse;

	if(vitesse>MAX_CONSIGNE_VITESSE_AUTORISEE) //vitesse supérieur à 50 cm/s
		vitesse = MAX_CONSIGNE_VITESSE_AUTORISEE;
	
	consigneVitesse.frame.id  = MC_ID_CONSIGNE_VITESSE;
	consigneVitesse.frame.dlc = MC_DLC_CONSIGNE_VITESSE;
	MESCAN_SetData8(&consigneVitesse, cdmc_consigneVitesse, vitesse);
	MESCAN_SetBit(&consigneVitesse, bdmc_sensDeplacementLoco, sense);
	
	return 	canLinux_transmit(CANLINUX_PRIORITY_HIGH, &consigneVitesse);
}

int  WriteTrameStatusRUNRP1(unsigned char status, unsigned char varDebug1, unsigned char varDebug2)
{
	uCAN1_MSG trameStatusRP1;
	trameStatusRP1.frame.id  = MC_ID_RP1_STATUS_RUN;
	trameStatusRP1.frame.dlc = MC_DLC_RP1_STATUS_RUN;
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_erreurs, 0);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_warnings, 0);
	MESCAN_SetBit(&trameStatusRP1, bdmc_RP1_etatConnexionWIFI, 1);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_configONBOARD, status);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_var1Debug, varDebug1);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_var2Debug, varDebug2);
	
	return 	canLinux_transmit(CANLINUX_PRIORITY_MEDIUM, &trameStatusRP1);
}


void TraitementDonnee (uCAN1_MSG *recCanMsg,  TrainInfo *infos)
{
	
		
    if (recCanMsg->frame.id==MC_ID_SCHEDULEUR_MESURES)
    {
		/** Envoi la vitesse instantannée (consigne vitesse) ,	le nombre dimpulsions, la vitesse mesurée, lerreur du PID **/

		if(MESCAN_GetData8(recCanMsg, cdmc_ordonnancementId)==MC_ID_RP1_STATUS_RUN)
			WriteTrameStatusRUNRP1(status, varDebug1, varDebug2);
			
        infos-> vit_mesuree= (int)MESCAN_GetData8(recCanMsg, cdmc_vitesseMesuree);/** le nbre d'implusion envoyé ici
		// est le nombre d'impulsion entre 2 mesures **/
		infos-> nb_impulsions+= infos-> vit_mesuree;
        infos-> distance= PAS_ROUE_CODEUSE * (infos->nb_impulsions);
		infos-> vit_consigne= (float)MESCAN_GetData8(recCanMsg, cdmc_vitesseConsigneInterne);
		printf("Actualisation: Postition courante : %lf cm, Vit: %d cm/s\n", infos-> distance, infos-> vit_mesuree);
	}
	else 
		printf("La trame lue a pour ID %X \n",recCanMsg->frame.id);
}