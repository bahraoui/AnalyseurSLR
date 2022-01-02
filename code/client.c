#include "arbre.c"
#define MAX_STEPS 150

int main(int argc, char const *argv[])
{
    /****************************
     *
     *  Verification du bon nombre d'arguments [Bon nombre = 2]
     *
     ****************************/

    if (argc < 3) // nombre d'arguments trop petit
    {
        fprintf(stderr, "erreur -- trop peu d'arguments (tableau SLR et mot a tester requis)\n");
        printf("USAGE:  ./LRanalyzer [fichier] \"[mot]\"\n\
        fichier:\t-fichier contenant grammaire et tableau SLR\n\
        mot:\t\t-mot a tester sur la grammaire du fichier\n");
        exit(EXIT_FAILURE);
    }
    else if (argc > 3) // nombre d'arguments trop grand
    {
        fprintf(stderr, "erreur -- trop d'arguments (tableau SLR et mot uniquement)\n");
        printf("USAGE:  ./LRanalyzer [fichier] \"[mot]\"\n\
        fichier:\t-fichier contenant grammaire et tableau SLR\n\
        mot:\t\t-mot a tester sur la grammaire du fichier\n");
        exit(EXIT_FAILURE);
    }

    /*##########################
     *
     * FIN de Verification du bon nombre d'arguments [Bon nombre = 2]
     *
    ##########################*/

    // Verification du fichier en entree [Premier argument]

    char *fichier = (char *)malloc(strlen(argv[1]) + 1);
    file_read grammaireEtTable;
    strcpy(fichier, argv[1]);

    FILE *file = fopen(fichier, "r+");
    printf("Lecture du fichier en cours ...\r");
    if (file != NULL) // Fichier existant
    {
        printf("Lecture du fichier en cours ... \xE2\x9C\x94\n");
        printf("Validation du fichier en cours ...\r");
        grammaireEtTable = read_file(fichier);
        printf("Validation du fichier en cours ... \xE2\x9C\x94\n");
        fclose(file);
    }
    else // Fichier inexistant ou impossible d'acces
    {
        printf("Lecture du fichier en cours ... \xE2\x9D\x8C\n");
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", fichier);
        exit(EXIT_FAILURE);
    }

    /*##########################
     *
     * FIN de Verification du fichier
     *
    ##########################*/

    // Lecture du mot en entree [Second Argument] :
    printf("Lecture du mot en cours ...\r");
    char *mot = (char *)calloc(strlen(argv[2]) + 1, sizeof(char));
    strcpy(mot, argv[2]);
    printf("Lecture du mot en cours ... \xE2\x9C\x94\n");

    // affichage des valeurs donnees en entree et verifiees :
    printf("\nFichier : %s\nMot : %s\n", fichier, mot);

    /*##########################
     *
     * FIN de Verification du mot
     *
    ##########################*/

    
    /****************************
     *
     *  Debut d'algo
     *
     ****************************/
    
    char *flot = (char *)calloc(strlen(mot)+1, sizeof(char));
    char *pile = (char *)calloc(strlen(mot) * 512, sizeof(char));
    neoudsRencontresOrphelins = (noeud **)malloc(strlen(mot) * 512 * sizeof(noeud *));
    tailleNeoudsRencontresOrphelins = 0;
    char tailleRegle, tmp, neoudRecupere;
    size_t indexRegle, indexNbTransition, taillePile = 1;
    pile[0] = '0';
    strcpy(flot, mot);
    printf("\n\n##############################\n\tDebut Algo SLR\n##############################\n\n\
    \tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s\t|    %s\n", flot, pile);

    signed char transitionMotEnCours = grammaireEtTable.t.trans[256 * 0 + flot[0]]; // 1 realisation avant de rentrer dans la boucle
    while (1)
    {
        // recuperation du noeud pour la construction de l'arbre
        neoudRecupere = recuperer_node(flot[0], transitionMotEnCours, grammaireEtTable.G);
        //construction arbre
        construire_arbre(neoudRecupere, transitionMotEnCours, grammaireEtTable.G);

        // dans le cas d'un decalage
        if (transitionMotEnCours > 0)
        {
            sprintf(&pile[taillePile], "%c%d", flot[0], transitionMotEnCours);
            if (transitionMotEnCours < 10)
            {
                taillePile += 2;
            }
            else
            {
                taillePile += snprintf(NULL, 0, "%i", transitionMotEnCours) + 1; // snprintf donne le nombre de caracteres necessaires pour ecrire le nombre [1567 => 4]
            }
            if (flot[0] != '\0')
            {
                memmove(flot, flot + 1, strlen(flot)); // enleve le 1er caracatere de flot
            }
            printf("d%d\t%s\t|    ", transitionMotEnCours, flot);
            printf("%s\n", pile);
            transitionMotEnCours = grammaireEtTable.t.trans[256 * transitionMotEnCours + flot[0]];
        }
        // dans le cas de fin de flot et d'acceptation
        else if (transitionMotEnCours == -127)
        {
            printf("\t\taccept\n");
            break;
        }
        // dans le cas d'une reduction
        else if (transitionMotEnCours < 0)
        {
            printf("r%d\t%s\t|    ", -transitionMotEnCours, flot);
            tailleRegle = strlen((const char*)grammaireEtTable.G.rules[-transitionMotEnCours - 1].rhs);
            indexRegle = taillePile - 1;
            tmp = 0;
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
            sprintf(&pile[indexRegle+1], "%c%d", grammaireEtTable.G.rules[-transitionMotEnCours - 1].lhs, grammaireEtTable.t.trans[256 * ((tmp) + 1) - grammaireEtTable.G.rules[-transitionMotEnCours - 1].lhs]);
            taillePile = indexRegle+2;
            tmp=grammaireEtTable.t.trans[256 * (tmp + 1) - grammaireEtTable.G.rules[-transitionMotEnCours - 1].lhs];
            printf("%s\n", pile);
            transitionMotEnCours = grammaireEtTable.t.trans[256 * (tmp) + flot[0]];
        }
        // dans le cas ou le flot n'est pas accepte (ex: "aa" avec S -> aSb|epsylon)
        else if (transitionMotEnCours == 0)
        {
            fprintf(stderr, "ATTENTION - Le mot \"%s\" n'est pas acceptable pour la grammaire suivante : \n",mot);
            print_grammar(grammaireEtTable.G);
            exit(EXIT_FAILURE);
        }
    }
    // print arbre
    printf("arbre:\n");
    print_arbre(neoudsRencontresOrphelins[0]);
    printf("\narbre pretty:\n");
    print_arbre_pretty(neoudsRencontresOrphelins[0],0);
    printf("\n\n##############################\n\tFin Algo SLR\n##############################\n\n");

    /*##########################
     *
     * Fin d'algo
     *
    ##########################*/
    
    free(flot);
    free(mot);
    free(fichier);
    free(pile);
    free(grammaireEtTable.G.rules);
    free(grammaireEtTable.t.trans);
    free_arbre(neoudsRencontresOrphelins[0]);
    free(neoudsRencontresOrphelins);
    return 0;
}