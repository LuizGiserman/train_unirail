#compilar
CC = gcc
LD = gcc
AR = ar

#linkeditar
DEBUG = -D DEBUG
CFLAGS = -Wall -pthread -lrt -DMC802=0 #$(DEBUG) 
LFLAGS = -Wall -pthread -lrt

LIBCHEMIN = ../../Libs_Unirail/CAN/
CONTROLLEUR_CHEMIN = controlleur/

EVCOBJS = evc.o canLinux.o MESCAN1_Utilitaire.o CONTROLADOR.o odometrie.o
			  
EXECS = evc

ALL = $(EXECS) 

all: $(ALL)

canLinux.o: $(LIBCHEMIN)canLinux.c
	$(CC) $(CFLAGS) -c $< 

CONTROLADOR.o : $(CONTROLLEUR_CHEMIN)CONTROLADOR.c
	$(CC) $(CFLAGS) -c $< 

MESCAN1_Utilitaire.o: $(LIBCHEMIN)MESCAN1_Utilitaire.c
	$(CC) $(CFLAGS) -c $< 


evc: $(EVCOBJS)
	$(LD) $(LFLAGS) $(EVCOBJS) -o $@ 


#Regra Implicita
.c.o:
	$(CC) $(CFLAGS) -c $<   


clean:
	rm -f *.o $(ALL)