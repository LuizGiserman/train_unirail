#ifndef ERTMS_H
	#define ERTMS_H
#define DEBUG
#include <stdio.h>
#include "GSM_R_message.h"
#include "EBT_message.h"

/// Facteur d'echelle pour les distances (par rapport aux valeurs de Q_SCALE de ERTMS-> pour une echelle de 1/500 cela donne: (rappel: echelle O=(~1/50))
/**
    <table>
    <caption id="Transformation d'echelles">Transformation des echelles selon le facteur d'echelles</caption>
    <tr><th>Valeur Q_SCALE 		<th>0 		<th>1 		<th>2  		<th>3
    <tr><td>Echelle ERTMS 		<td>10cm	<td>1m 		<td>10m 	<td>spare
    <tr><td>Echelle transformee <td>0.2mm	<td>2mm		<td>2cm		<td>spare
    </table>
	Cela s'applique aussi aux longueurs des trains, ou la resolution passe de 1m a 2cm, et L_DOUBTOVER et L_DOUBTUNDER qui sont affectes par Q_SCALE
 */
#define SCALE_FACTOR_DISTANCE 0.002 

/// Facteur d'echelle pour le temps (qui affecte aux resolutions de T_TRAIN, T_SECTIONTIMER et avec SCALE_FACTOR_DISTANCE, aux vitesses -> pour une echelle 0.28 cela donne:
/**
    <table>
    <caption id="Transformation de temps">Transformation des temps et vitesses selon le facteur</caption>
    <tr><th>Variables	 			<th>T_TRAIN 		<th>T_SECTIONTIMER et timeouts	<th>V_MAXTRAIN et autre vitesses
    <tr><td>Resolution ERTMS 		<td>10ms			<td>1s 							<td>5km/h						
    <tr><td>Resolution transformee 	<td>2.8ms	 		<td>0.28s						<td>0.99cm/s
    </table>
 */
#define SCALE_FACTOR_TIME 0.277

/// Fonction d'initialisation du packet EBT_Level1MovementAuthority.
/**
nid_packet(12), q_dir(1) et l_packet(17-258) sont remplies automatiquement.
 */
void initEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* pointer, uint8_t q_scale, uint8_t v_main, uint8_t v_ema, uint16_t t_ema,
	uint8_t n_iter_sections, GSMR_SectionDescription section[32], GSMR_SectionDescription endsection, ERTMS_SectionTimer end,
	uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp, ERTMS_SectionTimer overlap, uint16_t d_startol, uint8_t v_releaseol);
	
/// Fonction d'initialisation du packet EBT_LevelTransitionOrder.
/**
nid_packet(41), q_dir(1) et l_packet(12-257) sont remplies automatiquement.
 */
void initEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* pointer, uint8_t q_scale, uint16_t d_leveltr,
	uint8_t m_leveltr, uint8_t nid_ntc, uint16_t l_ackleveltr, uint8_t n_iter_next, uint8_t m_leveltr_next[8], 
	uint8_t nid_ntc_next[8], uint16_t l_ackleveltr_next[8]);
	
/// Fonction d'initialisation du packet GSMR_PositionReportPacket.
/**
nid_packet(0) et l_packet(24) sont remplies automatiquement.
 */
void initGSMR_PositionReportPacket(GSMR_PositionReportPacket* pointer, uint8_t q_scale, GSMR_nid_lrbg nid_lrbg, int16_t d_lrbg,
	uint8_t q_dirlrbg, uint8_t q_dlrbg, uint16_t l_doubtover, uint16_t l_doubtunder, uint8_t q_length, uint16_t l_traininit,
	uint8_t v_train, uint8_t q_dirtrain, uint8_t m_mode, uint8_t m_level, uint8_t nid_ntc);
	
/// Fonction d'initialisation du packet GSMR_PositionReportPacketTwoBaliseGroups.
/**
nid_packet(1) et l_packet(28) sont remplies automatiquement.
 */
void initGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* pointer, uint8_t q_scale, GSMR_nid_lrbg nid_lrbg, 
	GSMR_nid_lrbg nid_prvlrbg, uint16_t d_lrbg, uint8_t q_dirlrbg, uint8_t q_dlrbg, uint16_t l_doubtover, uint16_t l_doubtunder,
	uint8_t q_length, uint16_t l_traininit, uint8_t v_train, uint8_t q_dirtrain, uint8_t m_mode, uint8_t m_level, uint8_t nid_ntc);

/// Fonction d'initialisation du packet GSMR_ValidatedTrainDataPacket.
/**
nid_packet(11) et l_packet(16-144) sont remplies automatiquement.
 */
void initGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* pointer, uint8_t nc_cdtrain, uint16_t nc_train, 
	uint16_t l_train, uint8_t v_maxtrain, uint8_t m_loadinggauge, uint8_t m_axleloadcat, uint8_t m_airtight, uint16_t n_axle,
	uint8_t n_iter_engine, GSMR_engine_identifier engine_identifier[32], uint8_t n_iter_ntc, uint8_t nid_ntc[32]);

/// Fonction d'initialisation du packet GSMR_Level2_3MovementAuthorityPacket.
/**
nid_packet(15) et l_packet(33-257) sont remplies automatiquement.
 */
void initGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* pointer, uint8_t q_dir,	uint8_t q_scale,
	uint8_t v_ema, uint16_t t_ema, uint8_t n_iter_section, GSMR_SectionDescription section[32], GSMR_SectionDescription endsection,
	ERTMS_SectionTimer end, uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp, ERTMS_SectionTimer overlap, uint16_t d_startol,
	uint8_t v_releaseol);

/// Fonction d'initialisation d'un EBT_Message.
/**
q_updown(1) et q_media(0) sont remplies automatiquement (pas de support format EuroLoop).
packetPointer doit etre du type:EBT_Level1MovementAuthority, EBT_RepositioningInformation, EBT_LevelTransitionOrder ou EBT_NationalValues
 */
void initEBT(EBT_Message* pointer, uint8_t m_version, uint8_t n_pig, uint8_t n_total, uint8_t m_dup,
	uint8_t m_mcount, GSMR_nid_lrbg nid_lrbg, uint8_t q_link, void* packetPointer);

/// Fonction d'initialisation du message GSMR_CommunicationInitiationMessage.
/**
nid_message(15) et l_message(8) sont remplies automatiquement.
 */
void initGSMR_CommunicationInitiationMessage(GSMR_CommunicationInitiationMessage* pointer, uint32_t timeStamp, uint8_t nidEngine);

/// Fonction d'initialisation du message GSMR_RBCSystemVersionMessage.
/**
nid_message(32) et l_message(13) sont remplies automatiquement.
 */
void initGSMR_RBCSystemVersionMessage(GSMR_RBCSystemVersionMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint8_t m_version);

/// Fonction d'initialisation du message GSMR_SessionEstablishedMessage.
/**
nid_message(159) et l_message(8) sont remplies automatiquement.
 */
void initGSMR_SessionEstablishedMessage(GSMR_SessionEstablishedMessage* pointer, uint32_t timeStamp, uint8_t nidEngine);

/// Fonction d'initialisation du message GSMR_ValidatedTrainDataMessage.
/**
nid_message(129) et l_message(45-180) sont remplies automatiquement.
packetPointer doit etre du type:GSMR_PositionReportPacket ou GSMR_PositionReportPacketTwoBaliseGroups
 */
void initGSMR_ValidatedTrainDataMessage(GSMR_ValidatedTrainDataMessage* pointer, uint32_t timeStamp, uint8_t nidEngine, void* packetPointer, GSMR_ValidatedTrainDataPacket packetNb11);

/// Fonction d'initialisation du message GSMR_ACKTrainDataMessage.
/**
nid_message(32) et l_message(13) sont remplies automatiquement.
 */
void initGSMR_ACKTrainDataMessage(GSMR_ACKTrainDataMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint32_t firstTimeStamp);

/// Fonction d'initialisation du message GSMR_MARequestMessage.
/**
nid_message(132) et l_message(33-37) sont remplies automatiquement.
packetPointer doit etre du type:GSMR_PositionReportPacket ou GSMR_PositionReportPacketTwoBaliseGroups
 */
void initGSMR_MARequestMessage(GSMR_MARequestMessage* pointer, uint32_t timeStamp, uint8_t nidEngine, uint8_t q_marqstreason, void* packetPointer);

/// Fonction d'initialisation du message GSMR_MovementAuthorityMessage.
/**
nid_message(3) et l_message(27-269) sont remplies automatiquement.
 */
void initGSMR_MovementAuthorityMessage(GSMR_MovementAuthorityMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, GSMR_Level2_3MovementAuthorityPacket packetnb15);

/// Fonction d'initialisation du message GSMR_SRAuthorisationMessage.
/**
nid_message(2) et l_message(15) sont remplies automatiquement.
 */
void initGSMR_SRAuthorisationMessage(GSMR_SRAuthorisationMessage* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg, uint8_t q_scale, uint16_t d_sr);

/// Fonction d'initialisation du message GSMR_Acknowledgment.
/**
nid_message(146) et l_message(12) sont remplies automatiquement.
 */
void initGSMR_Acknowledgment(GSMR_Acknowledgment* pointer, uint32_t timeStamp, uint8_t nidEngine, uint32_t firstTimeStamp);

/// Fonction d'initialisation du message GSMR_EndOfMission.
/**
nid_message(150) et l_message(29-36) sont remplies automatiquement.
packetPointer doit etre du type:GSMR_PositionReportPacket ou GSMR_PositionReportPacketTwoBaliseGroups
 */
void initGSMR_EndOfMission(GSMR_EndOfMission* pointer, uint32_t timeStamp, uint8_t nidEngine, void* packetPointer);

/// Fonction d'initialisation du message GSMR_AckTerminationCommunicationSession.
/**
nid_message(39) et l_message(12) sont remplies automatiquement.
 */
void initGSMR_AckTerminationCommunicationSession(GSMR_AckTerminationCommunicationSession* pointer, uint32_t timeStamp, uint8_t m_ack, GSMR_nid_lrbg nid_lrbg);

//outils
/// Fonction de serialisation EBT_Message.
/**
La trame finit par 0xFF (255)
 */
int serializeEBT (EBT_Message* messagePointer, uint8_t* buffer);
/// Fonction de serialisation GSMR_Message.
/**
La trame finit par 0xFF (255)
 */
int serializeMessage (void* messagePointer, uint8_t* buffer);

uint16_t serializeUint16(uint16_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeUint32(uint32_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_PositionReportPacket(GSMR_PositionReportPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t serializeGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* dataPointer, uint8_t* buffer, uint16_t counter);


int deSerializeEBT (EBT_Message* messagePointer, uint8_t* buffer);
int deserializeMessage(uint8_t* buffer, uint8_t messNb, void* messagePointer);

uint16_t deSerializeUint16(uint16_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeUint32(uint32_t* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeEBT_Level1MovementAuthority(EBT_Level1MovementAuthority* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeEBT_LevelTransitionOrder(EBT_LevelTransitionOrder* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_PositionReportPacketTwoBaliseGroups(GSMR_PositionReportPacketTwoBaliseGroups* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_PositionReportPacket(GSMR_PositionReportPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_ValidatedTrainDataPacket(GSMR_ValidatedTrainDataPacket* dataPointer, uint8_t* buffer, uint16_t counter);
uint16_t deSerializeGSMR_Level2_3MovementAuthorityPacket(GSMR_Level2_3MovementAuthorityPacket* dataPointer, uint8_t* buffer, uint16_t counter);


// API

#endif
	
