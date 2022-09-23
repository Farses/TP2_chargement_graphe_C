//
// Created by Laurent Debize on 21/09/2022.
//

#ifndef TP2_CHARGEMENT_GRAPHE_C_CELLULE_H
#define TP2_CHARGEME744NT_GRAPHE_C_CELLULE_H
typedef int typage;

struct _cellule {
    typage element;
    int numSommet ;
    struct _cellule *suivant;
};

typedef struct _cellule* Cellule;
#endif //TP2_CHARGEMENT_GRAPHE_C_CELLULE_H
