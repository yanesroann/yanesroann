# Roann Yanes (NetID: ryanes)
# Makefile

CC=		gcc
CFLAGS= -g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.

TARGETS= udpserver \
		 udpclient
		
all:		$(TARGETS)

udpserver.o: udpserver.c pg1lib.h
	$(CC) $(CFLAGS) -c -o udpserver.o udpserver.c

udpclient.o: udpclient.c pg1lib.h
	$(CC) $(CFLAGS) -c -o udpclient.o udpclient.c

udpserver: udpserver.o
	$(LD) $(LDFLAGS) -o udpserver udpserver.o -lcrypto -lz
	
udpclient: udpclient.o
	$(LD) $(LDFLAGS) -o udpclient udpclient.o -lcrypto -lz
clean:
	rm -f $(TARGETS) *.o
