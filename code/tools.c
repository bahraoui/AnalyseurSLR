#include "tools.h"

void verif_args(int argc){
    if (argc < 3) // nombre d'arguments trop petit
    {
        printf("USAGE:  ./LRanalyzer [fichier] \"[mot]\"\n\
        fichier:\t-fichier contenant grammaire et tableau SLR\n\
        mot:\t\t-mot a tester sur la grammaire du fichier\n");
        fprintf(stderr, "erreur -- trop peu d'arguments (tableau SLR et mot a tester requis)\n");
        exit(EXIT_FAILURE);
    }
    else if (argc > 3) // nombre d'arguments trop grand
    {
        printf("USAGE:  ./LRanalyzer [fichier] \"[mot]\"\n\
        fichier:\t-fichier contenant grammaire et tableau SLR\n\
        mot:\t\t-mot a tester sur la grammaire du fichier\n");
        fprintf(stderr, "erreur -- trop d'arguments (tableau SLR et mot uniquement)\n");
        exit(EXIT_FAILURE);
    }
}

file_read verification_fichier(char const *argv1){
    char *fichier = (char *)malloc(strlen(argv1) + 1);
    file_read grammaireEtTable;
    strcpy(fichier, argv1);

    FILE *file = fopen(fichier, "r+");
    printf("Lecture du fichier en cours ...\r");
    if (file != NULL) // Fichier existant
    {
        printf("Lecture du fichier en cours ... \xE2\x9C\x94\n");
        printf("Validation du fichier en cours ...\r");
        grammaireEtTable = read_file(fichier);
        printf("Validation du fichier en cours ... \xE2\x9C\x94\n");
        fclose(file);
    }
    else // Fichier inexistant ou impossible d'acces
    {
        printf("Lecture du fichier en cours ... \xE2\x9D\x8C\n");
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", fichier);
        exit(EXIT_FAILURE);
    }
    free(fichier);
    return grammaireEtTable;
}

char* verification_mot(char const *argv2){
    printf("Lecture du mot en cours ...\r");
    char *mot = (char *)calloc(strlen(argv2) + 1, sizeof(char));
    strcpy(mot, argv2);
    printf("Lecture du mot en cours ... \xE2\x9C\x94\n");
    return mot;
}

void affichage_ligne(char* pile, char* flot, signed char transition, size_t tailleMot){
    unsigned char limite = tailleMot - strlen(flot);
    if (transition>0)
    {
        fprintf(stdout,"d%d\t", transition);
    } else
    {
        fprintf(stdout,"r%d\t", -transition);
    }
    for (size_t i = 0; i != limite; i++)
    {
        fprintf(stdout," ");
    }
    fprintf(stdout,"%s    |    %s\n",flot, pile);
}