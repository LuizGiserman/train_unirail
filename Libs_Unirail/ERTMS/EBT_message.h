#ifndef EBT_MESSAGE_H
	#define	EBT_MESSAGE_H
	
	#include "EBT_packet.h"
	#include "GSM_R_packet.h"

	///EBT_Message:
	/**Taille:12+packet<BR>
	*/
	typedef struct 
	{
		uint8_t q_updown;	///< = 1
		uint8_t m_version;
		uint8_t q_media;	///< = 0
		uint8_t n_pig;
		uint8_t n_total;
		uint8_t m_dup;
		uint8_t m_mcount;
		GSMR_nid_lrbg nid_lrbg;
		uint8_t q_link;
		union 
		{
			EBT_Level1MovementAuthority packetNb12;
			EBT_RepositioningInformation packetNb16;
			EBT_LevelTransitionOrder packetNb41;
			EBT_NationalValues packetNb3;
		};
	} EBT_Message;
	
#endif