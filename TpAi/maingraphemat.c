
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphemat.h"
#include "liregraphe.h"

typedef GrapheMat Graphe;


int menu () {

  printf ("\n\nGRAPHES avec matrices\n\n");

  printf ("0 - Fin du programme\n");
  printf ("1 - Création à partir d'un fichier\n");
  printf ("\n");
  printf ("2 - Initialisation d'un graphe vide\n");
  printf ("3 - Ajout d'un sommet\n");
  printf ("4 - Ajout d'un arc\n");
  printf ("\n");
  printf ("5 - Liste des sommets et des arcs\n");
  printf ("6 - Destruction du graphe\n");
  printf ("7 - Parcours en profondeur d'un graphe\n");
  printf ("\n");
  printf ("8  - Floyd \n");
  printf ("9  - parcoursLargeur \n");
  printf ("11  - Profondeur limited \n");
  printf ("12  - Profondeur iterative limited \n");
  printf("13 - Uniform Cost\n");
  printf("14 - A*\n");
  printf("15 - IDA*\n");
  printf("16 - Escalade 2-opt\n");
  printf("17 - Perceptron mono couche\n");
  printf ("\n");
  printf ("Votre choix ? ");
  int cod; scanf ("%d", &cod); getchar();
  printf ("\n");
  return cod;
}
int main () {
  Graphe* graphe;
  booleen fini = faux;
  int limit;
  while (!fini) {
    switch ( menu() ) {
    case 0:
      fini = vrai;
      break;
    case 1: {  // création à partir d'un fichier
      printf ("Nom du fichier contenant le graphe ? ");
      char nomFe [50];
      scanf  ("%s", nomFe);
      //strcpy (nomFe, "graphe.txt");
      FILE* fe = fopen (nomFe, "r");
      if (fe == NULL) {
        perror (nomFe);
      } else {
        graphe = lireGraphe (fe, 20); // 20 sommets maximum
        fclose (fe);
      }
      } break;
   case 2: {             // création d’un graphe vide
      printf ("Nombre maximum de sommets ? ");
      int nMaxSom; scanf  ("%d", &nMaxSom);
      printf ("0) non valué; 1) graphe valué ? ");
      int value; scanf ("%d", &value);

      graphe = creerGrapheMat (nMaxSom, value);

    } break;
    case 3: {  // ajouter un sommet
      printf ("Nom du sommet à insérer ? ");
      NomSom somD; scanf  ("%s", somD);
      ajouterUnSommet (graphe, somD);
    } break;
    case 4: {  // ajouter un arc
      printf ("Nom du sommet de départ ? ");
      NomSom somD; scanf  ("%s", somD);
      printf ("Nom du sommet d'arrivée ? ");
      NomSom somA; scanf  ("%s", somA);
      int cout;
      if (graphe->value) {
        printf ("Cout de la relation ? ");
        scanf ("%d", &cout);
      } else {
        cout = 0;
      }
      ajouterUnArc (graphe, somD, somA, cout);
    } break;
    case 5:
      ecrireGraphe (graphe);
      break;
    case 6:
      detruireGraphe (graphe);
      break;
    case 7:
      parcoursProfond (graphe);
      break;
    case 8:
     if (graphe->value) {
        printf ("\nLes plus courts chemins\n\n");
          floyd (graphe);
      } else {
        printf ("Graphe non valué\n");
      }
      break;

    case 9:
        parcoursLargeur(graphe);
        break;
    case 11 :
        printf ("limite de la recherche? ");
        scanf ("%d", &limit);
        printf ("Nom du sommet d'arrivée ? ");
        NomSom somA;
        scanf  ("%s", somA);
        profondeurLimite(graphe,limit,somA);
        break;
    case 12 :
        printf ("limite de la recherche? ");
        scanf ("%d", &limit);
        printf ("Nom du sommet d'arrivée ? ");
        scanf  ("%s", somA);
        profondeurIterativeLimited(graphe,limit,somA);
        break;
    case 13 :
        printf ("Nom du sommet d'arrivée ? ");
        scanf  ("%s", somA);
        parcoursUniform(graphe,somA);
        break;
    case 14 :
        printf ("Nom du sommet d'arrivée ? ");
        scanf  ("%s", somA);
        Aheuristique(graphe,somA);
        break;
    case 15 :
        printf ("Nom du sommet d'arrivée ? ");
        scanf  ("%s", somA);
        IterativedeepingA(graphe,somA);
        break;
    case 16:
        escalade_opt(graphe);
        break;
    case 17:
        perceptron();
        break;
    case 18:
        //perceptronMulticouche();
        break;
    }
       // switch
    if (!fini) {
      printf ("\n\nTaper Return pour continuer\n");
      getchar();
    }
  }

return 0;
}
