#include "LRGrammar.h"
#include "read_file.h"

char construire_arbre(char *arbre, char *pile, rule parRule, char *arbreSize)
{
    char a = *(arbreSize);
    if (strlen(parRule.rhs) == 0)
    {
        a += 3;
        arbre = (char *)realloc(arbre, a * sizeof(char));
        sprintf(&arbre[a - 3], "%c()", parRule.lhs);
    }
    else
    {
        size_t i = 0, indexNonFinal = 0;
        int size = strlen(parRule.rhs), parOuvrante = 0, parFermante = 0, debut=-1;
        char *newArbre = calloc(size * 3 + a + 3, sizeof(char));
        char terminaux[6];
        sprintf(newArbre, "%c(", parRule.lhs);
        
        for (i = 0; i < size; i++)
        {
            if (parRule.rhs[i] > 0)
            {
                if (parRule.rhs[i] == '(' || parRule.rhs[i] == ')')
                {
                    sprintf(terminaux, "\'%c\'()", parRule.rhs[i]);
                    strcat(newArbre, terminaux);
                    a += 5;
                }
                else
                {
                    sprintf(terminaux, "%c()", parRule.rhs[i]);
                    strcat(newArbre, terminaux);
                    a += 3;
                }
            }
            else
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
                a += indexNonFinal - debut;
            }
        }
        strcat(newArbre, ")");
        a++;
        printf("##n#%s###",newArbre);
        printf("##a#%s###",arbre);
        if (debut==-1)
        {
            strcat(arbre,newArbre);
        }else
        {
            strcpy(arbre, newArbre);
        }
    }

    return a;
}