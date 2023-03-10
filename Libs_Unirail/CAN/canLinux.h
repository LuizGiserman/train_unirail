#ifndef CANLINUX_H
	#define CANLINUX_H
#ifndef MC802
	#define MC802 1
#endif

#if MC802 ==0

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <unistd.h>
	#include <string.h>
	#include <time.h>
	
	#include <net/if.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <linux/sockios.h>
	#include <sys/fcntl.h>
	#include <pthread.h>
	#include <linux/can.h>
	#include <linux/can/raw.h>
	#include <errno.h>

	#include <netinet/in.h>
	#include <netdb.h>
	
	#include <arpa/inet.h>

#endif	

	#include "MESCAN1_VarTrain.h"
	// #undef TailleFIFO 
	// #define TailleFIFO 	30
	// #define VERBOSE
	
	///Niveau de priorite de la trame CAN, 0(bas) -> 3(elevee)
	typedef enum 
	{
		CANLINUX_PRIORITY_HIGH =   0b11,
		CANLINUX_PRIORITY_MEDIUM = 0b10,
		CANLINUX_PRIORITY_LOW =    0b01,
		CANLINUX_PRIORITY_NONE =   0b00
	} CANLINUX_TX_PRIOIRTY;
	
	typedef struct CanBufferPrio
	{
		iFILE_MesCAN fileHigh;
		iFILE_MesCAN fileMedium;
		iFILE_MesCAN fileLow;
		iFILE_MesCAN fileNone;
		int canPort;
		bool running;
	}CanBufferPrio;
#if MC802 ==0
	pthread_t threadSend;
	///Tache pour l'envoi de messages CAN. Interroge les FIFOs dans l'ordre de priorite tous les 500 us, et envoi dans le buffer de sortie.
	/**Une fois le message depile pour envoi, il reste en memoire en cas d'echec de transmission et il y a une tentative de renvoi toutes les 500us*/
	void *task_send (void *p_data);
	
	///Initialisation du CAN (#define VERBOSE contrôle la sortie de messages par console)<BR> retourne l'index du bus a utiliser par la suite.
	int canLinux_Init (char *portName)__attribute__((deprecated("This fuction is deprecated. Please use canLinux_init_prio instead")));
	
	///Initialisation du CAN (#define VERBOSE controle la sortie de messages par console), ainsi que les fifos de transmission. Enregistre egalement en interne le port CAN.<BR> retourne l'index du bus a utiliser par la suite pour des operations sur le socket.
	int canLinux_init_prio (char *portName);
	
	///Ferme l'acces aux FIFO pour l'envoi des nouveaux messages, attend qu'elles soient vides, puis detruit le thread d'envoi et ferme le port.
	void canLinux_close ();
	///Initialisation d'un filtre de trames par ID
	// struct can_filter {
	// 	canid_t can_id;
	// 	canid_t can_mask;
	// };
	/*longueur max: 512 (limite de la lib)*/
		
	void canLinux_InitFilter (int portCan, struct can_filter* rfilter, int longueur)__attribute__((deprecated("This fuction is deprecated. Please use canLinux_initFilter instead")));
	///Initialisation d'un filtre de trames par ID
	/**struct can_filter {
		canid_t can_id;
		canid_t can_mask;
	};
	longueur max: 512 (limite de la lib)*/
	void canLinux_initFilter (struct can_filter* rfilter, int longueur);
	
	/// transmission par bus CAN et renvoit son état.
	/** Retourne true si l'envoi a été réussi, sinon false <BR>Traite une seule trame CAN a la fois */
	bool ECAN1_transmit(int portCan, CANLINUX_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg)__attribute__((deprecated("This fuction is deprecated. Please use canLinux_transmit instead")));
	/// Mise de donnees dans une FIFO selon sa priorite et renvoit son état.
	/** Retourne true si le message a trouve une place dans la FIFO, false si la FIFO etait pleine<BR>Traite une seule trame CAN a la fois */
	bool canLinux_transmit(CANLINUX_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg);	///<\todo renommer cette fonction comme canLinux_Init
	
	/// Interroge le bus CAN selectionné et remplit le champ recCanMsg.
	/** Retourne true s'il a recupere des donnees, sinon false <BR>Traite une seule trame CAN a la fois. Fonction bloquante dans l'etat */
	bool ECAN1_receive(int portCan, uCAN1_MSG *recCanMsg)__attribute__((deprecated("This fuction is deprecated. Please use canLinux_receive instead")));
	/// Interroge le bus CAN et remplit le champ recCanMsg s'il y a un nouveau message. Sinon, retente tous les 500 us jusqu'au timeout renseigne (en ms).
	/** Retourne true s'il a recupere des donnees, false s'il n'y a pas des donnees dans le timeout.<BR>Traite une seule trame CAN a la fois.*/
	bool canLinux_receive(uCAN1_MSG *recCanMsg, unsigned int timeOut);
	
	/// Identifie la trame CAN selectionné comme etant ou pas un message dans le rang des GSMR_SENT.
	/** Retourne true si l'identifiant est du type GSMR_SENT, false en cas contraire.<BR> Rang des identifiants GSMR_SENT: 0x60 - 0x6F */
	bool messageIsGSM_R_SENT(int IDunderTest);
	
	/// Identifie la trame CAN selectionné comme etant ou pas un message dans le rang des GSMR_RECEIVED.
	/** Retourne true si l'identifiant est du type GSMR_RECEIVED, false en cas contraire.<BR> Rang des identifiants GSMR_RECEIVED: 0x70 - 0x7F */
	bool messageIsGSM_R_RECEIVED(int IDunderTest);
	
	/// Identifie la trame CAN selectionné comme etant ou pas un message dans le rang des EBT.
	/** Retourne true si l'identifiant est du type EBT, false en cas contraire.<BR> Rang des identifiants EBT: 0x30 - 0x3F */
	bool messageIsEBT_L2(int IDunderTest);
#endif
	
	
#endif
