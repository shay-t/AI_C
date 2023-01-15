#ifndef DOINCLUDE
#define DOINCLUDE
#include<stdbool.h>
#define faux 0
#define vrai 1
typedef void Objet;
typedef struct element{
	Objet* reference;
	struct element* suivant;
} Element;
typedef struct {
	Element* premier;
	Element* dernier;
	Element* courant;
	int nbElt;
	int type;
	char* (*afficher)(Objet* objet);
	int (*comparer)(Objet* objet1,Objet* objet2);
} Liste;
void initListe(Liste* li,int type, char* (*afficher)(Objet*),int (*comparer)(Objet*,Objet*));
Liste* creerListe(int type,char* (*afficher)(Objet*),int (*comparer)(Objet*,Objet*));
bool listeVide(Liste* li);
int nbElement(Liste* li);
static Element* creerElement();
void insererEnTeteDeListe(Liste* li,Objet* objet);
static void insererApres(Liste* li,Element* precedent,Objet* objet);
void insererEnFinDeListe(Liste* li,Objet* objet);
void ouvrireListe(Liste* li);
bool finListe(Liste* li);
static Element* elementCourant(Liste* li);
Objet* objetCourant(Liste* li);
void listerListe(Liste* li);
Objet* chercherUnObjet(Liste* li,Objet* objetcherche);
Objet* extraireEnTeteDeListe(Liste* li);
static Objet* extraireApres(Liste* li,Element* precedent);
Objet* extraireFinDeListe(Liste* li);
bool extraireObjet(Liste * li,Objet* objet);
void detruireListe(Liste* li);
void inserOrdre(Liste* li, Objet* objet);
void insererEnOrdre(Liste* li, Objet* objet);
void insererEnOrdreCout (Liste* li, int* accesseur,int* intcout);
#endif
