/* modifié le 4 fevrier 2020, Ajout "mc_CRO_Ebt_BaliseA"
 *  * modifie le 12 fevrier 2020, Déclaration de la trame "mc_InfraBAL_sliceEbtL1_ToBalA"
 */



/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_VarInfraBalAig.h

  @Summary:
    This is the MESCAN1_DeclarationVarTrain.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  dsPIC33FJ128MC802
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05

 * Created on 11 octobre 2019
 */
#ifndef ECAN1_DECLARATION_VAR_INFRA_BAL_AIG_H
#define	ECAN1_DECLARATION_VAR_INFRA_BAL_AIG_H


#include "MESCAN1_DefinitionVariable.h"
#include "MESCAN1_ID&DLC_INFRA.h"
#include "MESCAN1_Utilitaire.h"
//#include "MESCAN1_MAIN_PARAMS.h" // a valider
//#include "Librairies_Unirail/MESCAN1_Common.h"
#include "MESCAN1_common.h"
#include "MESCAN1_ID&DLC_INFRA.h"
//#include "MESCAN1_VarInfraBalAig.h"



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_InfraBAL_parametreCarte"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_InfraBAL_parametreCarte"

typedef enum {
    VAL_ROUES_CODEUSES = 0,
    VAL_CFG_DIPSWITCH = 1,
    VAL_CFG_SUPP = 2,
    NUMERO_BALISEA = 3, //ajout du 3 mars 2020
    NUMERO_BALISEB = 4, //ajout du 3 mars 2020
    VERSION_SOFT_INFRA_BALISE = 5,
} MC_MESSAGE_PARAMETRE_CARTE_BALISE;

//config bits de la data "VAL_CFG_DIPSWITCH" de la trame "mc_InfraBAL_parametreCarte"

typedef enum {
    IF_MODE_DEBUG_ACTIF = 7,
    NUMERO_MODE_DEBUG = 6,
    PROTECT_EEPROM = 5,
    ASSOCIATION_BALI_FEUX = 4,
    CONFA_BALISE_FEUX = 3,
    CONFB_GROUPE_BALISE = 2,
    FAIL1_BALISE = 1,
    FAIL2_BALISE = 0,
} MC_VAL_CFG_DIPSWITCH_BIT;

//config bits de la data "VAL_CFG_SUPP" de la trame "mc_InfraBAL_parametreCarte"

typedef enum {
    ACTIVATION_BALISEB = 0,
    ACTIVATION_MODE_FAILURE_BALISE = 1,
    SWITCH_ACTION_EVENT_BALISE = 2,
} MC_VAL_CFG_SUPP;


//------------------------------------------------------------------------------
extern uCAN1_MSG mc_InfraBAL_parametreCarte;

extern MC_Data8 cdmc_InfraBAL_RC;



//Union en 1 octet de tous les bits cfgs_DipswitchBalise
extern MC_Data8 cdmc_InfraBAL_cfgs_Dipswitch;

extern MC_Bit bdmc_InfraBAL_modeDebug;
extern MC_Bit bdmc_InfraBAL_modeDebug1or2;
extern MC_Bit bdmc_InfraBAL_modeProtectEEPROM;
extern MC_Bit bdmc_associeBaliseEtFeux;
extern MC_Bit bdmc_confA_BaliseFeux;
extern MC_Bit bdmc_confB_GroupeBalises;
extern MC_Bit bdmc_InfraBAL_fail1;
extern MC_Bit bdmc_InfraBAL_fail2;


//Union en 1 octet de tous les bits cdmc_InfraBAL_confSupp
extern MC_Data8 cdmc_InfraBAL_confSupp;

extern MC_Bit bdmc_InfraBAL_activationBalB;
extern MC_Bit bdmc_InfraBAL_activationModeFailure;
extern MC_Bit bdmc_InfraBAL_switchActionEvent;

extern MC_Data8 cdmc_numero_BalA;
extern MC_Data8 cdmc_numero_BalB;
extern MC_Data8 cdmc_InfraBAL_VersionSoft;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_CRO_Ebt_BaliseA" et datas associées
//
//  ATTENTION, ce sera commun avec la
// Déclaration de la trame "mc_CRO_Ebt_BaliseB" et datas associées

//Typedef commun aux 2 trames CAN

typedef enum {
    NUMERO_LOCO = 0,
    //VERSION_SOFT_INFRA = 1, //a verif 
    CRO_TRANSFERT_EBTL2 = 1,
} MC_CRO_TRANSFERT_EBTL2;

extern uCAN1_MSG mc_InfraBAL_CRO_EbtL2_BalA;

extern MC_Data8 cdmc_InfraBAL_numeroLoco_BalA;
//extern MC_Data8 cdmc_baliA_infraBalise_versionSoft;
extern MC_Data8 cdmc_InfraBAL_CRO_transfert_EbtL2_BalA;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_CRO_EbtL2_BalB" et datas associées

extern uCAN1_MSG mc_InfraBAL_CRO_EbtL2_BalB;

extern MC_Data8 cdmc_InfraBAL_numeroLoco_BalB;
extern MC_Data8 cdmc_InfraBAL_CRO_transfert_EbtL2_BalB;
///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_InfraBAL_capteurOnCI_BalA"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_CAPTEUR_ON_CI_BALIA = 0,
    ETAT_CAPTEUR_ON_CI_BALIA = 1,
    STATUS_CAPTEUR_ON_CI_BALIA = 2,
} MC_MESSAGE_CAPTEUR_ON_CI_BALIA;

//------------------------------------------------------------------------------
extern uCAN1_MSG mc_InfraBAL_capteurOnCI_BalA;

extern MC_Data8 cdmc_typeData_CapteurOnCI_BalA;
extern MC_Data8 cdmc_etat_CapteurOnCI_BalA;
extern MC_Data8 cdmc_status_CapteurOnCI_BalA;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_InfraBAL_feu_A"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_FEU_BALIA = 0,
    COULEUR_FEU_BALIA = 1,
    STATUS_FEU_BALIA = 2,
} MC_MESSAGE_FEU_BALIA;

//------------------------------------------------------------------------------

// Déclaration de la trame "mc_InfraBAL_feu_A" et datas associées
extern uCAN1_MSG mc_InfraBAL_feu_A;

extern MC_Data8 cdmc_InfraBAL_typeData_Feu_A;
extern MC_Data8 cdmc_InfraBAL_couleur_Feu_A;
extern MC_Data8 cdmc_InfraBAL_status_Feu_A;


///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_InfraBAL_feu_B"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_FEU_BALIB = 0,
    COULEUR_FEU_BALIB = 1,
    STATUS_FEU_BALIB = 2,
} MC_MESSAGE_FEU_BALIB;

//------------------------------------------------------------------------------

// Déclaration de la trame "mc_InfraBAL_feu_B" et datas associées
extern uCAN1_MSG mc_InfraBAL_feu_B;

extern MC_Data8 cdmc_InfraBAL_typeData_Feu_B;
extern MC_Data8 cdmc_InfraBAL_couleur_Feu_B;
extern MC_Data8 cdmc_InfraBAL_status_Feu_B;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_InfraBAL_DV_A"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_DV_BALIA = 0,
    ETAT_DV_BALIA = 1,
    STATUS_DV_BALIA = 2,
} MC_MESSAGE_DV_BALIA;

//------------------------------------------------------------------------------

// Déclaration de la trame "mc_InfraBAL_DV_A" et datas associées
extern uCAN1_MSG mc_InfraBAL_DV_A;

extern MC_Data8 cdmc_typeData_DV_A;
extern MC_Data8 cdmc_etat_DV_A;
extern MC_Data8 cdmc_status_DV_A;




///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_InfraBAL_DV_B"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_DV_BALIB = 0,
    ETAT_DV_BALIB = 1,
    STATUS_DV_BALIB = 2,
} MC_MESSAGE_DV_BALIB;

//------------------------------------------------------------------------------

// Déclaration de la trame "mc_InfraBAL_DV_B" et datas associées
extern uCAN1_MSG mc_InfraBAL_DV_B;

extern MC_Data8 cdmc_typeData_DV_B;
extern MC_Data8 cdmc_etat_DV_B;
extern MC_Data8 cdmc_status_DV_B;





///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_InfraBAL_capteurOnCI_BalB"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_CAPTEUR_ON_CI_BALIB = 0,
    ETAT_CAPTEUR_ON_CI_BALIB = 1,
    STATUS_CAPTEUR_ON_CI_BALIB = 2,
} MC_MESSAGE_CAPTEUR_ON_CI_BALIB;

//------------------------------------------------------------------------------
extern uCAN1_MSG mc_InfraBAL_capteurOnCI_BalB;

extern MC_Data8 cdmc_typeData_CapteurOnCI_BalB;
extern MC_Data8 cdmc_etat_CapteurOnCI_BalB;
extern MC_Data8 cdmc_status_CapteurOnCI_BalB;




//------------------------------------------------------------------------------





///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_InfraBAL_statusDynamique"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_InfraBAL_statusDynamique"

typedef enum {
    LEDS_BARGRAPH = 0,
    CPT_BAD_COM_IR_BALIA = 1,
    CPT_BAD_COM_IR_BALIB = 2,
    CPT_BAL_BAD_TRAMES = 3,
    CPT_BAL_TX_CAN_ERROR = 4,
    CPT_BAL_RX_CAN_ERROR = 5,
    LAST_ID_BAL_TRAME_ERRONE = 6,
} MC_STATUS_DYNAMIQUE_CARTE_BALISE;

//Enumeration pour leds du bargraph

typedef enum {
    ERROR_PASSIVE_CANTX_CARTE_BALISE = 7,
    ERROR_PASSIVE_CANRX_CARTE_BALISE = 6,
    FAIL_COM_IR_BALIA = 5,
    FAIL_COM_IR_BALIB = 4,
    FAIL_EEPROM_CARTE_BALISE = 3,
    DEF1_CARTE_BALISE = 2,
    DEF2_CARTE_BALISE = 1,
    DEF3_CARTE_BALISE = 0,
} ENUM_LED_BARGRAPH_CARTE_BALISE;

// Déclaration de la trame "mc_InfraBAL_statusDynamique" et datas associées
extern uCAN1_MSG mc_InfraBAL_statusDynamique;

extern MC_Data8 cdmc_InfraBAL_etatLedsBargraph;

//Decomposition de "cdmc_InfraBAL_etatLedsBargraph" en bits distincts
extern MC_Bit bdmc_InfraBAL_CAN_TxErrorPassive;
extern MC_Bit bdmc_InfraBAL_CAN_RxErrorPassive;
extern MC_Bit bdmc_warningFailureCommBalA;
extern MC_Bit bdmc_warningFailureCommBalB;
extern MC_Bit bdmc_InfraBAL_defEEPROM;
extern MC_Bit bdmc_InfraBAL_def1TrameErronee;
extern MC_Bit bdmc_InfraBAL_def2;
extern MC_Bit bdmc_InfraBAL_def3;

//Autres variables 
extern MC_Data8 cdmc_cptBadComIR_WithBalA;
extern MC_Data8 cdmc_cptBadComIR_WithBalB;
extern MC_Data8 cdmc_InfraBAL_cptTrameErronee;
extern MC_Data8 cdmc_InfraBAL_cptTxCAN_Error;
extern MC_Data8 cdmc_InfraBAL_cptRxCAN_Error;
extern MC_Data16 wdmc_InfraBAL_ID_TrameErronee;




#ifndef EEPROM
#define EEPROM
///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_InfraBAL_EEPROM"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    COMMANDE_EEPROM = 0,
    OFFSET_EEPROM = 1,
    DATA1EEPROM = 1,
    DATA2EEPROM = 2,
    DATA3EEPROM = 3,
    DATA4EEPROM = 4,
    DATA5EEPROM = 5,
    DATA6EEPROM = 6,
    DATA7EEPROM = 7,
} MC_MESSAGE_EEPROM;


//------------------------------------------------------------------------------
#endif
// Déclaration de la trame "mc_InfraBAL_EEPROM" et datas associées
extern uCAN1_MSG mc_InfraBAL_EEPROM;
extern MC_Data8 cdmc_InfraBAL_commande_EEPROM;
extern MC_Data16 wdmc_InfraBAL_offset_EEPROM;
extern MC_Data8 cdmc_InfraBAL_data1_EEPROM;
extern MC_Data8 cdmc_InfraBAL_data2_EEPROM;
extern MC_Data8 cdmc_InfraBAL_data3_EEPROM;
extern MC_Data8 cdmc_InfraBAL_data4_EEPROM;
extern MC_Data8 cdmc_InfraBAL_data5_EEPROM;
extern MC_Data8 cdmc_InfraBAL_data6_EEPROM;
extern MC_Data8 cdmc_InfraBAL_data7_EEPROM;







//TRAMES CAN ETENDUES   TRAMES CAN ETENDUES     TRAMES CAN ETENDUES

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_sliceEbtL1_ToBalA" et datas associées

//Commun pour trames BaliA et BaliB
#ifndef EBT_ENUM
#define EBT_ENUM

typedef enum {
    LEN_EBTL0 = 0,
    CKS_EBTL1 = 1,
    STANDARD_COM = 2,
    DATASUP = 3,
} MC_SLICE_EBTL1_TO_BALIX;
#endif

extern uCAN1_MSG mc_InfraBAL_sliceEbtL1_ToBalA;

extern MC_Data8 cdmc_len_EbtL0_BalA;
extern MC_Data8 cdmc_CKS_EbtL1_BalA;
extern MC_Data8 cdmc_standardCom_BalA;
extern MC_Data8 cdmc_dataSup_BalA;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_sliceEbtL1_ToBalB" et datas associees
extern uCAN1_MSG mc_InfraBAL_sliceEbtL1_ToBalB;

extern MC_Data8 cdmc_len_EbtL0_BalB;
extern MC_Data8 cdmc_CKS_EbtL1_BalB;
extern MC_Data8 cdmc_standardCom_BalB;
extern MC_Data8 cdmc_dataSup_BalB;





///////////////////////////////////////////////////////////////////////////////
//  POUR CARTE AIGUILLAGE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_InfraAIG_parametreCarte"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    REF_ENERGIE_A = 3,
    REF_ENERGIE_B = 4,
    VERSION_SOFT_INFRA_AIGUILLE = 5,
} MC_MESSAGE_PARAMETRE_CARTE_AIGUILLE;


extern uCAN1_MSG mc_InfraAIG_parametreCarte;

extern MC_Data8 cdmc_InfraAIG_RC;

//Definitions des variables de "cdmc_InfraAIG_cfgs_Dipswitch"

extern MC_Data8 cdmc_InfraAIG_cfgs_Dipswitch;

extern MC_Bit bdmc_InfraAIG_modeDebug;
extern MC_Bit bdmc_InfraAIG_modeDebug_1or2;
extern MC_Bit bdmc_InfraAIG_modeProtect_EEPROM;
extern MC_Bit bdmc_associeAiguilleEtFeux;
extern MC_Bit bdmc_confA_NombreFeuxActifs;
extern MC_Bit bdmc_confB_NombreHallActifs;
extern MC_Bit bdmc_InfraAIG_fail1;
extern MC_Bit bdmc_InfraAIG_fail2;

//Definitions des variables de "cdmc_InfraAIG_confSupp"

extern MC_Data8 cdmc_InfraAIG_confSupp;

extern MC_Bit bdmc_InfraAIG_activationSecu;
extern MC_Bit bdmc_InfraAIG_activationModeFailure;
extern MC_Bit bdmc_InfraAIG_switchActionEvent;

extern MC_Data8 cdmc_numero_energieA;
extern MC_Data8 cdmc_numero_energieB;
extern MC_Data8 cdmc_InfraAIG_VersionSoft;




///////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_Aiguille" et datas associees
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_AIG_TYPEDATA = 0,
    STATUS_MC_AIG_POSITION = 1,
    STATUS_MC_AIG_LOCK_OR_CRO = 2,
} MC_MESSAGE_AIG;

extern uCAN1_MSG mc_InfraAIG_Aiguille;

extern MC_Data8 cdmc_InfraAIG_typeData;
extern MC_Data8 cdmc_InfraAIG_position;
extern MC_Data8 cdmc_InfraAIG_lock_or_CRO;





///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_InfraAIG_feu_A"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_FEUA_AIG = 0,
    COULEUR_FEUA_AIG = 1,
    STATUS_FEUA_AIG = 2,
} MC_MESSAGE_FEUA_AIG;

// Declaration de la trame "mc_InfraAIG_feu_A" et datas associees
extern uCAN1_MSG mc_InfraAIG_feu_A;

extern MC_Data8 cdmc_InfraAIG_typeData_Feu_A;
extern MC_Data8 cdmc_InfraAIG_couleur_Feu_A;
extern MC_Data8 cdmc_InfraAIG_status_Feu_A;



///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_InfraAIG_feu_B"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    STATUS_MC_FEUB_AIG = 0,
    COULEUR_FEUB_AIG = 1,
    STATUS_FEUB_AIG = 2,
} MC_MESSAGE_FEUB_AIG;

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_feu_B" et datas associees
extern uCAN1_MSG mc_InfraAIG_feu_B;

extern MC_Data8 cdmc_InfraAIG_typeData_Feu_B;
extern MC_Data8 cdmc_InfraAIG_couleur_Feu_B;
extern MC_Data8 cdmc_InfraAIG_status_Feu_B;






////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_capteurPositionA" et datas associees

typedef enum {
    STATUS_DATA_CAPTEUR_AIG_POSITION_AandB = 0,
    ETAT_CAPTEUR_AIG_POSITION_AandB = 1,
    STATUS_CAPTEUR_AIG_POSITION_AandB = 2,
} MC_MESSAGE_CAPTEUR_AIG;

extern uCAN1_MSG mc_InfraAIG_capteurPositionA;

extern MC_Data8 cdmc_InfraAIG_typeData_CapteurA;
extern MC_Data8 cdmc_InfraAIG_etat_CapteurA;
extern MC_Data8 cdmc_InfraAIG_status_CapteurA;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_capteurPositionA" et datas associees
extern uCAN1_MSG mc_InfraAIG_capteurPositionB;

extern MC_Data8 cdmc_InfraAIG_typeData_CapteurB;
extern MC_Data8 cdmc_InfraAIG_etat_CapteurB;
extern MC_Data8 cdmc_InfraAIG_status_CapteurB;






////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_energieA" et datas associes
extern uCAN1_MSG mc_InfraAIG_energieA;
extern MC_Data8 cdmc_commande_EnergieA;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_energieB" et datas associes
extern uCAN1_MSG mc_InfraAIG_energieB;
extern MC_Data8 cdmc_commande_EnergieB;





////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_EEPROM" et datas associees
extern uCAN1_MSG mc_InfraAIG_EEPROM;

extern MC_Data8 cdmc_InfraAIG_commande_EEPROM;

extern MC_Data16 wdmc_InfraAIG_offset_EEPROM;

extern MC_Data8 cdmc_InfraAIG_data1_EEPROM;
extern MC_Data8 cdmc_InfraAIG_data2_EEPROM;
extern MC_Data8 cdmc_InfraAIG_data3_EEPROM;
extern MC_Data8 cdmc_InfraAIG_data4_EEPROM;
extern MC_Data8 cdmc_InfraAIG_data5_EEPROM;
extern MC_Data8 cdmc_InfraAIG_data6_EEPROM;
extern MC_Data8 cdmc_InfraAIG_data7_EEPROM;




///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_InfraAIG_statusDynamique"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_InfraAIG_statusDynamique"

typedef enum {
    LEDS_BARGRAPH_AIG = 0,
    AIG_STATUS = 1,
    CPT_BASCUL_DURDUR = 2,
    CPT_AIG_BAD_TRAMES = 3,
    CPT_AIG_TX_CAN_ERROR = 4,
    CPT_AIG_RX_CAN_ERROR = 5,
    LAST_ID_TRAME_ERRONE = 6,
} MC_STATUS_DYNAMIQUE_CARTE_AIG;

//Enumeration pour leds du bargraph

typedef enum {
    ERROR_PASSIVE_CANTX_CARTE_AIG = 7,
    ERROR_PASSIVE_CANRX_CARTE_AIG = 6,
    BASCUL_AIG_DURDUR = 5,
    AIG_SECU = 4,
    FAIL_EEPROM_CARTE_AIG = 3,
    DEF1_CARTE_AIG = 2,
    DEF2_CARTE_AIG = 1,
    DEF3_CARTE_AIG = 0,
} ENUM_LED_BARGRAPH_CARTE_AIG;

//typedef enum {
//    AIG_LOCKED = 0,
//    AIG_MODE_AUTO_LOCKED = 1,
//} ENUM_STATUS_AIG;

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_statusDynamique" et datas associees
extern uCAN1_MSG mc_InfraAIG_statusDynamique;

extern MC_Data8 cdmc_InfraAIG_etatLedsBargraph;

//Decomposition de "cdmc_InfraBAL_etatLedsBargraph" en bits distincts
extern MC_Bit bdmc_InfraAIG_CAN_TxErrorPassive;
extern MC_Bit bdmc_InfraAIG_CAN_RxErrorPassive;
extern MC_Bit bdmc_InfraAIG_Gripper;
extern MC_Bit bdmc_InfraAIG_secu;
extern MC_Bit bdmc_InfraAIG_defEEPROM;
extern MC_Bit bdmc_InfraAIG_def1TrameErronee;
extern MC_Bit bdmc_InfraAIG_def2;
extern MC_Bit bdmc_panneAig;

//extern MC_Data8 cdmc_InfraAIG_status_Aig;
//extern MC_Bit bdmc_Aig_Locked;
//extern MC_Bit bdmc_modeAutoLockAig;

extern MC_Data8 cdmc_cptBascul_Aig_complique;
extern MC_Data8 cdmc_InfraAIG_cptTrameErronee;
extern MC_Data8 cdmc_InfraAIG_cptTxCAN_Error;
extern MC_Data8 cdmc_InfraAIG_cptRxCAN_Error;
//extern MC_Data8 cdmc_InfraAIG_PoidsFaibles_ID_TrameErronee;
extern MC_Data16 wdmc_InfraAIG_ID_TrameErronee;






///////////////////////////////////////////////////////////////////////////////
//  COMMUN AUX CARTES INFRA
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_Infra_crash"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    SOURCE_CRASH_INFRA = 0,
    TYPE_CRASH_INFRA = 1,
    NUMERO_RC_CRASH_INFRA = 2,
    CODE_CRASH_INFRA = 3,
} MC_MESSAGE_CRASH_INFRA;

extern uCAN1_MSG mc_Infra_crash;
extern MC_Data8 cdmc_InfraCrash_source;

extern MC_Data8 cdmc_InfraCrash_type;
extern MC_Data8 cdmc_InfraCrash_RC;
extern MC_Data8 cdmc_InfraCrash_code;


///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_Infra_warning"
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    SOURCE_WARNING_INFRA = 0,
    TYPE_WARNING_INFRA = 1,
    NUMERO_RC_WARNING_INFRA = 2,
    CODE_WARNING_INFRA = 3,
} MC_MESSAGE_WARNING_INFRA;

extern uCAN1_MSG mc_Infra_warning;
extern MC_Data8 cdmc_InfraWarning_source;
extern MC_Data8 cdmc_InfraWarning_type;
extern MC_Data8 cdmc_InfraWarning_RC;
extern MC_Data8 cdmc_InfraWarning_code;



///////////////////////////////////////////////////////////////////////////////
//Decomposition des datas de la trame "mc_alimentationRails"
///////////////////////////////////////////////////////////////////////////////

#define INDICE_DATA_FOR_MODE_ALIM_RAILS     0x00
#define CAR_STOP_CHGT_POLARITY              0x01

extern uCAN1_MSG mc_alimentationRails;
extern MC_Data8 cdmc_typeCommande_AlimentationRails;



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_ledRouge_On_Tour" et datas associes

typedef enum {
    TYPE_DATA_LED_ON_TOUR = 0,
    ETAT_DATA_LED_ON_TOUR = 1,
    STATUS_DATA_LED_ON_TOUR = 2,
} MC_MESSAGE_TOUR_LED;

extern uCAN1_MSG mc_ledRouge_On_Tour;

extern MC_Data8 cdmc_typeData_LedRouge_On_Tour;
extern MC_Data8 cdmc_etat_LedRouge_On_Tour;
extern MC_Data8 cdmc_status_LedRouge_On_Tour;






#endif	/* ECAN1_DECLARATION_VAR_INFRA_BAL_AIG_H */