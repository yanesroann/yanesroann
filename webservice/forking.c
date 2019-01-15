/* forking.c: Forking HTTP Server */

#include "spidey.h"

#include <errno.h>
#include <signal.h>
#include <string.h>

#include <unistd.h>

/**
 * Fork incoming HTTP requests to handle the concurrently.
 *
 * The parent should accept a request and then fork off and let the child
 * handle the request.
 **/
void
forking_server(int sfd)
{
    struct request *request;
    pid_t pid;

    /* Accept and handle HTTP request */
    while (true) {
    	/* Accept request */
        request = accept_request(sfd);
        if (request == NULL) {
            continue;
        }

	/* Ignore children */
        signal(SIGCHLD, SIG_IGN);

	/* Fork off child process to handle request */
        pid = fork();
        if (pid < 0) {
            debug("fork failed %s", strerror(errno));
            
            free_request(request);
            continue;
        }
        if (pid == 0) { // Child
            debug("Handling client request");
            handle_request(request);
            close(sfd);
            exit(EXIT_SUCCESS);
        } else {        // Parent
            free_request(request);
        }
    }

    /* Close server socket and exit*/

    close(sfd);
    exit(EXIT_SUCCESS);
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
