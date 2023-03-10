#compilar
CC = gcc
LD = gcc
AR = ar

#linkeditar
DEBUG = -D DEBUG
CFLAGS = -Wall -pthread -DMC802=0#$(DEBUG) 
LFLAGS = -Wall -pthread

LIBCHEMIN = ../../Libs_Unirail/CAN/

EVCOBJS = evc.o canLinux.o MESCAN1_Utilitaire.o
			  
OBJS = $(SERVEUROBJS)

EXECS = evc

ALL = $(EXECS) \
	  $(OBJS)

all: $(ALL)

canLinux.o: $(LIBCHEMIN)canLinux.c
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