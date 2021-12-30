#include "LRGrammar.h"
#include "read_file.h"

typedef struct node
{
    struct node* voisins[100];
    char value;
    int nbvoisins;
}node;

void print_arbre(node *noeud){

    printf("%c(",noeud->value);
    if (noeud->nbvoisins>0)
    {
        for (size_t i = 0; i < noeud->nbvoisins; i++)
        {
            //printf("\t- voisin %d-%c\n",i,noeud3.voisins[i]->value);
            print_arbre(noeud->voisins[i]);
        }
    }
    printf(")");
};

/*
int main(int argc, char const *argv[])
{
    node noeud1, noeud2,noeud3;
    noeud1.value='a';
    noeud2.value='b';
    noeud3.value='S';

    noeud3.nbvoisins=0;
    noeud3.voisins[noeud3.nbvoisins++] = &noeud1;
    noeud3.voisins[noeud3.nbvoisins++] = &noeud2;
    noeud2.nbvoisins=0;
    noeud1.nbvoisins=0;

    printf("voisins de %c:\n",noeud3.value);
    for (size_t i = 0; i < noeud3.nbvoisins; i++)
    {
        printf("\t- voisin %d-%c\n",i,noeud3.voisins[i]->value);
    }
    printf("recursif:\n");
    print_arbre(&noeud3);
    printf("\n");
    return 0;
}
*/

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

void construire_arbre(node *nodeRencontrees, int sizeNodeRencontrees, char nodeRecup, signed char transition)
{
    if (nodeRecup==0) // accept ou erreur
    {
        return;
    }

    node terminal;
    terminal.nbvoisins = 0;
    terminal.value = nodeRecup;
    if (transition<0) // reduction
    {
        /* code */
    }
    else if (transition>0) // decalage
    {
        nodeRencontrees[sizeNodeRencontrees]=terminal;
        sizeNodeRencontrees++;
    }
    
/*

    if (strlen(parRule.rhs) == 0)
    {
        (*arbreSize) += 3;
        arbre = (char *)realloc(arbre, (*arbreSize) * sizeof(char));
        sprintf(&arbre[(*arbreSize) - 3], "%c()", parRule.lhs);
    }
    else
    {
        size_t i = 0, indexNonFinal = 0;
        int size = strlen(parRule.rhs), parOuvrante = 0, parFermante = 0, debut=-1;
        char *newArbre = calloc(size * 3 + (*arbreSize) + 3, sizeof(char));
        char terminaux[6];
        sprintf(newArbre, "%c(", parRule.lhs);
        (*arbreSize)+=2;
        
        for (i = 0; i < size; i++)
        {
            if (parRule.rhs[i] > 0) // terminal
            {
                if (parRule.rhs[i] == '(' || parRule.rhs[i] == ')')
                {
                    sprintf(terminaux, "\'%c\'()", parRule.rhs[i]);
                    strcat(newArbre, terminaux);
                    (*arbreSize) += 5;
                }
                else
                {
                    sprintf(terminaux, "%c()", parRule.rhs[i]);
                    strcat(newArbre, terminaux);
                    (*arbreSize) += 3;
                }
            }
            else // non terminal
            {
                while (arbre[indexNonFinal] != (-parRule.rhs[i]))
                {
                    indexNonFinal++;
                }
                debut = indexNonFinal;
                indexNonFinal += 2;
                parOuvrante = 1;
                parFermante = 0;
                while (parFermante != parOuvrante)
                {
                    if (arbre[indexNonFinal] == ')')
                    {
                        parFermante++;
                    }
                    else if (arbre[indexNonFinal] == '(')
                    {
                        parOuvrante++;
                    }
                    indexNonFinal++;
                }
                strncat(newArbre, &arbre[debut], indexNonFinal - debut);
                (*arbreSize) += indexNonFinal - debut;
            }
        }
        strcat(newArbre, ")");
        (*arbreSize)++;
        printf("##a#%s###",arbre);
        if (debut==-1)
        {
            strcat(arbre,newArbre);
        }else
        {
            strcpy(arbre, newArbre);
            (*arbreSize) -= oldArbreSize;
        }
        printf("#taille:%d#n#%s###",(*arbreSize),newArbre);
    }
*/
    return;
}