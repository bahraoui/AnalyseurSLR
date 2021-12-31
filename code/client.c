#include "func.c"
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
    file_read fichierLu;
    strcpy(fichier, argv[1]);

    FILE *file = fopen(fichier, "r+");
    printf("Lecture du fichier en cours ...\r");
    if (file != NULL) // Fichier existant
    {
        printf("Lecture du fichier en cours ... \xE2\x9C\x94\n");
        printf("Validation du fichier en cours ...\r");
        fichierLu = read_file(fichier);
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
    char taille_mot = strlen(argv[2]) + 1;
    char *mot = (char *)calloc(taille_mot, sizeof(char));
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
    
    char *flot = (char *)calloc(strlen(mot)+1, sizeof(char)); // plus tard : utiliser flot au lieu de mot
    char *pile = (char *)calloc(strlen(mot) * 512, sizeof(char));
    neoudsRencontresOrphelins = (node **)malloc(strlen(mot) * 1000 * sizeof(node *)); //A CHANGER BUFFER
    tailleNeoudsRencontresOrphelins = 0;
    char ruleSize, tmp, nodeRecup;
    size_t indexRule,indexNbTransition, pileSize = 1;
    pile[0] = '0';
    strcpy(flot, mot);
    printf("\n\n##############################\n\tDebut Algo SLR\n##############################\n\n\
    \tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s\t|    %s\n", flot, pile);

    signed char transMot = fichierLu.t.trans[256 * 0 + flot[0]]; // 1 realisation avant de rentrer dans la boucle
    while (1)
    {
        // recuperation du noeud pour la construction de l'arbre
        nodeRecup = recup_node(flot[0], transMot, fichierLu.G);
        //construction arbre [NULL a changer par la taille de noeuds...Orphelins]
        printf("noderecup:|%c|,transmot:|%d|\n",nodeRecup,transMot);
        construire_arbre(nodeRecup, transMot, fichierLu.G);

        // dans le cas d'un decalage
        if (transMot > 0)
        {
            sprintf(&pile[pileSize], "%c%d", flot[0], transMot);
            if (transMot < 10)
            {
                pileSize += 2;
            }
            else
            {
                pileSize += snprintf(NULL, 0, "%i", transMot) + 1;
            }
            if (flot[0] != '\0')
            {
                memmove(flot, flot + 1, strlen(flot)); // enleve le 1er caracatere de flot
            }
            printf("d%d\t%s\t|    ", transMot, flot);
            printf("%s\n", pile);
            transMot = fichierLu.t.trans[256 * transMot + flot[0]];
        }
        // dans le cas de fin de flot et d'acceptation
        else if (transMot == -127)
        {
            printf("\t\taccept\n");
            break;
        }
        // dans le cas d'une reduction
        else if (transMot < 0)
        {
            printf("r%d\t%s\t|    \n", -transMot, flot);
            ruleSize = strlen((const char*)fichierLu.G.rules[-transMot - 1].rhs);
            indexRule = pileSize - 1;
            tmp = 0;
            // indexRule correspond au premier caractere de l'expression a retrouver
            while (tmp != ruleSize){
                if ('0'>pile[indexRule] || pile[indexRule]>'9')
                {
                    tmp++;
                }
                indexRule--;
            }
            
            // indexNbTransition correspond au nombre precedant l'expression retrouvee
            indexNbTransition=indexRule;
            printf("AVANT WHILE\n");
            if (indexNbTransition > 0) {
                while ('0'<=pile[indexNbTransition-1] && pile[indexNbTransition-1]<='9')
                {
                    indexNbTransition--;
                }
            }
            printf("POST WHILE\n");
            //printf("ok%d\n",indexNbTransition+1);
            sscanf(&pile[indexNbTransition],"%hhd",&tmp);
            sprintf(&pile[indexRule+1], "%c%d", fichierLu.G.rules[-transMot - 1].lhs, fichierLu.t.trans[256 * (tmp + 1) - fichierLu.G.rules[-transMot - 1].lhs]);
            pileSize = indexRule+2;
            // digits tout ca la >10
            tmp=fichierLu.t.trans[256 * (tmp + 1) - fichierLu.G.rules[-transMot - 1].lhs];
            printf("%s\n", pile);
            transMot = fichierLu.t.trans[256 * (tmp) + flot[0]];
        }
        // dans le cas ou le flot n'est pas accepte (ex: "aa" avec S -> aSb|ε)
        else if (transMot == 0)
        {
            fprintf(stderr, "ATTENTION - Le mot \"%s\" n'est pas acceptable pour la grammaire suivante : \n",mot);
            print_grammar(fichierLu.G);
            exit(EXIT_FAILURE);
        }
        
    }
    printf("SORT DU WHILE\n");

    // print arbre
    printf("arbre:\n");
    //printf("nb voisins n[0]:%d\n",neoudsRencontresOrphelins[0].nbfils);
    print_arbre(&neoudsRencontresOrphelins[0]);
    //printf("IN MAIN FILS DE LA RACINE : %c\n",neoudsRencontresOrphelins[0].fils[2]->value);
    printf("\narbre ok\n");
    if (neoudsRencontresOrphelins[0]->fils[0]==NULL)
    {
    printf("ERREUR - 1er fils NUL\n");
    }
    
    for (size_t i = 0; i < neoudsRencontresOrphelins[0]->nbfils; i++)
    {
        printf("\t- voisin %d-%c\n",i,neoudsRencontresOrphelins[0]->fils[i]->value);
    }
    printf("\n\n##############################\n\tFin Algo SLR\n##############################\n\n");

    /*##########################
     *
     * FFin d'algo
     *
    ##########################*/
    
    free(flot);
    free(mot);
    free(fichier);
    free(pile);
    free_arbre(neoudsRencontresOrphelins[0]);

    free(neoudsRencontresOrphelins);
    return 0;
}