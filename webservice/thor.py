#!/usr/bin/env python2.7

import multiprocessing
import os
import requests
import sys
import time
import math
# Globals

PROCESSES = 1
REQUESTS  = 1
VERBOSE   = False
URL       = None

# Functions

def usage(status=0):
    print '''Usage: {} [-p PROCESSES -r REQUESTS -v] URL
    -h              Display help message
    -v              Display verbose output

    -p  PROCESSES   Number of processes to utilize (1)
    -r  REQUESTS    Number of requests per process (1)
    '''.format(os.path.basename(sys.argv[0]))
    sys.exit(status)

def do_request(pid):
    average = 0 
    for req in range(0, REQUESTS):
        time_start = time.time()
        r = requests.get(URL)
        if VERBOSE == 1:
            print r.text
        time_elapsed = time.time() - time_start 
        average = average + time_elapsed 
        print "Process: {}, Requests: {}, Elapsed Time: {:.2f}".format(pid, req, time_elapsed)
    
    print "Process: {}, AVERAGE    , Elapsed Time: {:.2f}".format(pid, average/REQUESTS)
    return average/REQUESTS 
# Main execution

ARGUMENTS = sys.argv[1:]

if __name__ == '__main__':
    # Parse command line arguments
    while len(ARGUMENTS) and ARGUMENTS[0].startswith('-') and len(ARGUMENTS[0]) > 1:
        arg = ARGUMENTS.pop(0)
        if arg == '-v':
            VERBOSE = True
        elif arg == '-p':
            PROCESSES = int(ARGUMENTS.pop(0))
        elif arg == '-r':
            REQUESTS = int(ARGUMENTS.pop(0))
        elif arg == 'h':
            usage(0)
        else: 
            usage(1)
    URL = ARGUMENTS.pop(0)
    # Create pool of workers and perform requests 
    pool = multiprocessing.Pool(PROCESSES)
    avg_requests = pool.map(do_request, range(PROCESSES))
    avg_list = 0
    for i in avg_requests:
        avg_list = avg_list + i
    avg_list = avg_list/REQUESTS
    print "TOTAL AVERAGE ELAPSED TIME: {:.2f}".format(avg_list)
         
    #pass

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
