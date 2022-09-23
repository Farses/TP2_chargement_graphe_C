//
// Created by Laurent Debize on 21/09/2022.
//

#ifndef TP2_CHARGEMENT_GRAPHE_C_FIFO_H
#define TP2_CHARGEMENT_GRAPHE_C_FIFO_H

#include "cellule.h"

struct _file {
    int longueur;
    Cellule tete;
    Cellule queue;
};

typedef struct _file* File;

//Fonction qui renvoie si une file est vide ou non
#define fileEstVide(F) ((F)->longueur == 0)

//Fonction qui initialise une file vide
File fileVide();

//Fonction qui renvoie la longueur de la file en 0(1) (longueur stockee dans une variable)
int longueur(File F);

//Fonction qui enfile un element dans la File F
void enfiler(File F, typage element);

//Fonction qui renvoie la tete de la file (sans l'enlever)
typage tete(File F);

//Fonction qui enleve la tete de la file sans la renvoyer
void decapiter(File F);

//Fonction qui enleve la tete de la file ET qui renvoie la tete
typage defiler(File F);

//Fonction qui affiche le contenu d'une file
void afficherFile(File F);


#endif //TP2_CHARGEMENT_GRAPHE_C_FIFO_H
