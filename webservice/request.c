/* request.c: HTTP Request Functions */

#include "spidey.h"

#include <errno.h>
#include <string.h>

#include <unistd.h>

int parse_request_method(struct request *r);
int parse_request_headers(struct request *r);

/**
 * Accept request from server socket.
 *
 * This function does the following:
 *
 *  1. Allocates a request struct initialized to 0.
 *  2. Initializes the headers list in the request struct.
 *  3. Accepts a client connection from the server socket.
 *  4. Looks up the client information and stores it in the request struct.
 *  5. Opens the client socket stream for the request struct.
 *  6. Returns the request struct.
 *
 * The returned request struct must be deallocated using free_request.
 **/
struct request *accept_request(int sfd) {

    struct request *r;
    struct sockaddr raddr;
    socklen_t rlen;

    /* Allocate request struct (zeroed) */
    r = calloc(1, sizeof(struct request));
    r->headers = NULL;


    rlen = sizeof(struct sockaddr);
    /* Accept a client */
    int client_fd = accept(sfd, &raddr, &rlen);
    if (client_fd < 0) {
        fprintf(stderr, "Unable to accept: %s\n", strerror(errno));
        goto fail;
    }
    
    /* Lookup client information */
    int client_info = getnameinfo((struct sockaddr *) &raddr, rlen, r->host, sizeof(r->host), r->port, sizeof(r->port), (NI_NUMERICHOST|NI_NUMERICSERV)); //NI_NAMEREQD); //A 0 means successful completion
    if (client_info != 0) {
        fprintf(stderr, "%s\n", gai_strerror(client_info));
        goto fail;
    }

    /* Open socket stream */
    r->file = fdopen(client_fd, "w+");
    if (r->file == NULL) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        fclose(r->file);
    }

    log("Accepted request from %s:%s", r->host, r->port);
    return r;

fail:
    free_request(r);
    return NULL;
}

/**
 * Deallocate request struct.
 *
 * This function does the following:
 *
 *  1. Closes the request socket stream or file descriptor.
 *  2. Frees all allocated strings in request struct.
 *  3. Frees all of the headers (including any allocated fields).
 *  4. Frees request struct.
 **/
void
free_request(struct request *r)
{
    struct header *header;

    if (r == NULL) {
    	return;
    }

    /* Close socket or fd */
    if (r->file) { 
        fclose(r->file);
    }
    else if (r->fd >= 0) {
        close(r->fd);
    }
           
    /* Free allocated strings */
    free(r->method);
    free(r->uri);
    free(r->path);
    free(r->query);

    /* Free headers */
    header = r->headers;
    struct header *next;
    while (header) {
        next = header->next;
        free(header->name);
        free(header->value);
        free(header);
        header = next;
    }
    /* Free request */
    free(r);
}

/**
 * Parse HTTP Request.
 *
 * This function first parses the request method, any query, and then the
 * headers, returning 0 on success, and -1 on error.
 **/
int
parse_request(struct request *r)
{
    /* Parse HTTP Request Method */
    if (parse_request_method(r) < 0) {
        log("parse_request_method() failed");
        return -1;
    }
   
    /* Parse HTTP Request Headers*/
    return parse_request_headers(r);
}

/**
 * Parse HTTP Request Method and URI
 *
 * HTTP Requests come in the form
 *
 *  <METHOD> <URI>[QUERY] HTTP/<VERSION>
 *
 * Examples:
 *
 *  GET / HTTP/1.1
 *  GET /cgi.script?q=foo HTTP/1.0
 *
 * This function extracts the method, uri, and query (if it exists).
 **/
int
parse_request_method(struct request *r) //muy bueno
{
    char buffer[BUFSIZ];

    /* Read line from socket */
    if ((fgets(buffer, BUFSIZ, r->file)) == NULL) {
        debug("fgets failed");
        goto fail;
    }
     
    /* Parse method and uri */
    char * meth = strtok(skip_whitespace(buffer), WHITESPACE);
    char * ur = strtok(NULL, WHITESPACE);

    /* Parse query from uri */

    char *que = strchr(ur, '?');
    if (que != NULL) {
        *que++ = '\0';
    } else {
        que = "";
    }
    /* Record method, uri, and query in request struct */

    r->method = strdup(meth);
    r->uri = strdup(ur);
    r->query = strdup(que);

    debug("HTTP METHOD: %s", r->method);
    debug("HTTP URI:    %s", r->uri);
    debug("HTTP QUERY:  %s", r->query);

    return 0;

fail:
    return -1;
}

/**
 * Parse HTTP Request Headers
 *
 * HTTP Headers come in the form:
 *
 *  <NAME>: <VALUE>
 *
 * Example:
 *
 *  Host: localhost:8888
 *  User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:29.0) Gecko/20100101 Firefox/29.0
 *  Accept: text/html,application/xhtml+xml
 *  Accept-Language: en-US,en;q=0.5
 *  Accept-Encoding: gzip, deflate
 *  Connection: keep-alive
 *
 * This function parses the stream from the request socket using the following
 * pseudo-code:
 *
 *  while (buffer = read_from_socket() and buffer is not empty):
 *      name, value = buffer.split(':')
 *      header      = new Header(name, value)
 *      headers.append(header)
 **/
int
parse_request_headers(struct request *r) // checked
{
    struct header *curr = NULL;
    char buffer[BUFSIZ];
    char *name;
    char *value;
    
    /* Parse headers from socket */

    while (fgets(buffer, BUFSIZ, r->file) != NULL && strlen(skip_whitespace(buffer))) {
        chomp(buffer);
        name = skip_whitespace(buffer);
        value = strchr(name, ':');
        if (value == NULL) {
            log("header failed %s", buffer);
            goto fail;
        }
        *value++ = '\0';
        value = skip_whitespace(value);
        curr = calloc(1,sizeof(struct header));
        if (curr == NULL) {
            log("calloc failed: %s", strerror(errno)); 
            goto fail;
        }

        curr->name = strdup(name);
        curr->value = strdup(value);
        curr->next = r->headers;
        r->headers = curr;
    
    }
#ifndef NDEBUG
    for (struct header *header = r->headers; header != NULL; header = header->next) {
        if (strcmp(header->name, "Cookie")!= 0) {
    	    debug("HTTP HEADER %s = %s", header->name, header->value);
        }
    }
#endif
    
    
    return 0;

fail:
    return -1;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
