/* handler.c: HTTP Request Handlers */

#include "spidey.h"

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <dirent.h>
#include <unistd.h>

/* Internal Declarations */
http_status handle_browse_request(struct request *request);
http_status handle_file_request(struct request *request);
http_status handle_cgi_request(struct request *request);
http_status handle_error(struct request *request, http_status status);

/**
 * Handle HTTP Request
 *
 * This parses a request, determines the request path, determines the request
 * type, and then dispatches to the appropriate handler type.
 *
 * On error, handle_error should be used with an appropriate HTTP status code.
 **/
http_status
handle_request(struct request *r)
{
    http_status result;
    request_type type;

    /* Parse request */
    if (parse_request(r) < 0) {
        log("parse request failed");
        return handle_error(r, HTTP_STATUS_BAD_REQUEST);
    }

    /* Determine request path */
    if ((r->path = determine_request_path(r->uri)) == NULL) { 
        debug("HTTP REQUEST PATH: %s", r->path);
        return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }

    debug("HTTP REQUEST PATH: %s", r->path);
  
    /* Dispatch to appropriate request handler type */
    type = determine_request_type(r->path);
      
    switch (type) {
        case (REQUEST_BROWSE):
            result = handle_browse_request(r);
            debug("HTTP REQUEST TYPE: BROWSE");
            break;
        case (REQUEST_CGI):
            result = handle_cgi_request(r); 
            debug("HTTP REQUEST TYPE: CGI");
            break;
        case (REQUEST_FILE):
            result = handle_file_request(r);   
            debug("HTTP REQUEST TYPE: FILE");
            break;
        default:
            debug("HTTP REQUEST STATUS: NO TYPE");
            return handle_error(r, HTTP_STATUS_NOT_FOUND);
            break;
    }
    
    log("HTTP REQUEST STATUS: %s", http_status_string(result));
    return result;
}

/**
 * Handle browse request
 *
 * This lists the contents of a directory in HTML.
 *
 * If the path cannot be opened or scanned as a directory, then handle error
 * with HTTP_STATUS_NOT_FOUND.
 **/
http_status
handle_browse_request(struct request *r)
{
    struct dirent **entries;
    int n;

    /* Open a directory for reading or scanning */
    n = scandir(r->path, &entries, NULL, alphasort);
    if (n < 0) {
        fprintf(stderr, "scandir failed: %s\n", strerror(errno));
        return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }
    else {
        int i = 1;
     
        /* Write HTTP Header with OK Status and text/html Content-Type */
        fprintf(r->file, "HTTP/1.0 200 0K\n");
        fprintf(r->file, "Content-Type: text/html\n");
        fprintf(r->file, "\r\n");

        /* For each entry in directory, emit HTML list item */
        fprintf(r->file, "<ul>"); 
        while (i < n) {
            fprintf(r->file, "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">");
            fprintf(r->file, "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\" integrity=\"sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp\" crossorigin=\"anonymous\">");
            fprintf(r->file, "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>");
            fprintf(r->file, "<link href=\"https://maxcdn.bootstrapcdn.com/font-awesome/4.6.0/css/font-awesome.min.css\" rel=\"stylesheet\">");
            fprintf(r->file, "<li><a href = %s/>%s</a></li>", entries[i]->d_name, entries[i]->d_name);
            ++i;
        }
    }

    fprintf(r->file, "</ul>");
    /* Flush socket, return OK */

    if ((fflush(r->file)) < 0) {
        fprintf(stderr, "flush failed: %s\n", strerror(errno));
    }
 
    return HTTP_STATUS_OK;
}

/**
 * Handle file request

 * This opens and streams the contents of the specified file to the socket.
 *
 * If the path cannot be opened for reading, then handle error with
 * HTTP_STATUS_NOT_FOUND.
 **/
http_status
handle_file_request(struct request *r)
{
    FILE *fs;
    char buffer[BUFSIZ];
    char *mimetype = NULL;
    size_t nread;

    /* Open file for reading */
    if ((fs = fopen(r->path, "r")) == NULL) {
        fprintf(stderr, "fopen failed: %s\n", strerror(errno)); 
        fclose(fs);
        return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }     
 
    /* Determine mimetype */   
    mimetype = determine_mimetype(r->path);
    
    /* Write HTTP Headers with OK status and determined Content-Type */
    fprintf(r->file, "HTTP/1.0 200 0K\n");
    fprintf(r->file, "Content-Type: %s\n", mimetype);
    fprintf(r->file, "\r\n");
   
    /* Read from file and write to socket in chunks */
    while ((nread = fread(buffer, 1, BUFSIZ, fs)) != 0) {
        fwrite(buffer, 1, nread, r->file);
    }
 
    /* Close file, flush socket, deallocate mimetype, return OK */
    fclose(fs);
    fflush(r->file);
    free(mimetype);
    return HTTP_STATUS_OK;
}

/**
 * Handle file request
 *
 * This popens and streams the results of the specified executables to the
 * socket.
 *
 *
 * If the path cannot be popened, then handle error with
 * HTTP_STATUS_INTERNAL_SERVER_ERROR.
 **/
http_status
handle_cgi_request(struct request *r)
{
    FILE *pfs;
    char buffer[BUFSIZ];
    struct header *header;

    /* Export CGI environment variables from request:
    * http://en.wikipedia.org/wiki/Common_Gateway_Interface */

    /* Export CGI environment variables from request headers */
    setenv("REQUEST_METHOD", r->method, 1);
    setenv("REQUEST_URI", r->uri, 1);
    setenv("QUERY_STRING", r->query, 1);
    setenv("REMOTE_ADDR", r->host, 1);
    setenv("DOCUMENT_ROOT", RootPath, 1);
    setenv("REMOTE_PORT", r->port, 1);
    setenv("SCRIPT_FILENAME", r->path, 1);
    setenv("SERVER_PORT", r->port, 1);
    
    for (header = r->headers; header != NULL; header = header->next) {
        if (streq(header->name, "HTTP_ACCEPT")) { 
            setenv("HTTP_ACCEPT", header->value , 1);
        }
         if (streq(header->name, "HTTP_ACCEPT_LANGUAGE")) { 
            setenv("HTTP_ACCEPT_LANGUAGE", header->value , 1);
        }
        if (streq(header->name, "HTTP_ACCEPT_ENCODING")) { 
            setenv("HTTP_ACCEPT_ENCODING", header->value, 1);
        }
        if (streq(header->name, "HTTP_CONNECTION")) { 
            setenv("HTTP_CONNECTION", header->value , 1);
        }
        if (streq(header->name, "HTTP_USER_AGENT")) {
            setenv("HTTP_USER_AGENT", header->value , 1);
        }
        if (streq(header->name, "HTTP_HOST")) {
            setenv("HTTP_HOST", header->value, 1);
        }
    }

    /* POpen CGI Script */
    if ((pfs = popen(r->path, "r")) == NULL) {  
        log("popen failed");       
        pclose(pfs);
        return HTTP_STATUS_NOT_FOUND;
    }

    
    /* Copy data from popen to socket */
    while (fgets(buffer, BUFSIZ, pfs)) {
        fputs(buffer, r->file);
    }
    

    /* Close popen, flush socket, return OK */
    pclose(pfs); 
    fflush(r->file);
    return HTTP_STATUS_OK;
}

/**
 * Handle displaying error page
 *
 * This writes an HTTP status error code and then generates an HTML message to
 * notify the user of the error.
 **/
http_status
handle_error(struct request *r, http_status status)
{
    const char *status_string = http_status_string(status);

    /* Write HTTP Header */
    fprintf(r->file, "HTTP/1.0 %s\n", status_string);
    fprintf(r->file, "Content-Type: text/html\n");
    fprintf(r->file, "\r\n"); 
    /* Write HTML Description of Error*/ 
    fprintf(r->file,"<!DOCTYPE html>");
    fprintf(r->file, "<html lang=\"en\">");
    fprintf(r->file, "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">");

    fprintf(r->file, "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\" integrity=\"sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp\" crossorigin=\"anonymous\">");

    fprintf(r->file, "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>");

    fprintf(r->file, "<link href=\"https://maxcdn.bootstrapcdn.com/font-awesome/4.6.0/css/font-awesome.min.css\" rel=\"stylesheet\">");
    
    fprintf(r->file, "<body>");
    fprintf(r->file, "<h1>%s</h1>", status_string);
    fprintf(r->file, "<div class=\"thumbnail\" style=\"text-align: center\">");
    fprintf(r->file,"<img src=\"https://im.unp.im/acid/pics/20101224/funny_error_messages_02.jpg\" class=\"img-responsive\">");
    fprintf(r->file, "</div>");
    fprintf(r->file, "</body>");
    fprintf(r->file, "</html>");
    /* Return specified status */
    return status;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
