#include "LRGrammar.h"
#include "read_file.h"

int main(int argc, char const *argv[])
{
    size_t i, j, v;
    /****************************
     *
     *  Verification du bon nombre d'arguments [Bon nombre = 2]
     *
     ****************************/

    if (argc < 3) // nombre d'arguments trop petit
    {
        fprintf(stderr, "erreur -- trop peu d'arguments (tableau SLR et mot a tester requis)\n");
        exit(EXIT_FAILURE);
    }
    else if (argc > 3) // nombre d'arguments trop grand
    {
        fprintf(stderr, "erreur -- trop d'arguments (tableau SLR et mot a tester requis)\n");
        for (int i = 3; i < argc; i++)
        {
            printf("\t%s <-- argument en trop\n", argv[i]);
        }
        exit(EXIT_FAILURE);
    }

    /*##########################
     *
     * FIN de Verification du bon nombre d'arguments [Bon nombre = 2]
     *
    ##########################*/

    // Verification du fichier en entree [Premier argument]

    char *fichier = (char *)malloc(strlen(argv[1]) + 1);
    strcpy(fichier, argv[1]);

    FILE *file = fopen(fichier, "r+");
    file_read fichierLu;
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
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", fichier);
        exit(EXIT_FAILURE);
    }

    /*##########################
     *
     * FIN de Verification du fichier
     *
    ##########################*/

    // Lecture du mot en entree [Second Argument] :
    printf("Validation du mot en cours ...\r");
    char taille_mot = strlen(argv[2]) + 1;
    // mot a changer par motFlot ou qqch du genre
    char *mot = (char *)calloc(taille_mot, sizeof(char));
    strcpy(mot, argv[2]);
    printf("Validation du mot en cours ... \xE2\x9C\x94\n");

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
    char temp;
    char pileSize = 1;
    char pileBuffer[strlen(mot)];
    pileBuffer[2] = '\0';
    pile[0] = '0';
    printf("\n\n##############################\nDebut Algo SLR\n##############################\n\n\
    \tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s\t|    %s\n", mot, pile);

    // a changer plus tard en while(1) et break si erreur (4eme if) ou accept (2nd if)
    signed char transMot = fichierLu.t.trans[256 * 0 + mot[0]]; // 1 realisation avant de rentrer dans la boucle
    for (i = 0; i < taille_mot+1; i++)
    {
        // dans le cas d'un decalage
        if (transMot > 0)
        {
            pileBuffer[0] = mot[0];
            pileBuffer[1] = transMot + '0'; // int to str (Faire attention si plus de 10 regles)
            strcat(pile, pileBuffer);
            if (mot[0]!='\0')
            {
                memmove(mot, mot + 1, strlen(mot)); // enleve le 1er caracatere de mot
            }
            printf("d%d\t%s\t|    ", transMot, mot);
            printf("%s\n", pile);
            pileSize += 2;
            transMot = fichierLu.t.trans[256 * transMot + mot[0]];
        }
        // dans le cas de fin de mot et d'acceptation
        else if (transMot == -127)
        {
            printf("\t\taccept\n");
        }
        // dans le cas d'une reduction
        else if (transMot < 0)
        {
            printf("r%d\t%s\t|    ", -transMot, mot);
            // (perso: cas unique)
            // si la regle de la grammaire produit uniquement un caractere vide (epsylon [ex: S -> ])
            if (!strlen(fichierLu.G.rules[-transMot-1].rhs)) 
            {
                pileBuffer[0]=fichierLu.G.rules[-transMot-1].lhs;
                // pile[pileSize-1] correspond au dernier char de pile
                pileBuffer[1]=fichierLu.t.trans[256 *(pile[pileSize-1]-'0'+1)  - fichierLu.G.rules[-transMot-1].lhs]+'0'; // [int+'0'] => [int to str]
                strcat(pile,pileBuffer);
                pileSize+=2;
                printf("%s\n",pile);
                transMot = fichierLu.t.trans[256 *(pile[pileSize-1]-'0')  + mot[0]];
            }
            // (perso: cas general)
            // si la regle de la grammaire produit qqch
            else
            {
                /**
                 * a faire dans ce else:
                 * reconnaitre la regle
                 * remplacer cette regle par le non terminal
                 */
                temp = strlen(fichierLu.G.rules[-transMot-1].rhs);
                char *ruleModified = (char *)calloc(temp,sizeof(char)); // pour changer les non terminaux (-S) en non terminaux (S)
                for (j = 0; j < temp; j++)
                {
                    ruleModified[j]=fichierLu.G.rules[-transMot-1].rhs[j];
                    if (ruleModified[j]<0)
                        ruleModified[j]=-ruleModified[j];
                }
                
                char premierCaractereRegle = ruleModified[0];
                // replace et replace2 correspondent aux indices de la pile ou l'expression a ete retrouvee
                char replace=0, replace2=0;
                for (j = 0; j < pileSize; j++) // parcours de la pile, changer par while pile[j]!='\0'
                {
                    if (pile[j]==premierCaractereRegle){
                        replace=j;
                        replace2=0;
                        for (v = j; v < pile[j]*2; v+=2)
                        {
                            if (ruleModified[replace2]!=pile[v]){
                                replace2=-1;
                                break;
                            }
                            replace2++;
                        }
                        if (replace2!=-1)
                            replace2*=2;
                    }
                }
                //pileBuffer[0]=fichierLu.G.rules[-transMot-1].lhs;
                //pileBuffer[1]=fichierLu.t.trans[256 *(pile[pileSize-1]-'0'+1)  - fichierLu.G.rules[-transMot-1].lhs]+'0';
                //strcpy(pileBuffer,"Sx"); // 
                printf(" j'ai trouve : replace1 : %d,replace2: %d:::",replace,replace2);
                                
                printf("%c wow %c\n",fichierLu.G.rules[-transMot-1].lhs,fichierLu.G.rules[-transMot-1].rhs[2]);
                free(ruleModified);
            }
            
            
            // ok

            // fin ok
        }
        // dans le cas ou le mot n'est pas accepte (ex: "aa" avec le fichier toto)
        else if (transMot == 0)
        {
            fprintf(stderr, "ERREUR - mot non accepte\n");
            exit(EXIT_FAILURE);
        }
    }

    free(pile);
    free(flot);
    printf("\n\n##############################\nFin Algo SLR\n##############################\n\n");
    
    // test suppr une partie d'une chaine en gardant son debut et sa fin
    // ne fonctionne que si la partie a supprimer est plus grande que la partie a mettre/remplacer
    char* ppp = (char*)calloc(15,sizeof(char));
    char* xxx = "S9";
    char* ok = "a1S2b3"; // str a remplacer
    strcpy(ppp,"0a1S2b3c4"); // str de base, objectif => 0S9c4
    printf("ppp : %s\n",ppp);
    strncpy(&ppp[1],xxx,strlen(xxx));
    printf("ppp : %s\n",ppp);
    strcpy(&ppp[1+strlen(xxx)],&ppp[1+strlen(ok)]);
    printf("ppp : %s\n",ppp);
    
    //print_table(fichierLu.t, fichierLu.G);

    return 0;
}