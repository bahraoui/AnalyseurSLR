#include "LRGrammar.h"
#include "read_file.h"

int main(int argc, char const *argv[])
{
    /****************************
        Verification du bon nombre d'arguments [Bon nombre = 2]
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
    printf("Validation du fichier en cours ...\n");
    if (file != NULL) // Fichier existant
    {
        printf("--> Le fichier %s existe\n", fichier);
        file_read marwane = read_file(fichier);
        printf("--> Le fichier %s est bien lu\n", fichier);
        fclose(file);
    }
    else // Fichier inexistant ou impossible d'acces
    {
        fprintf(stderr, "--> Impossible d'ouvrir le fichier %s\n", fichier);
        exit(EXIT_FAILURE);
    }

    // Lecture du mot en entree [Second Argument] :
    printf("Validation du mot en cours ...\n");
    char *mot = (char *)malloc(strlen(argv[2]) + 1);
    strcpy(mot, argv[2]);
    printf("--> Le mot est valide ");

    // affichage des valeurs donnees en entree et verifiees :
    printf("\n\nFichier : %s\nMot : %s\n", fichier, mot);

    /****************************
        FIN de Verification du bon nombre d'arguments [Bon nombre = 2]
    ****************************/
    return 0;
}