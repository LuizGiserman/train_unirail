#include "../evc.h"
#include "stdlib.h"

nodeDemande path[PATH_SIZE] = {

	/* Demander aiguillages avant. Derniere Canton a la fin */
	[0] = { 
			2, (int[2]) {AIGUILLAGE + 2, 2}, 	/* Demander */
			0, NULL, 						 	/* Liberer */
		  },

	[1] = { 
			3, (int[3]) {AIGUILLAGE + 2, 2, 3}, /* Demander */
			2, (int[2]) {AIGUILLAGE + 2, 2}, 	/* Liberer */
		  }
};

cantonDistance pathCanton[CANTON_PATH_SIZE] = 
{
	C1, C2, C3, C12, C13, C7, C8, C9
};

int vitesseConsigne[CANTON_PATH_SIZE] = 
{
	25, 25, 25, 25, 25, 25, 25, 25
};