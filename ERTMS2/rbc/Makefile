#compilar
CC = gcc
LD = gcc
AR = ar

#linkeditar
DEBUG = -D DEBUG
CFLAGS = -Wall -pthread#$(DEBUG) 
LFLAGS = -Wall -pthread

RBCOBJS = rbc.o \
			  queueDemande.o \
			  queueEnvoi.o \
			  queueBusyResource.o
			  
OBJS = $(SERVEUROBJS)

EXECS = rbc

ALL = $(EXECS) \
	  $(OBJS)


rbc: $(RBCOBJS)
	$(LD) $(LFLAGS) $(RBCOBJS) -o $@ 


#Regra Implicita
.c.o:
	$(CC) $(CFLAGS) -c $<   


clean:
	rm -f *.o $(ALL)