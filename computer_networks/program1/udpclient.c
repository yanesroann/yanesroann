/* Roann Yanes (NetID: ryanes)
 * udpclient.c
 * This program is the client. It sends a packet to the port on the specified machine, that contains whatever the user enters on the command line (either a file or a string).
 * The client sends an encrypted message to the server.
 * Solution adapted from Lecture 4 slides.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <sys/time.h>
#include "pg1lib.h"
#define MAX_BUF 4096


// display usage message
void usage(const char *progname, int status)
{
    fprintf(stderr, "Usage: %s\n", progname);
    fprintf(stderr, "Not enough arguments given");
    exit(status);
}

int main(int argc, char* argv[])
{
    // data structures to be used
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_BUF];
    int s, len;
    int SERVER_PORT;
    char message[MAX_BUF];
    bool is_file = false;
    char * public_key = getPubKey(); // generate public key

    // check the command line arguments
    if (argc == 4) {
        host = argv[1]; // location of server
        sscanf(argv[2], "%i", &SERVER_PORT); // server port #
        if ((fp = fopen(argv[3], "r+")) != NULL) {
             is_file = true; // if input is a file
        }
        else {
            strcpy(message, argv[3]); // if input is a string
        }
    } 
    else {
        usage(argv[0], 1); // if number of arguments given is incorrect
    }

    /* translate host name into peer's IP address*/
    hp = gethostbyname(host);
    if(!hp) {
        fprintf(stderr, "client: unknown host %s\n", host);
        exit(1);
    }

    /*build address data structure*/
    bzero((char*)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(hp->h_addr, (char*)&sin.sin_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);

    /*active open*/
    if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("client: socket\n");
        exit(1);
    }
    
    // send encrypted public key
    len = strlen(public_key) + 1;
    if(sendto(s, public_key, len, 0, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1) {
        perror ("client: sendto\n");
        exit(1);
    }
    
    // receive encrypted message
    char encrypted_message[MAX_BUF];
    socklen_t addr_len = sizeof(sin);

    /* receive public key from server */
    if(recvfrom(s, encrypted_message, sizeof(encrypted_message), 0,  (struct sockaddr *)&sin, &addr_len)== -1) {
        perror("Receive error!\n");
        exit(1);
    }
    
    /* decrypt server's public key */
    char *decrypted_message = decrypt(encrypted_message);

    /* main loop: get and send lines of text */
    if (is_file) {
        while (fgets(buf, sizeof(buf), fp)) {
            strcat(message, buf);
        }
    }

    // calculates checksum for the message
    unsigned long sum = checksum(message);
    fprintf(stdout, "Checksum sent: %lu\n", sum);
    
    // encrypts message using the server's public key
    char *actual_message = encrypt(message, decrypted_message);
    len = strlen(actual_message) + 1;
    if(sendto(s, actual_message, len, 0, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1) {
        perror ("client: sendto\n");
        exit(1);
    } // start time of message sent
    struct timeval time_struct;
    gettimeofday(&time_struct, NULL);
    long unsigned start_time = 1000000 * time_struct.tv_sec + time_struct.tv_usec;
    
    // receives checksum back from server
    uint32_t received_sum;
    if(recvfrom(s, &received_sum, sizeof(uint32_t), 0,  (struct sockaddr *)&sin, &addr_len)== -1) {
        perror("Receive error!\n");
        exit(1);
    } // end time of message received
    gettimeofday(&time_struct, NULL);
    long unsigned end_time = 1000000 * time_struct.tv_sec + time_struct.tv_usec;

    // calculation of RTT
    long unsigned RTT = end_time - start_time;

    // converts and compares the reported checksum
    unsigned long converted = ntohl(received_sum);
    if (converted != sum) {
        perror ("client: checksum\n");
        exit(1);
    }

    fprintf(stdout, "Checksum received: %lu\n", converted);
    fprintf(stdout, "RTT: %lu microseconds\n", RTT);

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
