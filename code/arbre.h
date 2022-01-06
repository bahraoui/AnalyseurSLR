/* Authors: GUENDOUZ Reda, BAHRAOUI Marwane, 2021-2022 */

#ifndef ARBRE
#define ARBRE

#include "LRGrammar.h"
#include "read_file.h"

/**
 * @brief Représentation d'un arbre
 * 
 */
typedef struct noeud
{
    struct noeud** fils;
    unsigned char value;
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
 * @brief construit l'arbre.
 *  si l'iteration de la boucle est un decalage, une feuille est cree et ajoute dans la liste des noeuds rencontrees.
 *  si l'iteration de la boucle est une reduction, un noeud est cree avec en fils les derniers neouds de la liste des noeuds rencontrees
 *  et modification de la liste.
 * 
 * @param nodeRecup la valeur du neoud a creer
 * @param transition transition en cours
 * @param parGrammar la grammaire donnee en entree
 */
void construire_arbre(char nodeRecup, signed char transition, grammar parGrammar);

#endif