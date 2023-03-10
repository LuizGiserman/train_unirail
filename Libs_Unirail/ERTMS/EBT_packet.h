#ifndef EBT_PACKET_H
	#define	EBT_PACKET_H
	
	#include <stdint.h>
	/** Legende:
		A_         Acceleration<BR>
		D_         distance<BR>
		G_         Gradient<BR>
		L_         length<BR>
		M_         Miscellaneous<BR>
		N_         Number<BR>
		NC_        class number<BR>
		NID_       identity number<BR>
		Q_         Qualifier<BR>
		T_         time/date<BR>
		V_         Speed<BR>
		X_         Text<BR>
	*/
	
	///EBT_VirtualBaliseCoverMarkerPacket: Indication to on-board that the telegram can be ignored according to a VBC.
	/**Taille:2<BR>
		ID packet:0<BR>
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 0
		uint8_t nid_vbcmk;
	} EBT_VirtualBaliseCoverMarkerPacket;
	
	///EBT_SystemVersionOrder: This packet is used to tell the on-board which is the operated system version.
	/**Taille:5<BR>
		ID packet:2<BR>
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 2
		uint8_t q_dir;
		uint16_t l_packet;	///< = 5
		uint8_t m_version;
	} EBT_SystemVersionOrder;
	
	///EBT_speedStep: Variable intermediaire, non existant dans la doc originale.
	/**Taille:3<BR>
	*/
	typedef struct 
	{
		uint8_t v_nvkvint;//	Speed step used to define the integrated correction factor Kv
		uint8_t m_nvkvint;//	Integrated correction factor Kv or if Q_NVKVINTSET = 1, gives the correction factor if maximum emergency brake deceleration is lower than A_NVP12
		uint8_t m_nvkvint_q_nvkvintset;//	Gives the correction factor if maximum emergency brake deceleration is higher than A_NVP23
	} EBT_speedStep;
	
	///EBT_NationalValues: Downloads a set of National Values to the train.
	/**Taille: <BR>
		ID packet:3<BR>
		\todo q_nvkvintset, v_nvkvint et m_nvkvint (dans EBT_speedStep) existent si q_nvkint=1
		\todo a_nvp12, a_nvp23  et m_nvkvint existent si q_nvkvintset=1
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 3
		uint8_t q_dir;
		uint16_t l_packet;	///< = 7
		uint8_t q_scale;
		uint16_t d_validnv;
		uint16_t first_nid_c;
		uint8_t n_iter_nid_c;
		uint16_t nid_c[32];
		uint8_t v_nvshunt;
		uint8_t v_nvstff;
		uint8_t v_nvonsight;
		uint8_t v_nvlimsuperv;
		uint8_t v_nvunfit;
		uint8_t v_nvrel;
		uint16_t d_nvroll;
		uint8_t q_nvsbtsmperm;
		uint8_t q_nvemrrls;
		uint8_t q_nvguiperm;
		uint8_t q_nvsbfbperm;
		uint8_t q_nvinhsmicperm;
		uint8_t v_nvallowovtrp;
		uint8_t v_nvsupovtrp;
		uint16_t D_NVOVTRP;
		uint8_t T_NVOVTRP;
		uint16_t D_NVPOTRP;
		uint8_t M_NVCONTACT;
		uint8_t T_NVCONTACT;
		uint8_t m_nvderun;
		uint16_t d_nvstff;
		uint8_t q_nvdriver_adhes;
		uint8_t a_nvmaxredadh1;
		uint8_t a_nvmaxredadh2;
		uint8_t a_nvmaxredadh3;
		uint8_t q_nvlocacc;
		uint8_t m_nvavadh;
		uint8_t m_nvebcl;
		uint8_t q_nvkint;
		uint8_t q_nvkvintset;
		uint8_t a_nvp12;
		uint8_t a_nvp23;
		EBT_speedStep NV_SpStFirst;
		uint8_t n_iter_nvkvint;
		EBT_speedStep NV_SpStNext[32];
		uint8_t n_iter_decLimits;
		uint8_t q_nvkvintsetNexr[32];
		uint8_t a_nvp12Next[32];
		uint8_t a_nvp23Next[32];
		EBT_speedStep NV_decLimitsNext[32];
		uint8_t n_iter_granularLimits[32];
		EBT_speedStep NV_decLimitsGranular[32][32];
		uint8_t l_nvkrint;
		uint8_t m_nvkrint;
		uint8_t n_iter_nvkr;
		uint8_t l_nvkrintNext[32];
		uint8_t m_nvkrintNext[32];
		uint8_t m_nvktint;
	} EBT_NationalValues;
	
	///EBT_Level1MovementAuthority: Transmission of a movement authority for level 1.
	/**Taille:17-258<BR>
		ID packet:12<BR>
		\todo t_sectiontimer et d_sectiontimerstoploc existent si q_sectiontimer=1
		\todo t_endtimer et d_endtimerstartloc existent si q_endtimer=1
		\todo d_dp et v_releasedp existent si q_dangerpoint=1
		\todo d_startol, t_ol, d_ol et v_releaseol existent si q_overlap=1
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 12
		uint8_t q_dir;
		uint16_t l_packet;
		uint8_t q_scale;
		uint8_t v_main;
		uint8_t v_ema;
		uint16_t t_ema;
		uint8_t n_iter_sections;
		GSMR_SectionDescription section[32];
		GSMR_SectionDescription endsection;
		ERTMS_SectionTimer end; ///<end.d_section = start_location
		uint8_t q_dangerpoint;
		uint16_t d_dp;
		uint8_t v_releasedp;
		ERTMS_SectionTimer overlap;
		uint16_t d_startol;
		uint8_t v_releaseol;
	} EBT_Level1MovementAuthority;
	
	///EBT_RepositioningInformation: Transmission of the update of an MA section. 
	/**Taille:3-7<BR>
		\todo t_sectiontimer et d_sectiontimerstoploc existent si q_sectiontimer=1
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 16
		uint8_t q_dir;
		uint16_t l_packet;
		uint8_t q_scale;
		uint16_t l_section;
	} EBT_RepositioningInformation;
	
	///EBT_LevelTransitionOrder: Transmission of a movement authority for levels 2/3. 
	/**Taille:12-257<BR>
		ID packet:41<BR>
		\todo NID_NTC existe si M_LEVELTR=1
		\todo d_dp et v_releasedp existent si q_dangerpoint=1
		\todo d_startol, t_ol et v_releaseol existent si q_overlap=1
	*/
	typedef struct 
	{
		uint8_t nid_packet;	///< = 41
		uint8_t q_dir;
		uint16_t l_packet;
		uint8_t q_scale;
		uint16_t d_leveltr;
		uint8_t m_leveltr;
		uint8_t nid_ntc;
		uint16_t l_ackleveltr;
		uint8_t n_iter_next;
		uint8_t m_leveltr_next[8];
		uint8_t nid_ntc_next[8];
		uint16_t l_ackleveltr_next[8];
	} EBT_LevelTransitionOrder;
	
#endif	
