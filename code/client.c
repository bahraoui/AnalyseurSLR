#include "LRGrammar.h"
#include "read_file.h"
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
    strcpy(flot, mot);
    char *pile = (char *)calloc(strlen(mot) * 4, sizeof(char));
    char ruleSize, tmp, indexRule, indexNbTransition, nbDigits;
    char pileSize = 1;
    pile[0] = '0';
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
            //printf("-#%d#",indexRule);
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
            while ('0'<=pile[indexNbTransition] && pile[indexNbTransition]<='9')
            {
                indexNbTransition--;
            }
            //printf("ok%d\n",indexNbTransition+1);
            sscanf(&pile[indexNbTransition+1],"%d",&tmp);
            sprintf(&pile[indexRule+1], "%c%d", fichierLu.G.rules[-transMot - 1].lhs, fichierLu.t.trans[256 * (tmp + 1) - fichierLu.G.rules[-transMot - 1].lhs]);
            nbDigits = 
            pileSize = indexRule+2;
            // digits tout ca la >10
            tmp=fichierLu.t.trans[256 * (tmp + 1) - fichierLu.G.rules[-transMot - 1].lhs];
            transMot = fichierLu.t.trans[256 * (tmp) + flot[0]];
            printf("%s\n", pile);
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
    printf("\n\n##############################\n\tFin Algo SLR\n##############################\n\n");

    // test suppr une partie d'une chaine en gardant son debut et sa fin
    // ne fonctionne que si la partie a supprimer est plus grande que la partie a mettre/remplacer
    // PPP = pile
    // xxx 2 lettres a ajouter
    // ok char a remplacer
    // v1
    /*
    char* ppp = (char*)calloc(15,sizeof(char));
    char* xxx = (char*)calloc(15,sizeof(char));
    strcpy(xxx,"S9");
    char* ok = "a1S2b3"; // str a remplacer
    strcpy(ppp,"0a1S2b3c4"); // str de base, objectif => 0S9c4
    printf("ppp : %s\n",ppp);
    strncpy(&ppp[1],xxx,strlen(xxx));
    printf("ppp : %s\n",ppp);
    strcpy(&ppp[1+strlen(xxx)],&ppp[1+strlen(ok)]);
    printf("ppp : %s\n",ppp);
    */
    // v2
    char *oui = (char *)calloc(50, sizeof(char));
    long nb = 159999999;
    sprintf(oui, "%d", nb);
    printf("oui : %s\n", oui);
    nb = 16;
    sprintf(&oui[2], "%c%d", 'a', nb);
    printf("oui : %s\n", oui);

    //**//

    // v1
    char *mmm = "0a2S3b48a45";
    int li;
    sscanf(&mmm[6], "%d", &li);
    printf(" le li : %d\n", li);
    char x = 236;
    int count = snprintf(NULL, 0, "%i", x);
    printf(" le count : %d\n", count);

    return 0;
}