/* Authors: GUENDOUZ Reda, BAHRAOUI Marwane, 2021-2022 */

#include "arbre.h"

noeud **neoudsRencontresOrphelins;
int tailleNeoudsRencontresOrphelins;

void print_arbre(noeud *racine){
    printf("%c(",racine->value);
    for (size_t i = 0; i < racine->nbfils; i++)
    {
        print_arbre(racine->fils[i]);
    }
    printf(")");
};

void print_arbre_vertical(noeud *racine,int indentation){
    for (size_t i = 0; i < indentation; i++)
    {
        printf("   ");
    }
    if (indentation) // autres noeuds
    {
        if (racine->nbfils) // noeuds != feuilles
        {
            printf("- %c :\n",racine->value);
        }
        else // feuilles
        {
            printf("- %c\n",racine->value);
        }
    } else { // noeud racine
        printf("%c :\n",racine->value);
    }
    for (size_t i = 0; i < racine->nbfils; i++)
    {
        print_arbre_vertical(racine->fils[i],indentation + 1);
    }
};

void free_arbre(noeud *racine){
    if (racine != NULL) {
        for (size_t i = 0; i < racine->nbfils; i++)
        {
            free_arbre(racine->fils[i]);
        }
        free(racine);
    }
};



/**
 * @brief recup le noeud
 * 
 * @param caractereLu 
 * @param transition 
 * @param parGrammar 
 * @return 0 si erreur
 */
char recuperer_node(char caractereLu, char transition, grammar parGrammar){
    if (transition==-127) // accept
    {
        return 0;
    }
    else if (transition>0) // decalage
    {
        return caractereLu;
    } else if (transition<0) // reduciton
    {
        return parGrammar.rules[-transition - 1].lhs;
    }
    return 0; // erreur
}

void construire_arbre(char nodeRecup, signed char transition, grammar parGrammar)
{
    if (nodeRecup==0) // accept ou erreur
    {
        return;
    }
    
    if (transition<0) // reduction
    {
        noeud *nonTerminal = (noeud*)malloc(sizeof(noeud));
        nonTerminal->value = nodeRecup;
        nonTerminal->nbfils = 0;

        int nbRightElement = strlen((const char*)parGrammar.rules[-transition - 1].rhs);
        for (size_t i = nbRightElement; i != 0; i--)
        {
            nonTerminal->fils[nonTerminal->nbfils] = neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins-i];
            nonTerminal->nbfils++;
        }
        tailleNeoudsRencontresOrphelins -= nbRightElement;
        neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins] = nonTerminal;
        tailleNeoudsRencontresOrphelins++;
    }
    else if (transition>0) // decalage
    {
        noeud* terminal = (noeud *)malloc(sizeof(noeud));
        terminal->nbfils = 0;
        terminal->value = nodeRecup;
        
        neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins] = terminal;
        tailleNeoudsRencontresOrphelins++;
    }
}