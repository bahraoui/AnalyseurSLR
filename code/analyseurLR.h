#ifndef ANALYSELR
#define ANALYSELR

#include "LRGrammar.h"
#include "read_file.h"


void decalage(char* pile, char*flot, int* taillePile, signed char *transition, table tableau);


void reduction();


#endif