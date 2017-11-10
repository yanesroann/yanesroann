#!/usr/bin/env python2.7

import os 
import sys
import re
import subprocess

def printline (process, requests, time, mode):
	print "|", process, "|",  mode, "|", time, "|", request, "|"
print '''
| PROCESSES   | MODE      | TIME     |REQUEST    |
| ------------| ----------| -------  | ----------|
''',

number = 1
while number <= 10:
	pipe = "./thor -p %s -r %s http://%s"% (number, number, url)
	output = subprocess.Popen(pipe, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).communicate()[0]
	q = re.findall('\d+', output)
	time = float(q[0]+"."+q[1])
	time = '%.2f' % time
	printline(str(processes).ljust(8), "Single   ", time.ljust(8), request.ljust(8))

	pipe = "shuf -i1-%s -n %s | ./measure ./lsort -n -q > /dev/null"% (number, number)
	output = subprocess.Popen(pipe, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).communicate()[0]
	q = re.findall('\d+', output)
	time = float(q[0]+"."+q[1])
	time = '%.2f' % time
	printline(str(number).ljust(8), "Forking   ", time.ljust(8), request.ljust(8))
	number = number*10
