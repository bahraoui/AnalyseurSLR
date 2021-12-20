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

    // Lecture du mot en entree [Second Argument] :
    printf("Validation du mot en cours ...\r");
    char *mot = (char *)malloc(strlen(argv[2]) + 1);
    strcpy(mot, argv[2]);
    printf("Validation du mot en cours ... \xE2\x9C\x94\n");

    // affichage des valeurs donnees en entree et verifiees :
    printf("\nFichier : %s\nMot : %s\n\n##############################\nDebut Algo SLR\n##############################\n\n", fichier, mot);

    /*##########################
     * 
     * FIN de Verification du bon nombre d'arguments [Bon nombre = 2]
     * 
    ##########################*/

    /******
    * oui
    ******/
    printf("Flot | Pile\n");
    char c1 = mot[0];
    char* flot = (char*)calloc(strlen(mot),sizeof(char));
    char* pile = (char*)calloc(strlen(mot)*2,sizeof(char));

    for (size_t i = 0; i != fichierLu.t.nblines; i++)
    {
    printf("fichierLu.t.trans : %d\n",fichierLu.t.trans[256*i]);
    }

    /*
    unsigned short taille_mot = strlen(mot);
    for (size_t i = 0; i < taille_mot; i++)
    {
        printf("i:%d,a:%c\n",i,mot[i]);
    }*/
    printf("accept\n");
   
    return 0;
}