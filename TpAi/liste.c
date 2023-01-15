#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"liste.h"
typedef int booleen;
void initListe(Liste* li,int type, char*(*afficher)(Objet*),int (*comparer)(Objet*, Objet*)){
	li->premier=NULL;
	li->courant=NULL;
	li->dernier=NULL;
	li->nbElt=0;
	li->type=type;
	li->afficher=afficher;
	li->comparer=comparer;
}
Liste* creerListe(int type, char* (*afficher)(Objet*),int (*comparer)(Objet*, Objet*)){
	Liste* li=(Liste*)malloc(sizeof(Liste));//allouer de la memoir pour une liste
	initListe(li,type,afficher,comparer);
	return li;
}
int nbElement(Liste* li){
	return li->nbElt;
}
bool listeVide(Liste* li){
	return li->nbElt==0;
}
static Element* creerElement(){
	return (Element*) malloc (sizeof(Element));
}
void insererEnTeteDeListe(Liste* li,Objet* objet){
	Element* nouveau=creerElement();
	nouveau->reference=objet;
	nouveau->suivant=li->premier;
	li->premier=nouveau;
	if(li->dernier==NULL){
		li->dernier=nouveau;
	}
	li->nbElt++;
}
static void insererApres(Liste* li,Element* precedent,Objet* objet){
	if(precedent==NULL){
		insererEnTeteDeListe(li,objet);
	}else{
		Element* nouveau=creerElement();
		nouveau->reference=objet;
		nouveau->suivant=precedent->suivant;
		precedent->suivant=nouveau;
		if(precedent==li->dernier){
			li->dernier=nouveau;
		}
		li->nbElt++;
	}
}
/////////////////////////////////////////////////////
void inserOrdre(Liste* li, Objet* objet){
	ouvrireListe(li);
	Element* el=creerElement();
	while(!finListe(li)){
        Element* ptc=elementCourant(li);
		Objet* objetc=ptc->reference;
		if(li->comparer(objet,objetc)==1){
            el=ptc;
		}
	}
	if(el==NULL){
        insererEnTeteDeListe(li,objet);
	}else{
        insererApres(li,el,objet);
	}

}
//////////////////////////////////////////////////////
void insererEnFinDeListe(Liste* li,Objet* objet){// courant houwa lwl
	insererApres(li,li->dernier,objet);
}
void ouvrireListe(Liste* li){
	li->courant=li->premier;
}
bool finListe(Liste* li){
	return li->courant==NULL;
}
static Element* elementCourant(Liste* li){
	Element* ptc=li->courant;
	if(!finListe(li)){
		li->courant=li->courant->suivant;
	}
	return ptc;
}
Objet* objetCourant(Liste* li){
	Element* ptc=elementCourant(li);
	return ptc==NULL ? NULL: ptc->reference;
}
void listerListe(Liste* li){
	ouvrireListe(li);
	while(!finListe(li)){
		Objet* objet=objetCourant(li);
		printf("%s\n",li->afficher(objet));
	}
}
Objet* chercherUnObjet(Liste* li,Objet* objetcherche){
	bool trouve= false;
	Objet* objet;
	ouvrireListe(li);
	while(!finListe(li) && !trouve){
		objet=objetCourant(li);
		trouve=li->comparer(objetcherche,objet)==0;
	}
	return trouve? objet:NULL;
}
Objet* extraireEnTeteDeListe(Liste* li){
	Element* extrait=li->premier;
	if(!listeVide(li)){
		li->premier=li->premier->suivant;
		if(li->premier==NULL){
			li->dernier=NULL;
		}
		li->nbElt--;
	}
	return extrait /*!=NULL*/?extrait->reference:NULL;
}
static Objet* extraireApres(Liste* li,Element* precedent){
	if(precedent==NULL){
		return extraireEnTeteDeListe(li);
	}else{
		Element* extrait=precedent->suivant;
		if(extrait !=NULL){
			precedent->suivant=extrait->suivant;
			if(extrait==li->dernier){
				li->dernier=precedent;
			}
            li->nbElt--;
		}
		return extrait != NULL  ? extrait->reference : NULL;
	}
}
Objet* extraireFinDeListe(Liste* li){
	Objet* extrait;
	if(listeVide(li)){
		extrait=NULL;
	}else if(li->premier==li->dernier){
		extrait=extraireEnTeteDeListe(li);
	}else{
		Element* ptc=li->premier;
		while(ptc->suivant != li->dernier){
			ptc=ptc->suivant;
		}
		extrait=extraireApres(li,ptc);
	}
	return extrait;
}
bool extraireObjet(Liste * li,Objet* objet){
	Element* precedent=NULL;
	Element* ptc=NULL;
	Objet* extrait;
	bool trouve=false;
	ouvrireListe(li);
	while(!finListe(li) && !trouve){
		precedent=ptc;
		ptc=elementCourant(li);
		trouve=(ptc->reference==objet)? true : false;
	}
	if(trouve){
		extrait=extraireApres(li,precedent);
		return true;
	}else{
		return false;
	}
}
void detruireListe(Liste* li){
	ouvrireListe(li);
	while(!finListe(li)){
		Element* ptc=elementCourant(li);
		free(ptc);
	}
	initListe(li,li->type,li->afficher,li->comparer);
}

//***************************************************

static booleen enOrdre (Objet* objet1, Objet* objet2, booleen ordreCroissant,int (*comparer) (Objet*, Objet*)) {
  booleen ordre = comparer (objet1, objet2) < 0;
  if (!ordreCroissant) ordre = !ordre;
  return ordre;
}

void insererEnOrdre (Liste* li, Objet* objet) {
  if (listeVide (li) ) {   // liste vide
    insererEnTeteDeListe (li, objet);
  } else {
    Element* ptc = li->premier;
    if ( enOrdre (objet, ptc->reference, li->type==1, li->comparer) ) {
      // insertion avant le premier �l�ment
      insererEnTeteDeListe (li, objet);
    } else {
	  // insertion en milieu ou fin de liste
      booleen  trouve = faux;
      Element* prec   = NULL;
      while (ptc != NULL && !trouve) {
        prec   = ptc;
        ptc    = ptc->suivant;
        if (ptc!=NULL) trouve = enOrdre (objet, ptc->reference, li->type==1, li->comparer);
      }
      insererApres (li, prec, objet);
    }
  }
}


static booleen enOrdreCout (int* objet1, int* objet2) {
  booleen ordre =  (*objet1)< (*objet2) ;
  return ordre;
}


void insererEnOrdreCout (Liste* li, int* accesseur,int* intcout) {
  if (listeVide (li) ) {
    insererEnTeteDeListe (li, accesseur);
  } else {
    Element* ptc = li->premier;
    if ( enOrdreCout(intcout+(*accesseur),intcout+ *((int*)ptc->reference))) {
      insererEnTeteDeListe (li, accesseur);
    } else {
      booleen  trouve = faux;
      Element* prec   = NULL;
      while (ptc != NULL && !trouve) {
        prec   = ptc;
        ptc    = ptc->suivant;
        if (ptc!=NULL) trouve =enOrdreCout(intcout+(*accesseur),intcout+ *((int*)ptc->reference));
      }
      // insertion en milieu de liste ou fin de liste
      insererApres (li, prec, accesseur);
    }
  }
}


