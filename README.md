# AnalyseurSLR
Ce projet a été réalisé par deux étudiants en IATIC4 (BAC+4) dans le cadre du cours de compilation au sein de l'ISTY.

### Fichiers de test

Nous avons testé notre code sur plusieurs fichiers de tests qui sont disponibles dans le dossier "assets":
* toto
* toto2
* toto3
* toto4
* toto5
  *  Ce fichier est spécial car il traite des cas où il est possible d'avoir un décalage, une réduction ou un GoTo > 9

### Dépendances

* compilateur gcc

### Compilation et lancement du programme

Avant de compiler, vérifier si les dépendances sont dans votre système.

Pour compiler le programme, il suffit d'utiliser la commande suivante dans le dossier "guendouz_bahraoui":
```
make
```

Cette dernière compilera tous les éléments nécessaires et créera un fichier exécutable nommé "LRanalyzer".
Ensuite, pour exécuter le programme, il faut effectuer la commande suivante:
```
./LRanalyzer [fichier] [mot]
```

Les arguments fichier et mot sont obligatoires, une erreur sera levé si il y a trop ou pas assez d'arguments.
* [fichier] le chemin du fichier relatif comportant une grammaire et la table d'analyse LR de cette grammaire selon la convention indiquée dans l'énoncé
* [mot] le mot à analyser

Sortie : Affichage de l'analyseur dans la sortie de fichier standard (dans le terminal)
