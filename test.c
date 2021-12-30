#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node* voisins[100];
    char value;
    int nbvoisins;
}node;

void function_add(node** t){
    node n4; // decalage
    n4.value='d';
    n4.nbvoisins=0;
    printf("oui%d\n",t[0]->nbvoisins);
    t[0]->voisins[t[0]->nbvoisins]=&n4; // noeud[0]<=>noeud3<=>'S' noeuds[2]=&n4;
    t[0]->nbvoisins++;
}

void print_arbre(node *noeud){
    printf("%c(",noeud->value);
    printf("oui\n");
    for (size_t i = 0; i < noeud->nbvoisins; i++)
    {
        //printf("\t- voisin %d-%c\n",i,noeud3.voisins[i]->value);
        print_arbre(noeud->voisins[i]);
    }
    printf(")");
};

void print_arbre_debug(node *noeud){
    printf("voisins de %c:\n",noeud[0].value);
    for (size_t i = 0; i < noeud[0].nbvoisins; i++)
    {
        printf("\t- voisin %ld-%c\n",i,noeud[0].voisins[i]->value);
    }
};

void test(node *noeud){
    printf("#%c#\n",noeud->value);
}

int main(int argc, char const *argv[])
{
    node noeud1, noeud2,noeud3;
    node *noeuds = (node *) malloc(2*sizeof(node)) ;
    noeud1.value='a';
    noeud2.value='b';
    noeud3.value='S';

    noeud3.nbvoisins=0;
    noeud3.voisins[noeud3.nbvoisins] = &noeud1;
    noeud3.nbvoisins++;
    noeud3.voisins[noeud3.nbvoisins] = &noeud2;
    noeud3.nbvoisins++;
    noeud2.nbvoisins=0;
    noeud1.nbvoisins=0;

    noeuds[0]=noeud3;
    function_add(&noeuds);

    printf("voisins de %c:\n",noeuds[0].value);
    for (size_t i = 0; i < noeuds[0].nbvoisins; i++)
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