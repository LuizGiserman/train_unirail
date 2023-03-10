/* modifi� le 4 fevrier 2020, Ajout "mc_CRO_Ebt_BaliseA"
 * modifie le 12 fevrier 2020, Déclaration de la trame "mc_InfraBAL_sliceEbtL1_ToBalA"
 */




/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_VarInfraBalAig.c

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

/**
  Section: Included Files
 */

#include "MESCAN1_VarInfraBalAig.h"


    


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_parametreCarte" et datas associes
uCAN1_MSG mc_InfraBAL_parametreCarte = {
    {MC_OFFSET_ID_PARAM_CARTE_BALISE,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_PARAM_CARTE_BALISE,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraBAL_RC = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_ROUES_CODEUSES,
};

//Definitions des variables de "cdmc_InfraBAL_cfgs_Dipswitch"

//Union en 1 octet de tous les bits cfgs_DipswitchBalise
MC_Data8 cdmc_InfraBAL_cfgs_Dipswitch = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
};

MC_Bit bdmc_InfraBAL_modeDebug = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    IF_MODE_DEBUG_ACTIF,
};
 
MC_Bit bdmc_InfraBAL_modeDebug1or2 = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    NUMERO_MODE_DEBUG,
};

MC_Bit bdmc_InfraBAL_modeProtectEEPROM = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    PROTECT_EEPROM,
};

MC_Bit bdmc_associeBaliseEtFeux = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    ASSOCIATION_BALI_FEUX,
};

MC_Bit bdmc_confA_BaliseFeux = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    CONFA_BALISE_FEUX,
};

MC_Bit bdmc_confB_GroupeBalises = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    CONFB_GROUPE_BALISE,
};

MC_Bit bdmc_InfraBAL_fail1 = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    FAIL1_BALISE,
};

MC_Bit bdmc_InfraBAL_fail2 = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_DIPSWITCH,
    FAIL2_BALISE,
};

//Definitions des variables de "cdmc_InfraBAL_confSupp"

//Union en 1 octet de tous les bits cdmc_InfraBAL_confSupp
MC_Data8 cdmc_InfraBAL_confSupp = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_SUPP,
};

MC_Bit bdmc_InfraBAL_activationBalB = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_SUPP,
    ACTIVATION_BALISEB,
};

MC_Bit bdmc_InfraBAL_activationModeFailure = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_SUPP,
    ACTIVATION_MODE_FAILURE_BALISE,
};

MC_Bit bdmc_InfraBAL_switchActionEvent = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VAL_CFG_SUPP,
    SWITCH_ACTION_EVENT_BALISE,
};

MC_Data8 cdmc_numero_BalA = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    NUMERO_BALISEA,
};
MC_Data8 cdmc_numero_BalB = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    NUMERO_BALISEB,
};

MC_Data8 cdmc_InfraBAL_VersionSoft = {
    MC_OFFSET_ID_PARAM_CARTE_BALISE,
    VERSION_SOFT_INFRA_BALISE,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_CRO_EbtL2_BalA" et datas associées

uCAN1_MSG mc_InfraBAL_CRO_EbtL2_BalA = {
    {MC_OFFSET_ID_CRO_EBTL2_BALIA,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_CRO_EBT_BALIA,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraBAL_numeroLoco_BalA = {
    MC_OFFSET_ID_CRO_EBTL2_BALIA,
    NUMERO_LOCO,
};
// \todo à valider (cette var n existe plus a cet endroit)
//MC_Data8 cdmc_baliA_infraBalise_versionSoft = {
//    MC_OFFSET_ID_CRO_EBTL2_BALIA,
//    VERSION_SOFT_INFRA_BALISE,
//};

MC_Data8 cdmc_InfraBAL_CRO_transfert_EbtL2_BalA = {
    MC_OFFSET_ID_CRO_EBTL2_BALIA,
    CRO_TRANSFERT_EBTL2,
};

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_CRO_EbtL2_BalB" et datas associées

uCAN1_MSG mc_InfraBAL_CRO_EbtL2_BalB = {
    {MC_OFFSET_ID_CRO_EBTL2_BALIB,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_CRO_EBT_BALIB,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraBAL_numeroLoco_BalB = {
    MC_OFFSET_ID_CRO_EBTL2_BALIB,
    NUMERO_LOCO,
};
// \todo à valider (cette var n existe plus a cet endroit)
//MC_Data8 cdmc_baliA_infraBalise_versionSoft = {
//    MC_OFFSET_ID_CRO_EBTL2_BALIA,
//    VERSION_SOFT_INFRA_BALISE,
//};

MC_Data8 cdmc_InfraBAL_CRO_transfert_EbtL2_BalB = {
    MC_OFFSET_ID_CRO_EBTL2_BALIB,
	CRO_TRANSFERT_EBTL2,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_capteurOnCI_BalA" et datas associees
uCAN1_MSG mc_InfraBAL_capteurOnCI_BalA = {
    {MC_OFFSET_ID_CAPTEURS_ON_CI_BALIA,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_CAPTEURS_ON_CI_BALIA,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_typeData_CapteurOnCI_BalA = {
    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIA,
    STATUS_MC_CAPTEUR_ON_CI_BALIA,
};

MC_Data8 cdmc_etat_CapteurOnCI_BalA = {
    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIA,
    ETAT_CAPTEUR_ON_CI_BALIA,
};

MC_Data8 cdmc_status_CapteurOnCI_BalA = {
    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIA,
    STATUS_CAPTEUR_ON_CI_BALIA,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_feu_A" et datas associees
uCAN1_MSG mc_InfraBAL_feu_A = {
    {MC_OFFSET_ID_FEU_BALIA,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_FEU_BALIA,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraBAL_typeData_Feu_A = {
    MC_OFFSET_ID_FEU_BALIA,
    STATUS_MC_FEU_BALIA,
};

MC_Data8 cdmc_InfraBAL_couleur_Feu_A = {
    MC_OFFSET_ID_FEU_BALIA,
    COULEUR_FEU_BALIA,
};

MC_Data8 cdmc_InfraBAL_status_Feu_A = {
    MC_OFFSET_ID_FEU_BALIA,
    STATUS_FEU_BALIA,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_feu_B" et datas associées
uCAN1_MSG mc_InfraBAL_feu_B = {
    {MC_OFFSET_ID_FEU_BALIB,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_FEU_BALIB,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraBAL_typeData_Feu_B = {
    MC_OFFSET_ID_FEU_BALIB,
    STATUS_MC_FEU_BALIB,
};

MC_Data8 cdmc_InfraBAL_couleur_Feu_B = {
    MC_OFFSET_ID_FEU_BALIB,
    COULEUR_FEU_BALIB,
};

MC_Data8 cdmc_InfraBAL_status_Feu_B = {
    MC_OFFSET_ID_FEU_BALIB,
    STATUS_FEU_BALIB,
};




////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_DV_A" et datas associées
uCAN1_MSG mc_InfraBAL_DV_A = {
    {MC_OFFSET_ID_DV_BALIA,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_DV_BALIA,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_typeData_DV_A = {
    MC_OFFSET_ID_DV_BALIA,
    STATUS_MC_DV_BALIA,
};

MC_Data8 cdmc_etat_DV_A = {
    MC_OFFSET_ID_DV_BALIA,
    ETAT_DV_BALIA,
};

MC_Data8 cdmc_status_DV_A = {
    MC_OFFSET_ID_DV_BALIA,
    STATUS_DV_BALIA,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_DV_B" et datas associées
uCAN1_MSG mc_InfraBAL_DV_B = {
    {MC_OFFSET_ID_DV_BALIB,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_DV_BALIB,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_typeData_DV_B = {
    MC_OFFSET_ID_DV_BALIB,
    STATUS_MC_DV_BALIB,
};

MC_Data8 cdmc_etat_DV_B = {
    MC_OFFSET_ID_DV_BALIB,
    ETAT_DV_BALIB,
};

MC_Data8 cdmc_status_DV_B = {
    MC_OFFSET_ID_DV_BALIB,
    STATUS_DV_BALIB,
};










////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_capteurOnCI_BalB" et datas associees
uCAN1_MSG mc_InfraBAL_capteurOnCI_BalB = {
    {MC_OFFSET_ID_CAPTEURS_ON_CI_BALIB,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_CAPTEURS_ON_CI_BALIB,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_typeData_CapteurOnCI_BalB = {
    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIB,
    STATUS_MC_CAPTEUR_ON_CI_BALIB,
};

MC_Data8 cdmc_etat_CapteurOnCI_BalB = {
    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIB,
    ETAT_CAPTEUR_ON_CI_BALIB,
};

MC_Data8 cdmc_status_CapteurOnCI_BalB = {
    MC_OFFSET_ID_CAPTEURS_ON_CI_BALIB,
    STATUS_CAPTEUR_ON_CI_BALIB,
};




           
            

 ////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_statusDynamique" et datas associees
uCAN1_MSG mc_InfraBAL_statusDynamique = {
    {MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_STATUS_DYNAMIQUE_CARTE_BALISE,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraBAL_etatLedsBargraph = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
};

//Decomposition de "cdmc_InfraBAL_etatLedsBargraph" en bits distincts
MC_Bit bdmc_InfraBAL_CAN_TxErrorPassive = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    ERROR_PASSIVE_CANTX_CARTE_BALISE,
};

MC_Bit bdmc_InfraBAL_CAN_RxErrorPassive = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    ERROR_PASSIVE_CANRX_CARTE_BALISE,
};

MC_Bit bdmc_warningFailureCommBalA = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    FAIL_COM_IR_BALIA,
};

MC_Bit bdmc_warningFailureCommBalB = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    FAIL_COM_IR_BALIB,
};

MC_Bit bdmc_InfraBAL_defEEPROM = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    FAIL_EEPROM_CARTE_BALISE,
};

MC_Bit bdmc_InfraBAL_def1TrameErronee = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    DEF1_CARTE_BALISE,
};

MC_Bit bdmc_InfraBAL_def2 = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    DEF2_CARTE_BALISE,
};

MC_Bit bdmc_InfraBAL_def3 = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LEDS_BARGRAPH,
    DEF3_CARTE_BALISE,
};

//Autres variables 
MC_Data8 cdmc_cptBadComIR_WithBalA = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    CPT_BAD_COM_IR_BALIA,
};

MC_Data8 cdmc_cptBadComIR_WithBalB = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    CPT_BAD_COM_IR_BALIB,
};

MC_Data8 cdmc_InfraBAL_cptTrameErronee = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    CPT_BAL_BAD_TRAMES,
};

MC_Data8 cdmc_InfraBAL_cptTxCAN_Error = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    CPT_BAL_TX_CAN_ERROR,
};

MC_Data8 cdmc_InfraBAL_cptRxCAN_Error = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    CPT_BAL_RX_CAN_ERROR,
};


MC_Data16 wdmc_InfraBAL_ID_TrameErronee = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_CARTE_BALISE,
    LAST_ID_BAL_TRAME_ERRONE,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_EEPROM" et datas associees
uCAN1_MSG mc_InfraBAL_EEPROM = {
    {MC_OFFSET_ID_EEPROM,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_INFRA_EEPROM,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_InfraBAL_commande_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    COMMANDE_EEPROM,
};
MC_Data16 wdmc_InfraBAL_offset_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    OFFSET_EEPROM,
};
MC_Data8 cdmc_InfraBAL_data1_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    DATA1EEPROM,
};
MC_Data8 cdmc_InfraBAL_data2_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    DATA2EEPROM,
};
MC_Data8 cdmc_InfraBAL_data3_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    DATA3EEPROM,
};
MC_Data8 cdmc_InfraBAL_data4_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    DATA4EEPROM,
};
MC_Data8 cdmc_InfraBAL_data5_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    DATA5EEPROM,
};
MC_Data8 cdmc_InfraBAL_data6_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    DATA6EEPROM,
};
MC_Data8 cdmc_InfraBAL_data7_EEPROM = {
    MC_OFFSET_ID_EEPROM,
    DATA7EEPROM,
};




//TRAMES CAN ETENDUES   TRAMES CAN ETENDUES     TRAMES CAN ETENDUES

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraBAL_sliceEbtL1_ToBalA" et datas associees
uCAN1_MSG mc_InfraBAL_sliceEbtL1_ToBalA = {
    {MC_OFFSET_IDEXT_SLICE_EBTL2BALIA,
        CAN1_FRAME_EXT, CAN1_MSG_DATA, MC_DLC_SLICE_EBTL2BALIA,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_len_EbtL0_BalA = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIA,
    LEN_EBTL0,
};

MC_Data8 cdmc_CKS_EbtL1_BalA = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIA,
    CKS_EBTL1,
};

MC_Data8 cdmc_standardCom_BalA = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIA,
    STANDARD_COM,
};

MC_Data8 cdmc_dataSup_BalA = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIA,
    DATASUP,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_InfraBAL_sliceEbtL1_ToBalB" et datas associées
uCAN1_MSG mc_InfraBAL_sliceEbtL1_ToBalB = {
    {MC_OFFSET_IDEXT_SLICE_EBTL2BALIB,
        CAN1_FRAME_EXT, CAN1_MSG_DATA, MC_DLC_SLICE_EBTL2BALIB,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_len_EbtL0_BalB = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIB,
    LEN_EBTL0,
};

MC_Data8 cdmc_CKS_EbtL1_BalB = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIB,
    CKS_EBTL1,
};

MC_Data8 cdmc_standardCom_BalB = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIB,
    STANDARD_COM,
};

MC_Data8 cdmc_dataSup_BalB = {
    MC_OFFSET_IDEXT_SLICE_EBTL2BALIB,
    DATASUP,
};






////////////////////////////////////////////////////////////////////////////////
//  Variables CAN de la Carte Aiguillage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_parametreCarte" et datas associes
uCAN1_MSG mc_InfraAIG_parametreCarte = {
    {MC_OFFSET_ID_PARAM_CARTE_AIG,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_PARAM_CARTE_AIG,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraAIG_RC = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_ROUES_CODEUSES,
};

//Definitions des variables de "cdmc_InfraAIG_cfgs_Dipswitch"

//Union en 1 octet de tous les bits cdmc_InfraAIG_cfgs_Dipswitch
MC_Data8 cdmc_InfraAIG_cfgs_Dipswitch = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
};

MC_Bit bdmc_InfraAIG_modeDebug = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    IF_MODE_DEBUG_ACTIF,
};
 
MC_Bit bdmc_InfraAIG_modeDebug_1or2 = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    NUMERO_MODE_DEBUG,
};

MC_Bit bdmc_InfraAIG_modeProtect_EEPROM = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    PROTECT_EEPROM,
};

MC_Bit bdmc_associeAiguilleEtFeux = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    ASSOCIATION_BALI_FEUX,
};

MC_Bit bdmc_confA_NombreFeuxActifs = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    CONFA_BALISE_FEUX,
};

MC_Bit bdmc_confB_NombreHallActifs = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    CONFB_GROUPE_BALISE,
};

MC_Bit bdmc_InfraAIG_fail1 = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    FAIL1_BALISE,
};

MC_Bit bdmc_InfraAIG_fail2 = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_DIPSWITCH,
    FAIL2_BALISE,
};

//Definitions des variables de "cdmc_InfraAIG_confSupp"

//Union en 1 octet de tous les bitscdmc_InfraAIG_confSupp
MC_Data8 cdmc_InfraAIG_confSupp = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_SUPP,
};

MC_Bit bdmc_InfraAIG_activationSecu = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_SUPP,
    ACTIVATION_BALISEB,
};

MC_Bit bdmc_InfraAIG_activationModeFailure = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_SUPP,
    ACTIVATION_MODE_FAILURE_BALISE,
};

MC_Bit bdmc_InfraAIG_switchActionEvent = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VAL_CFG_SUPP,
    SWITCH_ACTION_EVENT_BALISE,
};

MC_Data8 cdmc_numero_energieA = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    REF_ENERGIE_A,
};

MC_Data8 cdmc_numero_energieB = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    REF_ENERGIE_B,
};

MC_Data8 cdmc_InfraAIG_VersionSoft = {
    MC_OFFSET_ID_PARAM_CARTE_AIG,
    VERSION_SOFT_INFRA_AIGUILLE,
};




////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_Aiguille" et datas associees
uCAN1_MSG mc_InfraAIG_Aiguille = {
    {MC_OFFSET_ID_INFRA_AIG,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_OFFSET_DLC_INFRA_AIG,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraAIG_typeData = {
    MC_OFFSET_ID_INFRA_AIG,
    STATUS_MC_AIG_TYPEDATA,
};

MC_Data8 cdmc_InfraAIG_position = {
    MC_OFFSET_ID_INFRA_AIG,
    STATUS_MC_AIG_POSITION,
};

MC_Data8 cdmc_InfraAIG_lock_or_CRO = {
    MC_OFFSET_ID_INFRA_AIG,
    STATUS_MC_AIG_LOCK_OR_CRO,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_feu_A" et datas associees
uCAN1_MSG mc_InfraAIG_feu_A = {
    {MC_OFFSET_ID_FEUA_AIG,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_FEUA_AIG,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraAIG_typeData_Feu_A = {
    MC_OFFSET_ID_FEUA_AIG,
    STATUS_MC_FEUA_AIG,
};

MC_Data8 cdmc_InfraAIG_couleur_Feu_A = {
    MC_OFFSET_ID_FEUA_AIG,
    COULEUR_FEUA_AIG,
};

MC_Data8 cdmc_InfraAIG_status_Feu_A = {
    MC_OFFSET_ID_FEUA_AIG,
    STATUS_FEUA_AIG,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_feu_B" et datas associees
uCAN1_MSG mc_InfraAIG_feu_B = {
    {MC_OFFSET_ID_FEUB_AIG,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_FEUB_AIG,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraAIG_typeData_Feu_B = {
    MC_OFFSET_ID_FEUB_AIG,
    STATUS_MC_FEUB_AIG,
};

MC_Data8 cdmc_InfraAIG_couleur_Feu_B = {
    MC_OFFSET_ID_FEUB_AIG,
    COULEUR_FEUB_AIG,
};

MC_Data8 cdmc_InfraAIG_status_Feu_B = {
    MC_OFFSET_ID_FEUB_AIG,
    STATUS_FEUB_AIG,
};






////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_capteurPositionA" et datas associees
uCAN1_MSG mc_InfraAIG_capteurPositionA = {
    {MC_OFFSET_ID_AIG_POSITION_A,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_OFFSET_DLC_AIG_POSITION_A,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraAIG_typeData_CapteurA = {
    MC_OFFSET_ID_AIG_POSITION_A,
    STATUS_DATA_CAPTEUR_AIG_POSITION_AandB,
};

MC_Data8 cdmc_InfraAIG_etat_CapteurA = {
    MC_OFFSET_ID_AIG_POSITION_A,
    ETAT_CAPTEUR_AIG_POSITION_AandB,
};

MC_Data8 cdmc_InfraAIG_status_CapteurA = {
    MC_OFFSET_ID_AIG_POSITION_A,
    STATUS_CAPTEUR_AIG_POSITION_AandB,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_capteurPositionA" et datas associees
uCAN1_MSG mc_InfraAIG_capteurPositionB = {
    {MC_OFFSET_ID_AIG_POSITION_B,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_OFFSET_DLC_AIG_POSITION_B,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraAIG_typeData_CapteurB = {
    MC_OFFSET_ID_AIG_POSITION_B,
    STATUS_DATA_CAPTEUR_AIG_POSITION_AandB,
};

MC_Data8 cdmc_InfraAIG_etat_CapteurB = {
    MC_OFFSET_ID_AIG_POSITION_B,
    ETAT_CAPTEUR_AIG_POSITION_AandB,
};

MC_Data8 cdmc_InfraAIG_status_CapteurB = {
    MC_OFFSET_ID_AIG_POSITION_B,
    STATUS_CAPTEUR_AIG_POSITION_AandB,
};






////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_energieA" et datas associes
uCAN1_MSG mc_InfraAIG_energieA = {
    {MC_OFFSET_ID_ENERGIE_A,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_OFFSET_DLC_ENERGIE_A,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_commande_EnergieA = {
    MC_OFFSET_ID_ENERGIE_A,
    0,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_energieB" et datas associes
uCAN1_MSG mc_InfraAIG_energieB = {
    {MC_OFFSET_ID_ENERGIE_B,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_OFFSET_DLC_ENERGIE_B,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_commande_EnergieB = {
    MC_OFFSET_ID_ENERGIE_B,
    0,
};







 ////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_statusDynamique" et datas associees
uCAN1_MSG mc_InfraAIG_statusDynamique = {
    {MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_STATUS_DYNAMIQUE_CARTE_AIG,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_InfraAIG_etatLedsBargraph = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
};

//Decomposition de "cdmc_InfraBAL_etatLedsBargraph" en bits distincts
MC_Bit bdmc_InfraAIG_CAN_TxErrorPassive = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
    ERROR_PASSIVE_CANTX_CARTE_AIG,
};

MC_Bit bdmc_InfraAIG_CAN_RxErrorPassive = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
    ERROR_PASSIVE_CANRX_CARTE_AIG,
};

MC_Bit bdmc_InfraAIG_Gripper = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
    BASCUL_AIG_DURDUR,
};

MC_Bit bdmc_InfraAIG_secu = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
    AIG_SECU,
};

MC_Bit bdmc_InfraAIG_defEEPROM = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
    FAIL_EEPROM_CARTE_AIG,
};

MC_Bit bdmc_InfraAIG_def1TrameErronee = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
     DEF1_CARTE_AIG,
};

MC_Bit bdmc_InfraAIG_def2 = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
    DEF2_CARTE_AIG,
};

MC_Bit bdmc_panneAig = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LEDS_BARGRAPH_AIG,
    DEF3_CARTE_AIG,
};

////Autre datas de la trame "mc_InfraAIG_statusDynamique"
//MC_Data8 cdmc_InfraAIG_status_Aig = {
//    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
//    AIG_STATUS,
//};
//
////Decomposition de "cdmc_InfraAIG_status_Aig" en bits distincts
//MC_Bit bdmc_Aig_Locked = {
//    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
//    AIG_STATUS,
//    AIG_LOCKED,
//};
//
//MC_Bit bdmc_modeAutoLockAig = {
//    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
//    AIG_STATUS,
//    AIG_MODE_AUTO_LOCKED,
//};

//Autre datas de la trame "mc_InfraAIG_statusDynamique"
MC_Data8 cdmc_cptBascul_Aig_complique = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    CPT_BASCUL_DURDUR,
};

MC_Data8 cdmc_InfraAIG_cptTrameErronee = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    CPT_AIG_BAD_TRAMES,
};

MC_Data8 cdmc_InfraAIG_cptTxCAN_Error = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    CPT_AIG_TX_CAN_ERROR,
};

MC_Data8 cdmc_InfraAIG_cptRxCAN_Error = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    CPT_AIG_RX_CAN_ERROR,
};

MC_Data16 wdmc_InfraAIG_ID_TrameErronee = {
    MC_OFFSET_ID_STATUS_DYNAMIQUE_AIG,
    LAST_ID_TRAME_ERRONE,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_InfraAIG_EEPROM" et datas associees
uCAN1_MSG mc_InfraAIG_EEPROM = {
    {MC_OFFSET_ID_AIG_EEPROM,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_AIG_EEPROM,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_InfraAIG_commande_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    COMMANDE_EEPROM,
};
MC_Data16 wdmc_InfraAIG_offset_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    OFFSET_EEPROM,
};
MC_Data8 cdmc_InfraAIG_data1_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    DATA1EEPROM,
};
MC_Data8 cdmc_InfraAIG_data2_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    DATA2EEPROM,
};
MC_Data8 cdmc_InfraAIG_data3_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    DATA3EEPROM,
};
MC_Data8 cdmc_InfraAIG_data4_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    DATA4EEPROM,
};
MC_Data8 cdmc_InfraAIG_data5_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    DATA5EEPROM,
};
MC_Data8 cdmc_InfraAIG_data6_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    DATA6EEPROM,
};
MC_Data8 cdmc_InfraAIG_data7_EEPROM = {
    MC_OFFSET_ID_AIG_EEPROM,
    DATA7EEPROM,
};





////////////////////////////////////////////////////////////////////////////////
//  COMMUN AUX CARTES INFRA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_Infra_crash" et datas associes
uCAN1_MSG mc_Infra_crash = {
    {MC_ID_CRASH_INFRA,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_INFRA_CRASH,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_InfraCrash_source = {
    MC_ID_CRASH_INFRA,
    SOURCE_CRASH_INFRA,
};
MC_Data8 cdmc_InfraCrash_type = {
    MC_ID_CRASH_INFRA,
    TYPE_CRASH_INFRA,
};
MC_Data8 cdmc_InfraCrash_RC = {
    MC_ID_CRASH_INFRA,
    NUMERO_RC_CRASH_INFRA,
};
MC_Data8 cdmc_InfraCrash_code = {
    MC_ID_CRASH_INFRA,
    CODE_CRASH_INFRA,
};



 ////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_Infra_warning" et datas associes
uCAN1_MSG mc_Infra_warning = {
    {MC_ID_WARNING_INFRA,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_INFRA_WARNING,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_InfraWarning_source = {
    MC_ID_WARNING_INFRA,
    SOURCE_WARNING_INFRA,
};
MC_Data8 cdmc_InfraWarning_type = {
    MC_ID_WARNING_INFRA,
    TYPE_WARNING_INFRA,
};
MC_Data8 cdmc_InfraWarning_RC = {
    MC_ID_WARNING_INFRA,
    NUMERO_RC_WARNING_INFRA,
};
MC_Data8 cdmc_InfraWarning_code = {
    MC_ID_WARNING_INFRA,
    CODE_WARNING_INFRA,
};




////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_alimentationRails" et datas associes

uCAN1_MSG mc_alimentationRails = {
    {MC_ID_MODE_ALIM_RAILS,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_MODE_ALIM_RAILS,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_typeCommande_AlimentationRails = {
    MC_ID_MODE_ALIM_RAILS,
    INDICE_DATA_FOR_MODE_ALIM_RAILS,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_ledRouge_On_Tour" et datas associes

uCAN1_MSG mc_ledRouge_On_Tour = {
    {MC_ID_TOUR_LEDS,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_TOUR_LEDS,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_typeData_LedRouge_On_Tour = {
    MC_ID_TOUR_LEDS,
    TYPE_DATA_LED_ON_TOUR,
};

MC_Data8 cdmc_etat_LedRouge_On_Tour = {
    MC_ID_TOUR_LEDS,
    ETAT_DATA_LED_ON_TOUR,
};

MC_Data8 cdmc_status_LedRouge_On_Tour = {
    MC_ID_TOUR_LEDS,
    STATUS_DATA_LED_ON_TOUR,
};







