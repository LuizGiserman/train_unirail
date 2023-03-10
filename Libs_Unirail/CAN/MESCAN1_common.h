#ifndef MESCAN1_COMMON_H
#define	MESCAN1_COMMON_H ///<\todo le contenu de ce fichier n'est pas trié

#define UNIRAIL

//#define AVEC_INFRA
#define RAS             				0x00
#define NB_MAX_CAR_MES_EBT  20  //Si on n'utilise pas les 4 octets EEPROM
//#define NB_MAX_CAR_MES_EBT  15  //Avec les 4 octets EEPROM
///\todo aussi utilisï¿½ pour les crash, il faut changer le nom
typedef enum {
    HARDWARE = 0,
    SOFTWARE = 0x10,
    CAUSES_EXTERNES = 0x20
} TYPE_WARNING;


#endif	/* MESCAN1_COMMON_H */