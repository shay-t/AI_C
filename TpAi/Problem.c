/*
#include "Problem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char*  ecrireEntier (Objet* objet) {

    int * entier = (int*) objet;
    char* output      = (char*) malloc (sizeof (int));

    snprintf(output, sizeof (int), "%d \n", *entier);
    return output;
}


int comparerInt(Objet* objet1, Objet* objet2) {

    int * a = (int*) objet1;
    int * b = (int*) objet2;

	if (*a > *b)
	{
	  return 1;
	}
    else if (*a == *b)
	{
	  return 0;
	}
	else
	{
	  return -1;
	}
}

Problem * creerProblem(){
    Problem * problem = (Problem*) malloc(sizeof(Problem));
    return problem;
}

void formulerProb(GrapheMat* graphe,NomSom etatInitial, NomSom etatFinal,Problem* problem){
    if(rang(graphe,etatInitial)==-1 || rang(graphe,etatFinal)==-1){
        printf("incorrect\n");
    }else{
     problem->etatBut=etatFinal;
    problem->etatInitial=etatInitial;
    problem->graphe=graphe;
    }


}

Node* createNode(){
    Node* node = (Node*) malloc((sizeof(Node)));
    return node;
}

Node * initNode(Problem* problem,Node* pere,NomSom etat){
    Node* node = createNode();
    node->pere = pere;

    node->rang=rang(problem->graphe,etat);
    if(node->pere=NULL){
        node->coutChemin=0;
    }else{
        int indpere=pere->rang;
        int indnode=node->rang;
        int nMax=problem->graphe->nMax;
        node->coutChemin = pere->coutChemin + problem->graphe->valeur[indpere*indpere+indnode];
    }

    return node;
}
*/


