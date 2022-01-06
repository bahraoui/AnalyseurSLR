/* Authors: GUENDOUZ Reda, BAHRAOUI Marwane, 2021-2022 */

#include "arbre.h"
#include "analyseurLR.h"
#include "tools.h"

int main(int argc, char const *argv[])
{
    // Var. globales
    tailleNeoudsRencontresOrphelins = 0;
    // Var. locales
    char *mot, *flot, *pile, neoudRecupere;
    signed char transitionEnCours, transitionPrecedenteAffichage;
    file_read grammaireEtTable;
    size_t taillePile = 1, tailleMot;

    // Verification du nombre d'arguments
    verif_args(argc);

    // Verification du fichier en entree [Premier argument]
    grammaireEtTable = verification_fichier(argv[1]);

    // Lecture du mot en entree [Second Argument]
    mot = verification_mot(argv[2]);
    tailleMot = strlen(mot);

    // affichage des valeurs donnees en entree et verifiees
    printf("\nFichier : %s\nMot : %s\n", argv[1], mot);

    // initialisation des variables
    flot = (char *)calloc(strlen(mot)+1, sizeof(char));
    pile = (char *)calloc(strlen(mot) * 4 + 2, sizeof(char));
    pile[0] = '0';
    strcpy(flot, mot);
    neoudsRencontresOrphelins = (noeud **)malloc(strlen(mot) * 512 * sizeof(noeud *));
    transitionEnCours = grammaireEtTable.t.trans[(unsigned char)flot[0]]; // 1 realisation avant de rentrer dans la boucle

    // 1er affichage
    printf("\n\n##############################\n\tDebut Algo SLR\n##############################\n\n\
    \tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s    |    %s\n", flot, pile);

    while (transitionEnCours!=-127)
    {
        // recuperation du noeud pour la construction de l'arbre
        neoudRecupere = recuperer_node(flot[0], transitionEnCours, grammaireEtTable.G);
        //construction arbre
        construire_arbre(neoudRecupere, transitionEnCours, grammaireEtTable.G);

        // dans le cas d'un decalage
        if (transitionEnCours > 0)
        {
            transitionPrecedenteAffichage = transitionEnCours;
            decalage(pile, flot, &taillePile, &transitionEnCours, grammaireEtTable.t, stdout);
            affichage_ligne(pile,flot,transitionPrecedenteAffichage,tailleMot);
        }
        // dans le cas d'une reduction
        else if (transitionEnCours < 0)
        {
            transitionPrecedenteAffichage = transitionEnCours;
            reduction(pile, flot, &taillePile, &transitionEnCours, grammaireEtTable, stdout);
            affichage_ligne(pile,flot,transitionPrecedenteAffichage,tailleMot);
        }
        // dans le cas ou le flot n'est pas accepte (ex: "aa" avec S -> aSb|epsylon)
        else if (transitionEnCours == 0)
        {
            fprintf(stderr, "ATTENTION - Le mot \"%s\" n'est pas acceptable pour la grammaire suivante : \n",mot);
            print_grammar(grammaireEtTable.G);
            free(flot);
            free(mot);
            free(pile);
            free(grammaireEtTable.G.rules);
            free(grammaireEtTable.t.trans);
            free_arbre(neoudsRencontresOrphelins[0]);
            free(neoudsRencontresOrphelins);
            exit(EXIT_FAILURE);
        }
    }

    // affichage de l'arbre
    printf("\t\taccept\n");
    printf("\narbre (bien paranthésé):\n");
    print_arbre(neoudsRencontresOrphelins[0]);
    if (strlen(mot)<20)
    {
        printf("\n\narbre (vertical):\n");
        print_arbre_vertical(neoudsRencontresOrphelins[0],0);
    }
    

    // affichage de fin
    printf("\n##############################\n\tFin Algo SLR\n##############################\n");
    
    // free toutes les allocations precedentes
    free(flot);
    free(mot);
    free(pile);
    free(grammaireEtTable.G.rules);
    free(grammaireEtTable.t.trans);
    free_arbre(neoudsRencontresOrphelins[0]);
    free(neoudsRencontresOrphelins);
    return 0;
}