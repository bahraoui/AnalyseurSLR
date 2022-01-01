#include <stdio.h>
#include <stdlib.h>
#include "LRGrammar.h"
#include "read_file.h"

typedef struct node
{
    struct node* fils[100];
    char value;
    int nbfils;
}node;

node **neoudsRencontresOrphelins;
int tailleNeoudsRencontresOrphelins;

void print_arbre(node *racine){
    printf("%c(",racine->value);
    for (size_t i = 0; i < racine->nbfils; i++)
    {
        print_arbre(racine->fils[i]);
    }
    printf(")");
};

void print_arbre_pretty(node *racine,int indentation){
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
        print_arbre_pretty(racine->fils[i],indentation + 1);
    }    
};

void free_arbre(node *racine){
    if (racine != NULL) {
        for (size_t i = 0; i < racine->nbfils; i++)
        {
            free_arbre(racine->fils[i]);
        }
        free(racine);
    }
};



/**
 * @brief recup le node.
 * 
 * @param caractereLu 
 * @param transition 
 * @param parGrammar 
 * @return 0 si erreur
 */
char recup_node(char caractereLu, char transition, grammar parGrammar){
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
        node *nonTerminal = (node*)malloc(sizeof(node));
        nonTerminal->value = nodeRecup;
        nonTerminal->nbfils = 0;

        int nbRightElement = strlen((const char*)parGrammar.rules[-transition - 1].rhs);
        while (nbRightElement!=0)
        {
            nonTerminal->fils[nonTerminal->nbfils] = neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins-nbRightElement];
            nonTerminal->nbfils++;
            nbRightElement--;
        }
        tailleNeoudsRencontresOrphelins -= strlen((const char*)parGrammar.rules[-transition - 1].rhs);
        neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins] = nonTerminal;
        tailleNeoudsRencontresOrphelins++;
    }
    else if (transition>0) // decalage
    {
        node* terminal = (node *)malloc(sizeof(node));
        terminal->nbfils = 0;
        terminal->value = nodeRecup;
        
        neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins] = terminal;
        tailleNeoudsRencontresOrphelins++;
    }
}