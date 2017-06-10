/*

intermedial.c 

Application of catch and treatment Beacons.
Created in 2017 by Sergio García García.
Universidad Politecnica de Madrid.

*/

/* Libraries or files used */
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char buffer[80];

int main (int argc, char** argv) {
	// Pasamos como argumento la cola fifo
	sprintf(buffer, "./ibeacon_scan.sh %s", argv[1]);
	system(buffer);
}