/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_Enum_ID_DLC.h

  @Summary:
    This is the MESCAN1_DefinitionVarTrain.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  dsPIC33FJ128MC802
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05

 * Created on 5 juillet 2019
 */

#ifndef MESCAN1_ID_DLC_INFRA_H
#define	MESCAN1_ID_DLC_INFRA_H


/**
  Section: Included Files
 */

#include "MESCAN1_DefinitionVariable.h"
#include "MESCAN1_common.h"

#define CAN_SPEED_BUS       125
#define CAN_SPEED_BUS_INFRA       125


/*******************************************************************************/
//Partie pour l'INFRA Balise

/*******************************************************************************/

typedef enum {
    MC_OFFSET_ID_PARAM_CARTE_BALISE = 0x01, //ATTENTION VARIABLE AVEC OFFSET 
    MC_OFFSET_ID_CRO_EBTL2_BALIA = 0x02,

    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIA = 0x03,
    MC_OFFSET_ID_FEU_BALIA = 0x04,
    MC_OFFSET_ID_FEU_BALIB = 0x05,
    MC_OFFSET_ID_DV_BALIA = 0x06,
    MC_OFFSET_ID_DV_BALIB = 0x07,

    MC_OFFSET_ID_CRO_EBTL2_BALIB = 0x0A,
    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIB = 0x0B,

    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE = 0x0D,

    MC_OFFSET_ID_EEPROM = 0xE, //ATTENTION VARIABLE AVEC OFFSET 

    //Identifiant CAN etendu
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIA = 0x00000, //Decalage de 8 par rapport aux RC
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIB = 0x00080,

} MC_ID_BALI_INFRA;

typedef enum {
    MC_DLC_PARAM_CARTE_BALISE = 0x06,
    MC_DLC_CRO_EBT_BALIA = 0x02,

    MC_DLC_CAPTEURS_ON_CI_BALIA = 0x03,
    MC_DLC_FEU_BALIA = 0x03,
    MC_DLC_FEU_BALIB = 0x03,
    MC_DLC_DV_BALIA = 0x03,
    MC_DLC_DV_BALIB = 0x03,

    MC_DLC_CAPTEURS_ON_CI_BALIB = 0x03,
    MC_DLC_STATUS_DYNAMIQUE_CARTE_BALISE = 0x08,
    MC_DLC_CRO_EBT_BALIB = 0x02,

    MC_DLC_INFRA_EEPROM = 0x0, //Why not car parametrable!!

    MC_DLC_SLICE_EBTL2BALIA = 0x08,
    MC_DLC_SLICE_EBTL2BALIB = 0x08,

} MC_DLC_BALI_INFRA;

//Nombre d'elements du tableau a envoyer des balises vers les locos
//#define BUFFER_DMA_FLUX_BALI		64	// Avant -->24
#define BUFFER_DMA_FLUX_BALI		128	// Avant -->24 et apres 64

#define NOMBRE_DE_BALISE    31
#define NOMBRE_CARTE_AIG    18

#define ETAT_FEUX_BALISE_AFTER_POWER_ON     FEU_ETEINT
#define ETAT_FEUX_AIG_AFTER_POWER_ON        FEU_ETEINT

#define	LOCO_ON_CAPTEUR_LEFT_ON_BALIAB			0x01
#define	LOCO_ON_CAPTEUR_RIGHT_ON_BALIAB			0x02

#define	CAR_STOP_CHGT_POLARITY					0x01

//Code d'erreurs
#define BALIA_FAIL_COM_IR           0xAF
#define BALIB_FAIL_COM_IR           0xBF


/*******************************************************************************/
//Partie pour l'INFRA Aiguillage

/*******************************************************************************/

typedef enum {
    MC_OFFSET_ID_PARAM_CARTE_AIG = 0x01, //ATTENTION VARIABLE AVEC OFFSET 

    MC_OFFSET_ID_INFRA_AIG = 0x02,
    MC_OFFSET_ID_FEUA_AIG = 0x04,
    MC_OFFSET_ID_FEUB_AIG = 0x05,
    MC_OFFSET_ID_AIG_POSITION_A = 0x06,
    MC_OFFSET_ID_AIG_POSITION_B = 0x07,

    MC_OFFSET_ID_ENERGIE_A = 0x0A,
    MC_OFFSET_ID_ENERGIE_B = 0x0B,

    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG = 0x0D,

    MC_OFFSET_ID_AIG_EEPROM = 0xE, //ATTENTION VARIABLE AVEC OFFSET 

} MC_ID_AIG_INFRA;

typedef enum {
    MC_DLC_PARAM_CARTE_AIG = 0x06,

    MC_OFFSET_DLC_INFRA_AIG = 0x03,
    MC_DLC_FEUA_AIG = 0x03,
    MC_DLC_FEUB_AIG = 0x03,
    MC_OFFSET_DLC_AIG_POSITION_A = 0x03,
    MC_OFFSET_DLC_AIG_POSITION_B = 0x03,

    MC_OFFSET_DLC_ENERGIE_A = 0x01,
    MC_OFFSET_DLC_ENERGIE_B = 0x01,

    MC_DLC_STATUS_DYNAMIQUE_CARTE_AIG = 0x08,

    MC_DLC_AIG_EEPROM = 0x0, //Why not car parametrable!!

} MC_DLC_AIG_INFRA;

/*******************************************************************************/
//ID et DLC Communs aux cartes Infrastructure
/*******************************************************************************/

typedef enum {
	MC_ID_CRASH_INFRA = 0x0C,
	MC_ID_MODE_ALIM_RAILS = 0xF0,
	MC_ID_TOUR_LEDS = 0x290,
	MC_ID_WARNING_INFRA = 0x0D,

} MC_ID_AUTRES_INFRA;

typedef enum {
	MC_DLC_INFRA_CRASH = 0x04,
	MC_DLC_INFRA_WARNING = 0x04,
	MC_DLC_MODE_ALIM_RAILS = 0x01,
	MC_DLC_TOUR_LEDS = 0x03,

} MC_DLC_AUTRES_INFRA;


/*******************************************************************************/
//Autres definitions pour carte Aiguillage
/*******************************************************************************/
#define	CDE_ENABLE_TRONCON_A						0x00
#define	CDE_ENABLE_TRONCON_B						0x00
#define	CDE_DESABLE_TRONCON_A						0x01
#define	CDE_DESABLE_TRONCON_B						0x01

#define CAR_UNLOCK_ACTIONNEUR						'U'
#define CAR_LOCK_ACTIONNEUR							'L'
#define CAR_INIT_ACTIONNEUR							'I'
#define CAR_AUTO_LOCK								'A'

#define POSI_BIT_AIGUILLE_LOCK                  	0x80

#define ACTIONNEUR_OCCUPE							0x04
#define ACTIONNEUR_DEJA_LOCK						0x05
#define ACTIONNEUR_CHGT_MANU						0x06
#define ACTIONNEUR_EN_PANNE							0x07

#define AIGUILLE_DROIT								0x00
#define AIGUILLE_BIFFURQUE							0x01

#define VALMAX_CPT_ACTIVE_RELAIS                	50
#define VALMAX_CPT_REFROIDISSEMENT                  300
#define TIME_SHAKE_BOBINE_RELAIS                    10

typedef enum {
    ETAT_INIT_BASCUL_AIG = 0x00,

    ACTIVATION_BOBINE_DROITE = 0x10,
    TEMPS_ACTIVATION_BOBINE_DROITE = 0x11,
    VERIF_IF_BASCUL_DROIT_OK = 0x12,
    PANNE_AIG_BLOQUE_EN_BIFFURQUE = 0x13,

    ACTIVATION_BOBINE_BIFFURQUE = 0x20,
    TEMPS_ACTIVATION_BOBINE_BIFFURQUE = 0x21,
    VERIF_IF_BASCUL_BIFFURQUE_OK = 0x22,
    PANNE_AIG_BLOQUE_EN_DROIT = 0x23,

    NEW_ESSAI_BASCUL_DROIT_PHASE_INIT = 0x30,
    NEW_ESSAI_BASCUL_DROIT_PHASE1 = 0x31,
    NEW_ESSAI_BASCUL_DROIT_PHASE2 = 0x32,
    NEW_ESSAI_BASCUL_DROIT_PHASE3 = 0x33,

    NEW_ESSAI_BASCUL_BIFFURQUE_PHASE_INIT = 0x40,
    NEW_ESSAI_BASCUL_BIFFURQUE_PHASE1 = 0x41,
    NEW_ESSAI_BASCUL_BIFFURQUE_PHASE2 = 0x42,
    NEW_ESSAI_BASCUL_BIFFURQUE_PHASE3 = 0x43,

    TEMPS_REFROISSEMENT_APRES_BLOQUAGE = 0x50,
    INIT_PROCEDURE_REFROIDISSEMENT = 0x51,
    TEMPS_REFROIDISSEMENT = 0x52,


} DIAG_ETAT_BASCUL_AIG;

/*******************************************************************************/
//ID et DLC Communs aux cartes Infrastructure
/*******************************************************************************/
//#define MC_ID_CRASH_INFRA                   0x0C
//#define MC_DLC_INFRA_CRASH                  0x04
//#define MC_ID_MODE_ALIM_RAILS               0xF0
//#define MC_ID_TOUR_LEDS                     0x290

//#define MC_ID_WARNING_INFRA                 0x0D
//#define MC_DLC_INFRA_WARNING                0x04
//#define MC_DLC_MODE_ALIM_RAILS              0x01
//#define MC_DLC_TOUR_LEDS                    0x03
#define LED_ROUGE_TOUR_ON                   0x01
#define LED_ROUGE_TOUR_OFF                  0x00

#define	IDF_FAULT_BASCUL_AIG				0x20

/*******************************************************************************/
//Autres parametres Communs aux cartes Infrastructure
/*******************************************************************************/
#define CAR_CONNAITRE_ETAT_ACTIONNEUR       'D'
#define CAR_COMMANDE_GO_ACTIONNEUR          'W'
#define MODULE_DEJA_DANS_ETAT_DEMANDE		0x01
#define TRAME_ERRONNEE             			0x02

#define NB_MAX_ETAT_POSSIBLE_FEUX			0x05

//Parametre 1 de la fonction SetFeux()
#define FEU_A                               0x00
#define FEU_B                               0x01

//Parametre 2 de la fonction SetFeux()
#define FEU_ETEINT							0x00
#define FEU_ROUGE_FIXE						0x01
#define FEU_VERT_FIXE						0x02
#define FEU_ROUGE_CLIGNO   					0x03
#define FEU_VERT_CLIGNO						0x04
#define FEU_ORANGE             				0x05

#define FEU_CHIFFRE_MAX                     0x05
#endif


