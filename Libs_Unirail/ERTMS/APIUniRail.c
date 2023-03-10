#include "APIUniRail.h"

int checkPortNature(int fd)
{
	struct stat portStat;
	int portState;
	portState = fstat(fd, &portStat);
	if (!portState)
	{
		int isSock = S_ISSOCK(portStat.st_mode), isChar = S_ISCHR(portStat.st_mode);
		if (portStat.st_dev && portStat.st_ino && portStat.st_rdev && portStat.st_nlink && !isSock && isChar)
			return 1;	///<Serial
		if (portStat.st_dev && portStat.st_ino && !portStat.st_rdev && portStat.st_nlink && isSock && !isChar)
		{
			int ret, val;
			unsigned int len;
			struct can_filter rfilter;
			ret = getsockopt(fd, SOL_CAN_RAW, CAN_RAW_FILTER , &rfilter, &len);
			if (!ret)
				return 2;	///<CAN
			ret = getsockopt(fd, SOL_SOCKET, SO_TYPE , &val, &len);
			if (!ret)
				return 3;	///<NETWORK
			return 0;	///<UNKNOWN
		}
		return 0;	///<UNKNOWN
	}
	else
		return -1;	///<ERROR
}

void SendThroughCAN(uCAN1_MSG* headCanMsg, uint8_t* buffer)
{
	bool flowCtl;
	uCAN1_MSG sendCAN;
	uint8_t length = headCanMsg->frame.data0+1;
	flowCtl = canLinux_transmit(CANLINUX_PRIORITY_HIGH, headCanMsg);
	while (!flowCtl)
	{
		usleep(1000);
		flowCtl = canLinux_transmit(CANLINUX_PRIORITY_HIGH, headCanMsg);
	}
	bool exitCondition = false;
	do
	{
		exitCondition = MESCAN_sliceArray(&sendCAN, buffer, headCanMsg->frame.id, length, CAN1_MSG_DATA);
		flowCtl = canLinux_transmit(CANLINUX_PRIORITY_MEDIUM, &sendCAN);
		while (!flowCtl)
		{
			usleep(1000);
			flowCtl = canLinux_transmit(CANLINUX_PRIORITY_MEDIUM, &sendCAN);
		}
	}
	while(exitCondition == false);
}

void SendThroughTCP(uint8_t* buffer, uint16_t length, int socket)
{
	send(socket, buffer, length, 0);
}

void APISendCommunicationInitiationMessage(GSMR_CommunicationInitiationMessage* initCom, unsigned long long int timeStamp, TrainInfo* train1, uint8_t messTag, int fd)
{
	uint8_t tableau[30], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	int portType;
	initGSMR_CommunicationInitiationMessage(initCom, timeStamp, train1->parametres[IdTrain]);
	serializeMessage (initCom, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, initCom->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, initCom->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, initCom->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, initCom->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}
void APISendSessionEstablishedMessage(GSMR_SessionEstablishedMessage* SessionEstablished, unsigned long long int timeStamp, TrainInfo* train1, uint8_t messTag, int fd)
{
	uint8_t tableau[30], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	int portType;
	initGSMR_SessionEstablishedMessage(SessionEstablished, timeStamp, train1->parametres[IdTrain]);
	serializeMessage (SessionEstablished, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, SessionEstablished->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, SessionEstablished->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, SessionEstablished->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, SessionEstablished->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}	

void APISendValidatedTrainDataMessage(GSMR_ValidatedTrainDataMessage* valData, GSMR_PositionReportPacket* posReport, GSMR_ValidatedTrainDataPacket* dataPacket, BaliseInfo* baliseActuelle, TrainInfo* train1, GSMR_RBCSystemVersionMessage* RBCInfo, unsigned long long int timeStamp, uint8_t messTag, int fd)
{
	uint8_t tableau[100], cks;
	char destAddr[2];
	uCAN1_MSG envCanMsg;
	GSMR_nid_lrbg firstBalise;
	GSMR_engine_identifier identMotor[32];
	uint8_t systNat[32];
	identMotor[0].m_voltage = 1;
	identMotor[0].nid_ctraction = 7;
	
	firstBalise.nid_c = RBCInfo->nid_lrbg.nid_c;
	firstBalise.nid_bg = RBCInfo->nid_lrbg.nid_bg;
	
	int portType;
	initGSMR_PositionReportPacket(posReport, 0, firstBalise, train1->distance_parcourue, 0, 0, 2, 2, 1, (int)train1->parametres[LTrain], train1->vit_mesuree, 0, train1->modeTrain, (int)train1->parametres[NiveauERTMS], 0);
	initGSMR_ValidatedTrainDataPacket(dataPacket, 0, 2, (int)train1->parametres[LTrain], (int)train1->parametres[VitesseMaxTrain], 1, 0, 0, 8, 1, identMotor, 0, systNat);
	initGSMR_ValidatedTrainDataMessage(valData, timeStamp, train1->parametres[IdTrain], posReport, *dataPacket);
	serializeMessage (valData, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, valData->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, valData->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, valData->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, valData->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendMARequestMessage(GSMR_MARequestMessage* MARequest, GSMR_PositionReportPacket* posReport, BaliseInfo* baliseActuelle, TrainInfo* train1, GSMR_RBCSystemVersionMessage* RBCInfo, uint8_t qReason, unsigned long long int timeStamp, uint8_t messTag, int fd)
{
	char destAddr[2];
	uint8_t tableau[100], cks;
	uCAN1_MSG envCanMsg;
	GSMR_nid_lrbg firstBalise;
	firstBalise.nid_c = RBCInfo->nid_lrbg.nid_c;
	firstBalise.nid_bg = RBCInfo->nid_lrbg.nid_bg;
	
	int portType;
	initGSMR_PositionReportPacket(posReport, 0, firstBalise, train1->distance_parcourue, 0, 0, 2, 2, 1, (int)train1->parametres[LTrain], train1->vit_mesuree, 0, train1->modeTrain, (int)train1->parametres[NiveauERTMS], 0);
	initGSMR_MARequestMessage(MARequest, timeStamp, train1->parametres[IdTrain], qReason, posReport);
	serializeMessage (MARequest, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= train1->BTSantennaAddress>>8&0xFF;
		destAddr[1]= train1->BTSantennaAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, MARequest->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, MARequest->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, train1->BTSantennaAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, MARequest->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, MARequest->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendRBCSystemVersionMessage(GSMR_RBCSystemVersionMessage* RBCInfo, unsigned int timeStamp, GSMR_nid_lrbg baliseTag, uint8_t systemVersion, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[30], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_RBCSystemVersionMessage(RBCInfo, timeStamp , 1, baliseTag, systemVersion);
	serializeMessage (RBCInfo, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, RBCInfo->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, RBCInfo->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, RBCInfo->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, RBCInfo->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendACKTrainDataMessage(GSMR_ACKTrainDataMessage* trainACK, unsigned int timeStamp, uint8_t M_ack, GSMR_nid_lrbg baliseTag, unsigned int timeStampTrain, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[30], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	initGSMR_ACKTrainDataMessage(trainACK, timeStamp, M_ack, baliseTag, timeStampTrain);
	serializeMessage (trainACK, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, trainACK->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, trainACK->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, trainACK->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, trainACK->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}

void APISendLevel2_3MA_Message(GSMR_MovementAuthorityMessage* MA, unsigned int timeStamp, uint8_t M_ack, GSMR_nid_lrbg baliseTag, GSMR_Level2_3MovementAuthorityPacket packetnb15,
	uint8_t v_ema, uint16_t t_ema, GSMR_SectionDescription endsectiondescription, ERTMS_SectionTimer end, uint8_t q_dangerpoint, uint16_t d_dp, uint8_t v_releasedp,
	ERTMS_SectionTimer overlap, uint16_t d_startol, uint8_t v_releaseol, uint8_t messTag, int destAddress, int fd)
{
	char destAddr[2];
	uint8_t tableau[270], cks;
	uCAN1_MSG envCanMsg;

	int portType;
	GSMR_SectionDescription sectiondescription[32];
	initGSMR_Level2_3MovementAuthorityPacket(&packetnb15, 0, 0, v_ema, t_ema, 0, sectiondescription, endsectiondescription,  end, q_dangerpoint, d_dp, v_releasedp, overlap, d_startol,	v_releaseol);
	initGSMR_MovementAuthorityMessage(MA, timeStamp, M_ack, baliseTag, packetnb15);
	serializeMessage (MA, tableau);
	portType = checkPortNature(fd);
	switch (portType)
	{
	case 1:
		destAddr[0]= destAddress>>8&0xFF;
		destAddr[1]= destAddress&0xFF;
        PortXbee_envoyer(destAddr, tableau, MA->l_message+1, fd, TX_REQUEST_16BITS_ADR, messTag, 0x00);
		break;
	case 2:
		envCanMsg.frame.id = MC_ID_MESSAGE_GSM_SENT;
		envCanMsg.frame.dlc = MC_DLC_MESSAGE_GSM_SENT;
		envCanMsg.frame.data5 = 0;
		envCanMsg.frame.data6 = 0;
		envCanMsg.frame.data7 = 0;
		MESCAN_SetData8(&envCanMsg, cdmc_lenMessageSent, MA->l_message);
		MESCAN_SetData16(&envCanMsg, wdmc_destAdressMessageSent, destAddress);
		MESCAN_SetData8(&envCanMsg, cdmc_frameId_NumMessage, messTag);
		cks =  (MESCAN_generateChecksum(tableau, MA->l_message+1) + envCanMsg.frame.data2 + envCanMsg.frame.data3 + envCanMsg.frame.data4) &0xFF;
		MESCAN_SetData8(&envCanMsg, cdmc_customCKS_MessageSent, cks);
		SendThroughCAN(&envCanMsg, tableau);
		break;
	case 3:
		SendThroughTCP(tableau, MA->l_message+1,fd);
		break;
	default:
		printf("Not implemented or error port type %d\n", portType);
	}
}