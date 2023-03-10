#include "canLinux.h"

#if MC802 ==0

struct CanBufferPrio buffer;
pthread_mutex_t fifo_can_lock;

void *task_send (void* pdata)
{
	int nbytes, i;
	static struct can_frame frameT;
	static bool resend = false;
	uCAN1_MSG sendCanMsg;
	while(1)
	{
		pthread_mutex_lock(&fifo_can_lock);
		if(resend)
		{
			nbytes = write(buffer.canPort, &frameT, sizeof(struct can_frame));
			if (nbytes == sizeof(struct can_frame)) 
				resend = false;
		}
		else if (!MESCAN_isFileVide(&buffer.fileHigh) || !MESCAN_isFileVide(&buffer.fileMedium) || !MESCAN_isFileVide(&buffer.fileLow) || !MESCAN_isFileVide(&buffer.fileNone))
		{
			if (!MESCAN_isFileVide(&buffer.fileHigh))
				MESCAN_defiler(&buffer.fileHigh, &sendCanMsg);
			else if (!MESCAN_isFileVide(&buffer.fileMedium))
				MESCAN_defiler(&buffer.fileMedium, &sendCanMsg);
			else if (!MESCAN_isFileVide(&buffer.fileLow))
				MESCAN_defiler(&buffer.fileLow, &sendCanMsg);
			else if (!MESCAN_isFileVide(&buffer.fileNone))
				MESCAN_defiler(&buffer.fileNone, &sendCanMsg);
		
			if (CAN1_MSG_RTR == sendCanMsg.frame.idType)	///Remote CAN frame
				frameT.can_id = sendCanMsg.frame.id | CAN_RTR_FLAG ;
			else if (CAN1_FRAME_EXT == sendCanMsg.frame.idType)
				frameT.can_id = sendCanMsg.frame.id | CAN_EFF_FLAG ;	///Extended CAN frame
			else
				frameT.can_id = sendCanMsg.frame.id;	///Standard CAN frame
			frameT.can_dlc = sendCanMsg.frame.dlc;
			for (i=0;i<sendCanMsg.frame.dlc;i++)
				frameT.data[i] = sendCanMsg.array[i + OFFSET_DATA0_TO_7];

			nbytes = write(buffer.canPort, &frameT, sizeof(struct can_frame));
			if (nbytes != sizeof(struct can_frame))
			{
#ifdef VERBOSE
				printf("Error writing message, retrying\n");
#endif
				resend = true;
			}
		}
		pthread_mutex_unlock(&fifo_can_lock);
		usleep(500);
	}
	return NULL;

}

int canLinux_Init (char *portName)
{
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;
	char *ifname = portName;
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{
		perror("Error while opening socket");
	}
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	#ifdef VERBOSE
		printf("%s at index %d\n", ifname, ifr.ifr_ifindex);
	#endif
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Error in socket bind");
	}
	return s;
}

int canLinux_init_prio (char *portName)
{
	if (buffer.running)
	{
		return (buffer.canPort);
	}
	else
	{
		int s;
		struct sockaddr_can addr;
		struct ifreq ifr;
		char *ifname = portName;
		MESCAN_InitFIFO (&buffer.fileHigh);
		MESCAN_InitFIFO (&buffer.fileMedium);
		MESCAN_InitFIFO (&buffer.fileLow);
		MESCAN_InitFIFO (&buffer.fileNone);
		buffer.running = true;

		if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
		{
			perror("Error while opening socket");
		}
		strcpy(ifr.ifr_name, ifname);
		ioctl(s, SIOCGIFINDEX, &ifr);
		addr.can_family  = AF_CAN;
		addr.can_ifindex = ifr.ifr_ifindex;
		#ifdef VERBOSE
			printf("%s at index %d\n", ifname, ifr.ifr_ifindex);
		#endif
		if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			perror("Error in socket bind");
		}
		else
		{
			buffer.canPort = s;
			fcntl(buffer.canPort, F_SETFL, fcntl(buffer.canPort, F_GETFL) | O_NONBLOCK);
		}
		if(pthread_create(&threadSend, NULL, task_send, NULL)== -1)
		{
			perror("pthread_create Send");
			return EXIT_FAILURE;
		}
		return s;
	}
}

void canLinux_close (void)
{
	pthread_mutex_lock(&fifo_can_lock);
	if(buffer.running)
	{
		buffer.running = false;
		while (!(MESCAN_isFileVide(&buffer.fileHigh) && MESCAN_isFileVide(&buffer.fileMedium) && MESCAN_isFileVide(&buffer.fileLow) && MESCAN_isFileVide(&buffer.fileNone)))
		{
			pthread_mutex_unlock(&fifo_can_lock);
			usleep(1000);
			pthread_mutex_lock(&fifo_can_lock);
		}
		pthread_cancel(threadSend);
		pthread_mutex_destroy(&fifo_can_lock);
		close(buffer.canPort);
	}
#ifdef VERBOSE
	else
		printf("Error, port already closed\n");
#endif
}

bool ECAN1_transmit(int portCan, CANLINUX_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg) 
{
	int nbytes;
	bool messageSent = false;
	struct can_frame frameT;
	frameT.can_dlc = sendCanMsg->frame.dlc;
	frameT.data[0] = sendCanMsg->frame.data0;
	frameT.data[1] = sendCanMsg->frame.data1;
	frameT.data[2] = sendCanMsg->frame.data2;
	frameT.data[3] = sendCanMsg->frame.data3;
	frameT.data[4] = sendCanMsg->frame.data4;
	frameT.data[5] = sendCanMsg->frame.data5;
	frameT.data[6] = sendCanMsg->frame.data6;
	frameT.data[7] = sendCanMsg->frame.data7;
	nbytes = write(portCan, &frameT, sizeof(struct can_frame));
	if (nbytes == sizeof(struct can_frame))
		messageSent = true;
	return messageSent;
}

bool canLinux_transmit(CANLINUX_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg) 
{
	bool messageSent = false;

    if(!pthread_mutex_trylock(&fifo_can_lock))
		if (buffer.running)
		{
			if (priority == CANLINUX_PRIORITY_HIGH)
			{
				messageSent = MESCAN_enfiler(&buffer.fileHigh, *sendCanMsg);
			}	
			else if (priority == CANLINUX_PRIORITY_MEDIUM)
			{
				messageSent = MESCAN_enfiler(&buffer.fileMedium, *sendCanMsg );
			}
			else if (priority == CANLINUX_PRIORITY_LOW)
			{
				messageSent = MESCAN_enfiler(&buffer.fileLow, *sendCanMsg );
			}
			else
			{
				messageSent = MESCAN_enfiler(&buffer.fileNone, *sendCanMsg );
			}
		}
	pthread_mutex_unlock(&fifo_can_lock);

	return messageSent;
}

bool ECAN1_receive(int portCan, uCAN1_MSG *recCanMsg) 
{
	
	bool messageReceived = false;
	struct can_frame frameR;
	
	int nbytes = read(portCan,&frameR,sizeof(struct can_frame));
	if (nbytes >= sizeof(struct can_frame))
	{
		if (frameR.can_id & CAN_RTR_FLAG)	///Remote CAN frame
			recCanMsg->frame.msgtype = CAN1_MSG_RTR;
		else if (frameR.can_id & CAN_EFF_FLAG )
			recCanMsg->frame.msgtype = CAN1_FRAME_EXT;	///Extended CAN frame
		else
			recCanMsg->frame.msgtype = CAN1_MSG_DATA;	///Standard CAN frame
		
		if (frameR.can_id & CAN_EFF_FLAG )
			recCanMsg->frame.id = frameR.can_id & CAN_EFF_MASK ;
		else
			recCanMsg->frame.id = frameR.can_id & CAN_SFF_MASK ;
		recCanMsg->frame.dlc =  frameR.can_dlc;
		recCanMsg->frame.data0 = frameR.data[0];
		recCanMsg->frame.data1 = frameR.data[1];
		recCanMsg->frame.data2 = frameR.data[2];
		recCanMsg->frame.data3 = frameR.data[3];
		recCanMsg->frame.data4 = frameR.data[4];
		recCanMsg->frame.data5 = frameR.data[5];
		recCanMsg->frame.data6 = frameR.data[6];
		recCanMsg->frame.data7 = frameR.data[7];
		messageReceived=true;

	#ifdef VERBOSE
		printf("msgtype %i, ID %X, dlc %i data: %X %X %X %X %X %X %X %X\n", recCanMsg->frame.msgtype, recCanMsg->frame.id, recCanMsg->frame.dlc, recCanMsg->frame.data0, recCanMsg->frame.data1, recCanMsg->frame.data2, recCanMsg->frame.data3, recCanMsg->frame.data4, recCanMsg->frame.data5, recCanMsg->frame.data6, recCanMsg->frame.data7);
	#endif
	}
	return (messageReceived);
}

bool canLinux_receive(uCAN1_MSG *recCanMsg, unsigned int timeOut) 
{
	
	bool messageReceived = false;
	struct can_frame frameR;
    unsigned long ns, ns2; // Nanoseconds
    unsigned long s, s2; // Seconds
	unsigned long long ms, ms2;
    struct timespec spec;
	int i;
	clock_gettime(CLOCK_REALTIME, &spec);
	ns = spec.tv_nsec;
	s = spec.tv_sec;
	ms = s*1000 + ns/1e6;
	ms2 = ms;
	while ((ms2 - ms) < timeOut && !messageReceived)
	{
		int nbytes = read(buffer.canPort,&frameR,sizeof(struct can_frame));
		if (nbytes == sizeof(struct can_frame))
		{
			if (frameR.can_id & CAN_RTR_FLAG)	///Remote CAN frame
				recCanMsg->frame.msgtype = CAN1_MSG_RTR;
			else if (frameR.can_id & CAN_EFF_FLAG )
				recCanMsg->frame.msgtype = CAN1_FRAME_EXT;	///Extended CAN frame
			else
				recCanMsg->frame.msgtype = CAN1_MSG_DATA;	///Standard CAN frame
			
			if (frameR.can_id & CAN_EFF_FLAG )
				recCanMsg->frame.id = frameR.can_id & CAN_EFF_MASK ;
			else
				recCanMsg->frame.id = frameR.can_id & CAN_SFF_MASK ;
			recCanMsg->frame.dlc =  frameR.can_dlc;
			for (i=0;i<8;i++)
				recCanMsg->array[i + OFFSET_DATA0_TO_7] = frameR.data[i];
			messageReceived=true;

		#ifdef VERBOSE
			printf("msgtype %i, ID %X, dlc %i data: %X %X %X %X %X %X %X %X\n", recCanMsg->frame.msgtype, recCanMsg->frame.id, recCanMsg->frame.dlc, recCanMsg->frame.data0, recCanMsg->frame.data1, recCanMsg->frame.data2, recCanMsg->frame.data3, recCanMsg->frame.data4, recCanMsg->frame.data5, recCanMsg->frame.data6, recCanMsg->frame.data7);
		#endif
		}
		else
		{
			usleep(500);
			clock_gettime(CLOCK_REALTIME, &spec);
			ns2 = spec.tv_nsec;
			s2 = spec.tv_sec;
			ms2 = s2*1000 + ns2/1e6;
			
		}
	}
	return (messageReceived);
}

void canLinux_InitFilter (int portCan, struct can_filter* rfilter, int longueur)
{
	setsockopt(portCan, SOL_CAN_RAW, CAN_RAW_FILTER, rfilter, longueur); 
}

void canLinux_initFilter (struct can_filter* rfilter, int longueur)
{
	setsockopt(buffer.canPort, SOL_CAN_RAW, CAN_RAW_FILTER, rfilter, longueur); 
}

bool messageIsGSM_R_SENT(int IDunderTest)
{
	if ((IDunderTest >= MC_ID_MESSAGE_GSM_SENT) && (IDunderTest < (MC_ID_MESSAGE_GSM_SENT + 16)))
		return true;
	else
		return false;
}

bool messageIsGSM_R_RECEIVED(int IDunderTest)
{
	if ((IDunderTest >= MC_ID_MESSAGE_GSM_RECEIVED) && (IDunderTest < (MC_ID_MESSAGE_GSM_RECEIVED + 16)))
		return true;
	else
		return false;
}

bool messageIsEBT_L2(int IDunderTest)
{
	if (IDunderTest >= MC_ID_EBTL2_RECEIVED  && IDunderTest < MC_ID_SHADOWS_TRAME_CAN )	///<\todo C'est le premier ID apres 0x30, autrement cela peut aller jusqu'a 0x60. Cela permet 120 octets
		return true;
	else
		return false;
}


#endif


