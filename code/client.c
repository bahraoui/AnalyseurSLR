#include "LRGrammar.h"
#include "read_file.h"
#define MAX_STEPS 150

int main(int argc, char const *argv[])
{
    size_t j, v;
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
    strcpy(flot,mot);
    char *pile = (char *)calloc(strlen(flot) * 4, sizeof(char));
    char temp;
    char pileSize = 1;
    char pileBuffer[2];
    char* pileBufferNumbers = (char*)calloc(fichierLu.t.nblines,sizeof(char));
    pileBuffer[2] = '\0';
    pile[0] = '0';
    printf("\n\n##############################\nDebut Algo SLR\n##############################\n\n\
    \tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s\t|    %s\n", flot, pile);

    signed char transMot = fichierLu.t.trans[256 * 0 + flot[0]]; // 1 realisation avant de rentrer dans la boucle
    while(1)
    {
        // dans le cas d'un decalage
        if (transMot > 0)
        {
            pileBuffer[0] = flot[0];
            if (transMot<10)
            {
                pileBuffer[1] = transMot + '0'; // int to str (Faire attention si plus de 10 regles)
            } else
            {
                sprintf(pileBufferNumbers,"%d",transMot);
            }
            strcat(pile, pileBuffer);
            if (flot[0]!='\0')
            {
                memmove(flot, flot + 1, strlen(flot)); // enleve le 1er caracatere de flot
            }
            printf("d%d\t%s\t|    ", transMot, flot);
            printf("%s\n", pile);
            pileSize += 2;
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
                transMot = fichierLu.t.trans[256 *(pile[pileSize-1]-'0')  + flot[0]];
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
                j=0;
                //for (j = 0; j < pileSize; j++) // parcours de la pile, changer par while pile[j]!='\0'
                while(pile[j]!='\0')
                {
                    printf("pilesize:%d",pileSize);
                    if (pile[j]==premierCaractereRegle){
                        replace=j;
                        replace2=0;
                        printf("--temp:%d,j:%d--",temp,j);
                        for (v = j; v < (temp*2)+j; v+=2)
                        {
                            printf("--v:%d--",v);
                            if (ruleModified[replace2]!=pile[v]){
                                printf("--%c#%d--",ruleModified[replace2],v);
                                break;
                            }
                            replace2++;
                        }
                        if (replace2!=-1)
                            replace2*=2;
                    }
                    j++;
                }
                //pileBuffer[0]=fichierLu.G.rules[-transMot-1].lhs;
                //pileBuffer[1]=fichierLu.t.trans[256 *(pile[pileSize-1]-'0'+1)  - fichierLu.G.rules[-transMot-1].lhs]+'0';
                //strcpy(pileBuffer,"Sx"); // 
                if (replace2==0)
                {
                    fprintf(stderr, "ERREUR - L'expression de la regle [%c -> %s] n'a pas ete reconnu dans [%s].\n",fichierLu.G.rules[-transMot-1].lhs,ruleModified,pile);
                    exit(EXIT_FAILURE);
                } else
                {
                    pileBuffer[0]=fichierLu.G.rules[-transMot-1].lhs;
                    pileBuffer[1]=fichierLu.t.trans[256 *(pile[replace-1]-'0'+1)  - fichierLu.G.rules[-transMot-1].lhs]+'0';
                    strncpy(&pile[replace],pileBuffer,2);
                    strcpy(&pile[replace+2], &pile[replace+strlen(fichierLu.G.rules[-transMot-1].rhs)*2]);
                    pileSize+=2-strlen(fichierLu.G.rules[-transMot-1].rhs)*2;
                    transMot=fichierLu.t.trans[256 *(pile[pileSize-1]-'0') + flot[0]];
                }
                //printf(" j'ai trouve : replace1 : %d,replace2: %d:::",replace,replace2);
                printf("%s\n",pile);
                free(ruleModified);
            }
            
            
            // ok

            // fin ok
        }
        // dans le cas ou le flot n'est pas accepte (ex: "aa" avec le fichier toto)
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
    // PPP = pile
    // xxx 2 lettres a ajouter
    // ok char a remplacer
    char* ppp = (char*)calloc(15,sizeof(char));
    char* xxx = (char*)calloc(15,sizeof(char));
    strcpy(xxx,"S:\0p4");
    strcpy(xxx,"S9");
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