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
 * @brief affichage d'un arbre bien paranthese
 * 
 * @param racine noeud racine de l'arbre
 */
void print_arbre(noeud *racine);

/**
 * @brief affichage d'un arbre en vertical
 * 
 * @param racine noeud racine de l'arbre
 * @param indentation niveau actuel du noeud en cours
 */
void print_arbre_vertical(noeud *racine,int indentation);

/**
 * @brief liberer les neouds d'un arbre
 * 
 * @param racine noeud racine de l'arbre
 */
void free_arbre(noeud *racine);

/**
 * @brief recuperer la valeur du noeud a l'iteration en cours
 *  si l'iteration de la boucle est un decalage, la valeur retournee est la valeur terminale
 *  si l'iteration de la boucle est une reduction, la valeur retournee est le non terminal produisant la regle
 * 
 * @param caractereLu caractere en cours de lecture
 * @param transition transition en cours
 * @param parGrammar grammaire du fichier en entree
 * @return 0 si erreur
 */
char recuperer_node(char caractereLu, char transition, grammar parGrammar);

/**
 * @brief construit l'arbre
 * 
 * @param nodeRecup 
 * @param transition 
 * @param parGrammar 
 */
void construire_arbre(char nodeRecup, signed char transition, grammar parGrammar);

#endif