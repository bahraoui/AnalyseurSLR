#ifndef TOOLS
#define TOOLS

#include <stdio.h>
#include "read_file.h"

void verif_args(int argc);

file_read verification_fichier(char const *argv);

char* verification_mot(char const *argv);

#endif