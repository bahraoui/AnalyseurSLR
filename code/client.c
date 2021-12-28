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
    char *pile = (char *)calloc(strlen(mot) * 4, sizeof(char));
    char *arbre = (char *)calloc(strlen(mot) * 6, sizeof(char));
    char temp, temp2;
    char replace=0, replace2=0;
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
            if (transMot<10)
            {
                pileBuffer[0] = flot[0];
                pileBuffer[1] = transMot + '0'; // int to str (Faire attention si plus de 10 regles)
                //strcat(pile, pileBuffer);
                sprintf(&pile[pileSize],"%c%d",flot[0],transMot);
                pileSize += 2;
            } else
            {
                sprintf(pileBufferNumbers,"%d",transMot);
                pileSize+=strlen(pileBufferNumbers);
                strcat(pile, pileBufferNumbers);
            }
            if (flot[0]!='\0')
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
            // (perso: cas unique)
            // si la regle de la grammaire produit uniquement un caractere vide (epsylon [ex: S -> ])
            if (!strlen(fichierLu.G.rules[-transMot-1].rhs)) 
            {
                pileBuffer[0]=fichierLu.G.rules[-transMot-1].lhs;
                // pile[pileSize-1] correspond au dernier char de pile
                temp=pileSize-1;
                temp2=pile[pileSize-1]-'0';
                j=1;
                while (pile[temp]>='0'&&pile[temp]<='9')
                    temp--;
                while (temp!=pileSize-1)
                {
                    temp2=10*temp2+pile[temp]-'0';
                    temp++;
                }
                sprintf(&pile[pileSize],"%c%d",fichierLu.G.rules[-transMot-1].lhs,fichierLu.t.trans[256 *(pile[pileSize-1]-'0'+1)  - fichierLu.G.rules[-transMot-1].lhs]);
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

                if (replace2==-1)
                {
                    char *ruleModified = (char *)calloc(temp,sizeof(char)); // pour changer les non terminaux (-S) en non terminaux (S)
                    for (j = 0; j < temp; j++)
                    {
                        ruleModified[j]=fichierLu.G.rules[-transMot-1].rhs[j];
                        if (ruleModified[j]<0)
                            ruleModified[j]=-ruleModified[j];
                    }
                    fprintf(stderr, "ERREUR - L'expression de la regle [%c -> %s] n'a pas ete reconnu dans [%s].\n",fichierLu.G.rules[-transMot-1].lhs,ruleModified,pile);
                    exit(EXIT_FAILURE);
                } else
                {
                    sprintf(&pile[pileSize-temp*2],"%c%d",fichierLu.G.rules[-transMot-1].lhs, fichierLu.t.trans[256 *(pile[pileSize-temp*2-1]-'0'+1) - fichierLu.G.rules[-transMot-1].lhs]);
                    pileSize+=2-temp*2;
                    transMot=fichierLu.t.trans[256 *(pile[pileSize-1]-'0') + flot[0]];
                }
                printf("%s\n",pile);
            }
            
            
            // ok

            // fin ok
        }
        // dans le cas ou le flot n'est pas accepte (ex: "aa" avec le fichier toto)
        else if (transMot == 0)
        {
            fprintf(stderr, "ERREUR - mot non accepte-%d--%c-\n",transMot,flot[0]);
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
    //v1
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
    //v2
    char* oui = (char *)calloc(50,sizeof(char));
    long nb = 159999999;
    sprintf(oui,"%d",nb);
    printf("oui : %s\n",oui);
    nb = 16;
    sprintf(&oui[2],"%c%d",'a',nb);
    printf("oui : %s\n",oui);

    //**//

    //v1
    char* mmm = "0a2S3b4";
    char result[15];
    int li;
    sscanf(&mmm[6],"%d",&li);
    printf(" le li : %d\n",li);

    return 0;
}