#include "LRGrammar.h"
#include "read_file.h"

int main(int argc, char const *argv[])
{
    {
        // recupére l'analyseur SLR que l'on veut en argument

        // bon nombre d'arguments
        if (argc < 3)
        {
            printf("erreur -- trop peu d'arguments (tableau SLR et chaine a tester requis)\n");
            exit(EXIT_FAILURE);
        }
        else if (argc > 3)
        {
            printf("erreur -- trop d'arguments (tableau SLR et chaine a tester requis)\n");
            for (int i = 3; i < argc; i++)
            {
                printf("          %s <-- argument en trop\n", argv[i]);
            }
            exit(EXIT_FAILURE);
        }

        // fichier existe dans assets/

        char *fichier = (char *)malloc(strlen(argv[1]) + 1);
        strcpy(fichier, argv[1]);

        FILE *file = fopen(fichier, "r+");
        printf("Validation du fichier en cours ...\n");
        if (file != NULL)
        {
            printf("--> Le fichier %s existe\n", fichier);
            file_read marwane = read_file(fichier);
            printf("--> Le fichier %s est bien lu\n", fichier);
            fclose(file);
        }
        else
        {
            fprintf(stderr, "--> Impossible d'ouvrir le fichier %s\n", fichier);
            exit(EXIT_FAILURE);
        }

        // chaine de caractere (mot)est valide
        printf("Validation du mot en cours ...\n");
        char *mot = (char *)malloc(strlen(argv[2]) + 1);
        strcpy(mot, argv[2]);
        printf("--> Le mot est valide ");

        printf("\n\nFichier : %s\nMot : %s\n", fichier, mot);
        return 0;
    }
}