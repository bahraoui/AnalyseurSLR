/* Authors: GUENDOUZ Reda, BAHRAOUI Marwane, 2021-2022 */

#ifndef TOOLS
#define TOOLS

#include <stdio.h>
#include "read_file.h"

/**
 * @brief verification du nombre d'arguments.
 * 
 * @param argc nombre d'arguments donnees en entree lors de l'execution du programme
 */
void verif_args(int argc);

/**
 * @brief Verifie le fichier en entree et le retourne si aucune erreur n'est rencontree
 * 
 * @param argv 
 * @return file_read 
 */
file_read verification_fichier(char const *argv);


/**
 * @brief verifie le mot en entree et le retourne si aucune erreur n'est observe
 * 
 * @param argv 
 * @return char* 
 */
char* verification_mot(char const *argv);

/**
 * @brief affiche la ligne en l'état actuel de l'analyse syntaxique
 * 
 * @param pile 
 * @param flot 
 * @param transition la transition actuel
 * @param tailleMot la taille de base du mot en entree
 */
void affichage_ligne(char* pile, char* flot,signed char transition, size_t tailleMot);

#endif