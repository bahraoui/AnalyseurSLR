#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node* fils[100];
    char value;
    int nbfils;
}node;

void print_arbre(node *racine){
    printf("%c(",racine->value);
    printf("oui\n");
    for (size_t i = 0; i < racine->nbfils; i++)
    {
        //printf("\t- voisin %d-%c\n",i,noeud3.voisins[i]->value);
        print_arbre(racine->fils[i]);
    }
    printf(")");
};

void add_to_noeudRencontres(node* noeudRencontres, int taille, node nouveauNoeud){
    noeudRencontres[taille] = nouveauNoeud;
    taille++;
}

int main(int argc, char const *argv[])
{
    node noeud1, noeud2,noeud3;
    node *noeuds = (node *) malloc(2*sizeof(node)) ;
    noeud1.value='a';
    noeud2.value='b';
    noeud3.value='S';

    noeud3.nbfils=0;
    noeud3.voisins[noeud3.nbfils] = &noeud1;
    noeud3.nbfils++;
    noeud3.voisins[noeud3.nbfils] = &noeud2;
    noeud3.nbfils++;
    noeud2.nbfils=0;
    noeud1.nbfils=0;

    noeuds[0]=noeud3;
    function_add(&noeuds);

    printf("voisins de %c:\n",noeuds[0].value);
    for (size_t i = 0; i < noeuds[0].nbfils; i++)
    {
        printf("\t- voisin %ld-%c\n",i,noeuds[0].voisins[i]->value);
    }
    printf("-%c-\n",noeuds[0].voisins[2]->value);
    test(noeuds[0].voisins[2]);
    printf("recursif:\n");
    print_arbre(&noeuds[0]);
    printf("\n");

    return 0;
}