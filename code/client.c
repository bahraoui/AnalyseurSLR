#include "LRGrammar.h"
#include "read_file.h"

int main(int argc, char const *argv[])
{
    /****************************
     * 
     *  Verification du bon nombre d'arguments [Bon nombre = 2]
     * 
    ****************************/

    if (argc < 3) // nombre d'arguments trop petit
    {
        fprintf(stderr,"erreur -- trop peu d'arguments (tableau SLR et mot a tester requis)\n");
        exit(EXIT_FAILURE);
    }
    else if (argc > 3) // nombre d'arguments trop grand
    {
        fprintf(stderr,"erreur -- trop d'arguments (tableau SLR et mot a tester requis)\n");
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
    char *mot = (char *)malloc(strlen(argv[2]) + 1);
    strcpy(mot, argv[2]);
    printf("Validation du mot en cours ... \xE2\x9C\x94\n");

    // affichage des valeurs donnees en entree et verifiees :
    printf("\nFichier : %s\nMot : %s\n\n##############################\nDebut Algo SLR\n##############################\n\n", fichier, mot);

    /*##########################
     * 
     * FIN de Verification du mot
     * 
    ##########################*/

    /******
    * debut d'algo
    ******/
    char c1 = mot[0];
    char* flot = (char*)calloc(strlen(mot),sizeof(char));
    char* pile = (char*)calloc(strlen(mot)*4,sizeof(char));
    pile[0]='0';
    printf("\tFlot\t|    Pile\n----------------------------------------\n");
    printf("\t%s\t|    %s\n",mot,pile);
    signed char transMot = fichierLu.t.trans[256*0+mot[0]];
    char pileSize=1;
    char pileBuffer[3];
    pileBuffer[2]='\0';
    // dans le cas d'un decalage
    if (transMot>0) 
    {
        pileBuffer[0]=mot[0];
        pileBuffer[1]=transMot+'0';
        strcat(pile,pileBuffer);
        pileSize+=2;
        memmove(mot,mot+1,strlen(mot)); // enleve le 1er caracatere de mot
        printf("d%d\t%s\t|    ",transMot,mot); // afficher
        printf("%s\n",pile);
    }
    // dans le cas de fin de mot et d'acceptation
    else if (transMot==-127){
        printf("\t\taccept");
    }
    // dans le cas d'une reduction
    else if (transMot<0) {
        printf("r%d\t%s\t|    ",-transMot,mot);
    } 
    // dans le cas ou le mot n'est pas accepte (ex: "aa" avec le fichier toto)
    else if (transMot==0)
    {
        fprintf(stderr,"ERREUR - mot non accepte");
        exit(EXIT_FAILURE);
    }
    
    
    
    
    /*
    for (size_t i = 0; i != fichierLu.t.nblines; i++)
    {
    printf("fichierLu.t.trans %c : %d\n",mot[0],fichierLu.t.trans[256*i+mot[0]]);
    }*/

    printf("\n\n##############################\n\n");
    print_table(fichierLu.t,fichierLu.G);
    
    /*
    unsigned short taille_mot = strlen(mot);
    for (size_t i = 0; i < taille_mot; i++)
    {
        printf("i:%d,a:%c\n",i,mot[i]);
    }*/
    printf("accept\n");
   
    return 0;
}