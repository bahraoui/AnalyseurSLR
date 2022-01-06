#include "analyseurLR.h"

void decalage(char* pile, char*flot, size_t* taillePile, signed char *transition, table tableau){
    sprintf(&pile[(*taillePile)], "%c%d", flot[0], (*transition));
    if ((*transition) < 10)
    {
        (*taillePile) += 2;
    }
    else
    {
        (*taillePile) += snprintf(NULL, 0, "%i", (*transition)) + 1; // snprintf donne le nombre de caracteres necessaires pour ecrire le nombre [1567 => 4]
    }
    if (flot[0] != '\0')
    {
        memmove(flot, flot + 1, strlen(flot)); // enleve le 1er caracatere de flot
    }
    (*transition) = tableau.trans[256 * (*transition) + flot[0]];
}

void reduction(char* pile, char*flot, size_t* taillePile, signed char *transition, file_read grammaireEtTable){
    size_t tailleRegle = strlen((const char*)grammaireEtTable.G.rules[-(*transition) - 1].rhs);
    size_t indexRegle = (*taillePile) - 1, indexNbTransition;
    size_t tmp = 0;
    // indexRule correspond au premier caractere de l'expression a retrouver
    while (tmp != tailleRegle){
        if ('0'>pile[indexRegle] || pile[indexRegle]>'9')
        {
            tmp++;
        }
        indexRegle--;
    }
    
    // indexNbTransition correspond au nombre precedant l'expression retrouvee
    indexNbTransition=indexRegle;
    if (indexNbTransition > 0) {
        while ('0'<=pile[indexNbTransition-1] && pile[indexNbTransition-1]<='9')
        {
            indexNbTransition--;
        }
    }
    sscanf(&pile[indexNbTransition],"%hhd",&tmp);
    sprintf(&pile[indexRegle+1], "%c%d", grammaireEtTable.G.rules[-(*transition) - 1].lhs, grammaireEtTable.t.trans[256 * ((tmp) + 1) - grammaireEtTable.G.rules[-(*transition) - 1].lhs]);
    (*taillePile) = indexRegle+2;
    tmp=grammaireEtTable.t.trans[256 * (tmp + 1) - grammaireEtTable.G.rules[-(*transition) - 1].lhs];
    (*transition) = grammaireEtTable.t.trans[256 * (tmp) + flot[0]];
}