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

EVCOBJS = evc.o \
 canLinux.o MESCAN1_Utilitaire.o MESCAN1_VarStatusTrain.o MESCAN1_VarTrain.o\
 CONTROLADOR.o CONTROLADOR_data.o\
 odometrie.o
			  
EXECS = evc

ALL = $(EXECS) 

all: $(ALL)

canLinux.o: $(LIBCHEMIN)canLinux.c
	$(CC) $(CFLAGS) -c $< 

CONTROLADOR.o: $(CONTROLLEUR_CHEMIN)CONTROLADOR.c
	$(CC) $(CFLAGS) -c $< 

CONTROLADOR_data.o: $(CONTROLLEUR_CHEMIN)CONTROLADOR_data.c
	$(CC) $(CFLAGS) -c $< 

MESCAN1_Utilitaire.o: $(LIBCHEMIN)MESCAN1_Utilitaire.c
	$(CC) $(CFLAGS) -c $< 

MESCAN1_VarStatusTrain.o: $(LIBCHEMIN)MESCAN1_VarStatusTrain.c
	$(CC) $(CFLAGS) -c $< 

MESCAN1_VarTrain.o: $(LIBCHEMIN)MESCAN1_VarTrain.c
	$(CC) $(CFLAGS) -c $< 




evc: $(EVCOBJS)
	$(LD) $(LFLAGS) $(EVCOBJS) -o $@ 


#Regra Implicita
.c.o:
	$(CC) $(CFLAGS) -c $<   


clean:
	rm -f *.o $(ALL)