#ifndef ANALYSELR
#define ANALYSELR

#include "LRGrammar.h"
#include "read_file.h"


void decalage(char* pile, char*flot, size_t* taillePile, signed char *transition, table tableau, FILE* output);


void reduction(char* pile, char*flot, size_t* taillePile, signed char *transition, file_read grammaireEtTable, FILE* output);


#endif