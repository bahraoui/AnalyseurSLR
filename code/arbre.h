/* Authors: GUENDOUZ Reda, BAHRAOUI Marwane, 2021-2022 */

#ifndef ARBRE
#define ARBRE

#include "LRGrammar.h"
#include "read_file.h"

typedef struct noeud
{
    struct noeud* fils[100];
    char value;
    int nbfils;
}noeud;

extern noeud **neoudsRencontresOrphelins;
extern int tailleNeoudsRencontresOrphelins;

/**
 * @brief 
 * 
 * @param racine 
 */
void print_arbre(noeud *racine);

/**
 * @brief 
 * 
 * @param racine 
 * @param indentation 
 */
void print_arbre_pretty(noeud *racine,int indentation);

/**
 * @brief 
 * 
 * @param racine 
 */
void free_arbre(noeud *racine);

/**
 * @brief recup le noeud.
 * 
 * @param caractereLu 
 * @param transition 
 * @param parGrammar 
 * @return 0 si erreur
 */
char recuperer_node(char caractereLu, char transition, grammar parGrammar);

/**
 * @brief 
 * 
 * @param nodeRecup 
 * @param transition 
 * @param parGrammar 
 */
void construire_arbre(char nodeRecup, signed char transition, grammar parGrammar);

#endif