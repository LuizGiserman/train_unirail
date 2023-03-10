#ifndef API_UNIRAIL
	#define API_UNIRAIL
#include <stdlib.h>
#include <sys/stat.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "../CAN/canLinux.h"
#include "../CAN/MESCAN1_VarTrain.h"
#include "../CAN/MESCAN1_Utilitaire.h"
#include "../XBEE/xbee.h"
#include "GSM_R_message.h"
#include "EBT_message.h"
#include "ertms.h"

enum
{
    DriverID, ///< identifiant du driver
    NumeroCirculation, ///< le numéro de circulation : numéro de trajet
    PositionCourante, ///< le numéro du canton sur lequel se trouve le train
    NiveauERTMS, ///< le niveau de ERTMS utilisee
    IdTrain, ///< identifiant du train
    ClasseTrain, ///< classe du train
    LTrain, ///< longueur du train
    VitesseMaxTrain, ///< vitesse maximale du train
    BTSAdress, ///< Adresse par defaut du BTS
    CoefDec, ///< coefficient de deceleration
    CoefAccel, ///< Facteur de filtrage pour l'accélération
    VerboseLevel, ///< le ratio entre nb de trames envoyees et affichees par ecran
    ParametersNumber ///< le nombre de parametres
};

typedef enum Mode
{
    SB,	///<SB stand By
	SR,	///<SR Staff Responsible 
	FS,	///<FS Full Supervision 
	OS,	///<OS On Sight
	TR,	///<TR Trip
	PT,	///<PT Post Trip
	SF,	///<SF System Failure
	NP,	///<NP No Power
	LS	///<LS Limited Supervision 
}Mode;
// Mode modeTrain = SB;

/** Variable ERTMS **/
typedef struct ERTMSTrain
{
	int Driver_ID;
	int Train_Running_Number;
	int ERTMS_Level;// = 1;
	int Start;// = 0;
	int Stop;// = 0;
	int F_override;// = 0;
	int AckOnSight;// = 0; // 0 : non et 1 oui
	int AckSR;// = 0; // 0 : non et 1 oui
	int AckSB;// = 0; // 0 : non et 1 oui
}ERTMSTrain;

typedef struct TrainInfo
{
	float distance;  // en cm
	float distance_parcourue; // en cm
	float distance_2_balises_Init; // en cm
	float distance_restante; // en cm
	float vitesse_limit; // en cm/s
	float nouvelle_vitesse_alerte; // en cm/s
	float nouvelle_vitesse_urgence; // en cm/s
	float deceleration_alerte; // en cm/s2
	float deceleration_urgence; // en cm/s
	float vit_consigne;
	float vit_pilote;
	bool ctl_pilote;
	float vit_mesuree;
	int32_t nb_impulsions;
	int16_t BTSantennaAddress;
	int receivingGSMRtimeOut;	///<\todo initialiser
	int receivingEBTtimeOut;	///<\todo initialiser 
	Mode modeTrain;// = SB;
	double * parametres;
	struct ERTMSTrain ERTMSData;
}TrainInfo;

typedef struct BGInfo
{
	int E_NID_BG;
	int E_DIRECTION;
	int E_DISTANCE;
	int E_REACTION;
}BGInfo;

typedef struct BaliseInfo
{
	int Etat_Feux ;
	int Num_Balise ;
	BGInfo baliseGroup;
	int passagePremiereBalise;
	int Reception_balise;
	int GEO_REF ;
	int GEO_ORIENTATION ;
	int TSR;
	EBT_Message ERTMSBaliseData;
}BaliseInfo;

int checkPortNature(int fd);
void SendThroughCAN(uCAN1_MSG* headCanMsg, uint8_t* buffer);
void SendThroughTCP(uint8_t* buffer, uint16_t length, int socket);


void APISendCommunicationInitiationMessage(GSMR_CommunicationInitiationMessage* initCom, unsigned long long int timeStamp, TrainInfo* train1, uint8_t messTag, int fd);
void APISendSessionEstablishedMessage(GSMR_SessionEstablishedMessage* SessionEstablished, unsigned long long int timeStamp, TrainInfo* train1, uint8_t messTag, int fd);
void APISendValidatedTrainDataMessage(GSMR_ValidatedTrainDataMessage* valData, GSMR_PositionReportPacket* posReport, GSMR_ValidatedTrainDataPacket* dataPacket, BaliseInfo* baliseActuelle, TrainInfo* train1, GSMR_RBCSystemVersionMessage* RBCInfo, unsigned long long int timeStamp, uint8_t messTag, int fd);
void APISendMARequestMessage(GSMR_MARequestMessage* MARequest, GSMR_PositionReportPacket* posReport, BaliseInfo* baliseActuelle, TrainInfo* train1, GSMR_RBCSystemVersionMessage* RBCInfo, uint8_t qReason, unsigned long long int timeStamp, uint8_t messTag, int fd);
void APISendRBCSystemVersionMessage(GSMR_RBCSystemVersionMessage* RBCInfo, unsigned int timeStamp, GSMR_nid_lrbg baliseTag, uint8_t systemVersion, uint8_t messTag, int destAddress, int fd);
void APISendACKTrainDataMessage(GSMR_ACKTrainDataMessage* trainACK, unsigned int timeStamp, uint8_t M_ack, GSMR_nid_lrbg baliseTag, unsigned int timeStampTrain, uint8_t messTag, int destAddress, int fd);
void APISendLevel2_3MA_Message(GSMR_MovementAuthorityMessage* MA, unsigned int timeStamp, uint8_t M_ack, GSMR_nid_lrbg baliseTag, GSMR_Level2_3MovementAuthorityPacket packetnb15,
	uint8_t v_ema, uint16_t t_ema, GSMR_SectionDescription endsectiondescription, ERTMS_SectionTimer end, uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp,
	ERTMS_SectionTimer overlap, uint16_t d_startol, uint8_t v_releaseol, uint8_t messTag, int destAddress, int fd);

#endif