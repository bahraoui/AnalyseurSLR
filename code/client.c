#include "func.c"
#define MAX_STEPS 150

int main(int argc, char const *argv[])
{
    size_t j;
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
    printf("\nFichier : %s\nMot : %s", fichier, mot);

    /*##########################
     *
     * FIN de Verification du mot
     *
    ##########################*/

    /******
     * debut d'algo
     ******/
    char *flot = (char *)calloc(strlen(mot), sizeof(char)); // plus tard : utiliser flot au lieu de mot
    char *pile = (char *)calloc(strlen(mot) * 4, sizeof(char));
    char *arbre = (char *)calloc(1, sizeof(char));
    char ruleSize, tmp, indexRule, indexNbTransition, nbDigits;
    char pileSize = 1, arbreSize = 0;
    pile[0] = '0';
    strcpy(flot, mot);
    printf("\n\n##############################\n\tDebut Algo SLR\n##############################\n\n\
    \tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s\t|    %s\n", flot, pile);

    signed char transMot = fichierLu.t.trans[256 * 0 + flot[0]]; // 1 realisation avant de rentrer dans la boucle
    while (1)
    {
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
            printf("r%d\t%s\t|    ", -transMot, flot);
            ruleSize = strlen(fichierLu.G.rules[-transMot - 1].rhs);
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
            while ('0'<=pile[indexNbTransition-1] && pile[indexNbTransition-1]<='9')
            {
                indexNbTransition--;
            }
            //printf("ok%d\n",indexNbTransition+1);
            sscanf(&pile[indexNbTransition],"%d",&tmp);
            sprintf(&pile[indexRule+1], "%c%d", fichierLu.G.rules[-transMot - 1].lhs, fichierLu.t.trans[256 * (tmp + 1) - fichierLu.G.rules[-transMot - 1].lhs]);
            nbDigits = 
            pileSize = indexRule+2;
            // digits tout ca la >10
            tmp=fichierLu.t.trans[256 * (tmp + 1) - fichierLu.G.rules[-transMot - 1].lhs];
            arbreSize = construire_arbre(arbre,pile,fichierLu.G.rules[-transMot - 1], &arbreSize);
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

    free(pile);
    free(flot);
    printf("%s",arbre);
    printf("\n\n##############################\n\tFin Algo SLR\n##############################\n\n");

    // test 
    
    char *buffer="S(a()S()b())";
    char *oldre="a()S()b()";
    //strcpy(oldre,buffer);
    oldre=buffer;
    printf("oldre:%s\n",oldre);



    return 0;
}