/* Roann Yanes (NetID: ryanes)
 * udpserver.c
 * This program is the server. It sits on a machine and waits for incoming packets on a specific port. 
 * The server decrypts the messages from the client and replies with a checksum of the received message.
 * Solution adapted from Lecture 4 slides.
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "pg1lib.h"
#define MAX_BUF 4096

// display usage message
void usage(const char *progname, int status)
{
    fprintf(stderr, "Usage: %s \n", progname);
    fprintf(stderr, "Not enough arguments given");
    exit(status);
}

int main(int argc, char* argv[])
{
    // data structures to be used
    struct sockaddr_in sin, client_addr;
    char buf[MAX_BUF];
    int len;
    socklen_t addr_len;
    int s;
    int SERVER_PORT;
    char *pub_key = getPubKey(); // generates the server's public key

    // checks the command line arguments
    if (argc == 2) {
        sscanf(argv[1], "%i", &SERVER_PORT); // receives the port #
    }
    else {
        usage(argv[0], 1); // checks for correct number of arguments
    }

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY; // use the default IP address of server
    sin.sin_port = htons(SERVER_PORT);

    // setup passive open 
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("server: socket");
        exit(1);
    }

    // binds socket to an address
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("server: bind");
        exit(1);
    }

    /* receive message from client */
    while (1) {
        addr_len = sizeof (client_addr);

        char client_key[MAX_BUF];
        /* receive public key from client */
        if(recvfrom(s, client_key, sizeof(client_key), 0,  (struct sockaddr *)&client_addr, &addr_len)== -1) {
            perror("Receive error!\n");
            exit(1);
        }
    
        // encrypts server's public key with client's public key    
        char *encrypted_message = encrypt(pub_key, client_key);
    
        // sends the encrypted key as a response back to the client
        len = strlen(encrypted_message) + 1;
        if(sendto(s, encrypted_message, len, 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr)) == -1) {            
            perror ("server: sendto\n");
            exit(1);
        }

        // receives encrypted message from the client
        if(recvfrom(s, buf, sizeof(buf), 0,  (struct sockaddr *)&client_addr, &addr_len)== -1) {
            perror("Receive error!\n");
            exit(1);
        }
        
        // decrypts the message from the client
        char *new_message = decrypt(buf);

        // calculates and converts the checksum
        unsigned long sum = checksum(new_message);
        printf("Received %s, checksum %lu\n", new_message, sum);
        uint32_t converted = htonl(sum);
        
        // sends the converted checksum back to the client
        if(sendto(s, &converted, sizeof(uint32_t), 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr)) == -1) {            
            perror ("server: sendto\n");
            exit(1);
        }

        bzero((char*)&buf, sizeof(buf));
    }
    
    close(s);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
