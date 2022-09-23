//
// Created by Laurent Debize on 21/09/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

//Fonction qui initialise une file vide
File fileVide() {
    File F;
    F = (File)malloc(sizeof(struct _file));
    if (F == NULL) printf("erreur allocation fileVide");
    F->longueur = 0;
    F->tete = F->queue = NULL;
    return(F);
}

//Fonction qui renvoie la longueur de la file en 0(1) (longueur stockee dans une variable)
int longueur(File F) {
    if (F == NULL)printf("file existe pas - longueur");
    return(F->longueur);
}

//Fonction qui enfile un element dans la File F
void enfiler(File F, int numSommet) {
    Cellule cellule;
    if (F == NULL) printf ("file existe pas - enfiler");

    cellule = (Cellule)malloc(sizeof(struct _cellule));
    if (cellule == NULL) printf("erreur allocation memoire - enfiler");
    cellule->numSommet = numSommet;
    cellule->suivant = NULL;
    if (longueur(F) == 0){
        F->tete = F->queue = cellule;
    }
    else {
        F->queue->suivant = cellule;
        F->queue = cellule;
    }
    ++(F->longueur);
}

//Fonction qui renvoie la tete de la file (sans l'enlever)
typage tete(File F) {
    if (F == NULL || longueur(F) == 0) printf(" File existe pas - tete");
    return(F->tete->element);
}

//Fonction qui enleve la tete de la file sans la renvoyer
void decapiter(File F) {
    Cellule cellule;

    if (F == NULL || longueur(F) == 0)printf("File existe pas - defiler");
    cellule = F->tete;
    if (longueur(F) == 1)
        F->tete = F->queue = NULL;
    else
        F->tete = F->tete->suivant;
    --(F->longueur);
    free(cellule);
}

//Fonction qui enleve la tete de la file ET qui renvoie la tete
typage defiler(File F) {
    Cellule cellule;
    typage element;
    if (F == NULL || longueur(F) == 0) printf("File existe pas - defilement");
    cellule = F->tete;
    element = cellule->numSommet;
    if (longueur(F) == 1){
        F->tete = F->queue = NULL;
    }
    else{
        F->tete = F->tete->suivant;
    }
    free(cellule);
    --(F->longueur);
    return(element);
}

//Fonction qui affiche le contenu d'une file
void afficherFile(File F) {
    Cellule cellule;

    if (F == NULL) printf("erreur ecrireFile");
    cellule = F->tete;
    while (cellule != NULL) {
        printf("%d ", cellule->numSommet);
        cellule = cellule->suivant;
    }
    printf("\n");
}
