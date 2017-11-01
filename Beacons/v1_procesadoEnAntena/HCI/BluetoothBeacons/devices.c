
/* File devices.c */

#include <stdio.h>
#include <stdlib.h>
#include "devices.h"


int devices(){
	system("hcitool scan");
	return 0;
}