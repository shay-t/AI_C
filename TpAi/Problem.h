
/*
#include "graphemat.h"
#include "liste.h"
#include <stdio.h>

typedef struct Problem {
    NomSom * etatBut;
    NomSom * etatInitial;
    GrapheMat * graphe;
}Problem;

typedef struct Node{
    struct Node * pere;
    NomSom  etat;
    int rang;
    float coutChemin;
} Node;

typedef struct Result{
    Liste * chemin;
    booleen arret;
    booleen echec;
    float cout;
} Result;

Problem * creerProblem();
void formulerProb(GrapheMat* graphe,NomSom etatInitial, NomSom  etatFinal,Problem* problem);
Node * createNode();
Node * initNode(Problem* problem, Node * pere, NomSom etat);

*/
