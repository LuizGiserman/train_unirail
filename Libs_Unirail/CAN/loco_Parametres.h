#ifndef LOCO_MAIN_PARAMS_H
#define	LOCO_MAIN_PARAMS_H ///<\todo le contenu de ce fichier n'est pas trié

#define MAX_CONSIGNE_VITESSE_AUTORISEE  0x32

#define NUMERO_TRAIN_UNIVERSEL          0x0

//Prediviseur de tension par 10 pour lecture tension de batterie
//Ex codage: 0x0C10 --> 0x0C:12V et 0x10: 0.16V soit 12.16V
#define V_BATTERIE_FAIBLE               0x0C10  // soit 12.16V
#define V_BATTERIE_TROP_FAIBLE          0x0B32 // soit 11,5V pour essai alim12V
//#define V_BATTERIE_TROP_FAIBLE          0x0B5A  // soit 11.9V

#define VMAX_RAILS  0x1700  //Codage tension volts en Hexa reste en hexa
//Ex si VMAX_RAILS = 0x1700 -->  = 23V  
//NB: La valeur réelle appliquée aux rails est :
//  Cette tension auquelle il faut ajouter 2x 0.8V (seuil du pont redresseur)
//  Soit Vrails réel = 23V + 1.6V = 24.6V

#define COEFF_MULTIPLICATEUR_WHEN_POWER_ON_RAIL     2
#define MAXTIMEOUT4LOCO_OFF (long)3541 * (long)240
//3541 x 16.944ms = 60s ou 1 minute quand incrément de 1 
//C'est à dire quand le train est alimenté par les rails
//On multiplie par le nombre de minutes désirées.
//Sinon c'est 60s divisé par "COEFF_MULTIPLICATEUR_WHEN_POWER_ON_RAIL"

#define CONSIGNE_VITESSE_MODE_MANU      0x10

#define MAX_CPT_REBOURS_LOCO_OFF        1770    ///1770*17ms~=30 secondes

#define PAS_ROUE_CODEUSE 0.016944 // en cm
//Parametres moteur CC
#define tau 0.33
#define k 1.41
#define dt 0.017
#define n 2.0
#define alphamin 30 

//Correcteur PI du moteur
#define KI_USINE    (n/k)*(1/tau)*dt
#define KP_USINE    (n/k)





#endif	/* LOCO_MAIN_PARAMS_H */

