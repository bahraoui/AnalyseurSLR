/* Authors: GUENDOUZ Reda, BAHRAOUI Marwane, 2021-2022 */

#ifndef ANALYSELR
#define ANALYSELR

#include "LRGrammar.h"
#include "read_file.h"

/**
 * @brief ajout dans la pile et suppression du premier caractere dans flot.
 * 
 * @param pile 
 * @param flot 
 * @param taillePile 
 * @param transition 
 * @param tableau 
 */
void decalage(char* pile, char* flot, size_t* taillePile, signed char *transition, table tableau);

/**
 * @brief reduction dans la pile.
 * 
 * @param pile 
 * @param flot 
 * @param taillePile 
 * @param transition 
 * @param grammaireEtTable 
 */
void reduction(char* pile, char* flot, size_t* taillePile, signed char *transition, file_read grammaireEtTable);


#endif