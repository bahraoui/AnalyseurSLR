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
    signed char transitionMotEnCours;
    file_read grammaireEtTable;
    size_t taillePile = 1;


    // Verification du nombre d'arguments
    verif_args(argc);

    // Verification du fichier en entree [Premier argument]
    grammaireEtTable = verification_fichier(argv[1]);

    // Lecture du mot en entree [Second Argument]
    mot = verification_mot(argv[2]);

    // affichage des valeurs donnees en entree et verifiees
    printf("\nFichier : %s\nMot : %s\n", argv[1], mot);

    // initialisation des variables
    flot = (char *)calloc(strlen(mot)+1, sizeof(char));
    pile = (char *)calloc(strlen(mot) * 512, sizeof(char));
    pile[0] = '0';
    strcpy(flot, mot);
    neoudsRencontresOrphelins = (noeud **)malloc(strlen(mot) * 512 * sizeof(noeud *));
    transitionMotEnCours = grammaireEtTable.t.trans[flot[0]]; // 1 realisation avant de rentrer dans la boucle

    // 1er affichage
    printf("\n\n##############################\n\tDebut Algo SLR\n##############################\n\n\
    \tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s\t|    %s\n", flot, pile);


    while (transitionMotEnCours!=-127)
    {
        // recuperation du noeud pour la construction de l'arbre
        neoudRecupere = recuperer_node(flot[0], transitionMotEnCours, grammaireEtTable.G);
        //construction arbre
        construire_arbre(neoudRecupere, transitionMotEnCours, grammaireEtTable.G);

        // dans le cas d'un decalage
        if (transitionMotEnCours > 0)
        {
            decalage(pile, flot, &taillePile, &transitionMotEnCours, grammaireEtTable.t, stdout);
        }
        // dans le cas d'une reduction
        else if (transitionMotEnCours < 0)
        {
            reduction(pile, flot, &taillePile, &transitionMotEnCours, grammaireEtTable, stdout);
        }
        // dans le cas ou le flot n'est pas accepte (ex: "aa" avec S -> aSb|epsylon)
        else if (transitionMotEnCours == 0)
        {
            print_grammar(grammaireEtTable.G);
            fprintf(stderr, "ATTENTION - Le mot \"%s\" n'est pas acceptable pour la grammaire suivante : \n",mot);
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
    printf("\n\narbre (vertical):\n");
    print_arbre_vertical(neoudsRencontresOrphelins[0],0);

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