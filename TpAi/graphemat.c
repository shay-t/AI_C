#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphemat.h"
#include "liste.h"
#include "math.h"

booleen  grapheDetruit = vrai;

// remise à zéro du tableau de marquage
static void razMarque (GrapheMat* graphe)
{

    for(int i=0; i<graphe->n; i++) graphe->marque [i] = faux;
}

GrapheMat* creerGrapheMat (int nMax, int value)
{
    // allocation de graphe
    GrapheMat* graphe  = (GrapheMat*) malloc (sizeof (GrapheMat));
    graphe->n       = 0;
    graphe->nMax    = nMax;
    graphe->value   = value; // value : vrai si le graphe est valué
    graphe->nomS    = (NomSom*)  malloc (sizeof(NomSom)  *nMax);
    graphe->marque  = (booleen*) malloc (sizeof(booleen) *nMax);
    graphe->element = (int*)     malloc (sizeof(int)*nMax*nMax);
    graphe->valeur  = (int*)     malloc (sizeof(int)*nMax*nMax);
    // initialisation par défaut
    for (int i=0; i<nMax; i++)
    {
        for(int j=0; j<nMax; j++)
        {
            graphe->element [i*nMax+j] = faux;
            graphe->valeur  [i*nMax+j] = INFINI;
        }
    }
    razMarque (graphe);
    grapheDetruit = faux;
    return graphe;
}


// désallocation d'un graphe
void detruireGraphe (GrapheMat* graphe)
{
    free (graphe->nomS);
    free (graphe->marque);
    free (graphe->element);
    free (graphe->valeur);
    free (graphe);
    grapheDetruit = vrai;
}

static int rang (GrapheMat* graphe, NomSom nom)
{
    int      i      = 0;
    booleen  trouve = faux;
    while ( (i<graphe->n) && !trouve)
    {
        trouve = strcmp (graphe->nomS [i], nom) == 0;
        if (!trouve) i++;
    }
    return trouve ? i : -1;
}

void ajouterUnSommet (GrapheMat* graphe, NomSom nom)
{
    if (rang (graphe, nom) == -1)
    {
        if (graphe->n < graphe->nMax)
        {
            strcpy (graphe->nomS [graphe->n++], nom);
        }
        else
        {
            printf ("\nNombre de sommets > %d\n", graphe->nMax);
        }
    }
    else
    {
        printf ("\n%s déjà défini\n", nom);
    }
}

void ajouterUnArc (GrapheMat* graphe, NomSom somD, NomSom somA, int cout)
{
    int nMax = graphe->nMax;
    int rd = rang (graphe, somD);
    int rg = rang (graphe, somA);
    graphe->element [rd*nMax+rg] = vrai;
    graphe->valeur  [rd*nMax+rg] = cout;
}

void ecrireGraphe (GrapheMat* graphe)
{
    if (grapheDetruit == vrai)
    {
        printf ("Le graphe a ete detruit ou n'est pas encore cree\n");
    }
    else
    {
        int nMax = graphe->nMax;
        for (int i=0; i<graphe->n; i++) printf ("%s ", graphe->nomS[i]);
        printf (";\n");
        for (int i=0; i<graphe->n; i++)
        {
            printf ("\n%s : ", graphe->nomS[i]);
            for (int j=0; j<graphe->n; j++)
            {
                if (graphe->element [i*nMax+j] == vrai)
                {
                    printf ("%s ", graphe->nomS[j]) ;
                    if (graphe->value)
                    {
                        printf (" (%3d) ", graphe->valeur [i*nMax+j] );
                    }
                }
            }
            printf (";");
        }
    }
}

static void profondeur (GrapheMat* graphe, int numSommet)
{
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
    printf ("%s\n", graphe->nomS [numSommet]);
    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
            profondeur (graphe, i);
        }
    }
}


void parcoursProfond (GrapheMat* graphe)
{
    razMarque (graphe);
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]) profondeur (graphe, i);
    }
}



//PArcours en largeur

void parcoursLargeur(GrapheMat* graphe){
    razMarque(graphe);
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]) Largeur (graphe, i);
    }
}



static int comparerCout(Objet* cout1, Objet* cout2){
    int c1=(int) cout1;
    int c2 = (int) cout2;
    if(c1<c2){
        return -1;
    }else if(c1>c2){
        return 1;
    }else{
        return 0 ;
    }
}
static void Largeur(GrapheMat* graphe, int numSommet){

    int nMax=graphe->nMax;
    Liste* li= creerListe(0,NULL,NULL);
    insererEnFinDeListe(li,(void*)numSommet);
    graphe->marque [numSommet] = vrai;
    while(!listeVide(li)){
        int a = (int) extraireEnTeteDeListe(li);
        printf ("%s\n", graphe->nomS [a]);
        for (int i=0; i<graphe->n; i++){
                if(graphe->element[a*nMax + i]== vrai && !graphe->marque[i]){
                    insererEnFinDeListe(li,(void*)i);
                    graphe->marque [i] = vrai;
                }
        }
    }
    detruireListe(li);

}


// exploration itérative en profondeur


static void profondeurIterative (GrapheMat* graphe, int numSommet)
{
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
    printf ("%s\n", graphe->nomS [numSommet]);
    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
            profondeur (graphe, i);
        }
    }
}


void parcoursProfondIterative (GrapheMat* graphe)
{
    razMarque (graphe);
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]) profondeur (graphe, i);
    }
}



static void ecrireEtape (Matrice a, Matrice p, int k, int ns, int nMax)
{
    printf ("Passage par le sommet numéro %d\n", k);

    for (int i=0; i<ns; i++)
    {
        for (int j=0; j<ns; j++)
        {
            if (a [i*nMax+j]==INFINI)
            {
                printf (" %3s", "*");

            }
            else
            {
                printf (" %3d", a [i*nMax+j]);
            }
        }
        printf ("%6s", " ");
        for (int j=0; j<ns; j++)
        {
            printf ("%3d", p [i*nMax+j]);
        }
        printf ("\n");
    }
    printf ("\n");
}

// initialiser les matrices a et p à partir de graphe
static void initFloyd (GrapheMat* graphe, Matrice* a, Matrice* p)
{
    int nMax = graphe->nMax;

    Matrice ta = (int*) malloc (sizeof(int)*nMax*nMax);
    Matrice tp = (int*) malloc (sizeof(int)*nMax*nMax);


    for (int i=0; i<graphe->n; i++)
    {
        for (int j=0; j<graphe->n; j++)
        {
            if(i==j){
                ta [i*nMax+j]=0;
                tp [i*nMax+j] = i;
            }
            else{
                ta [i*nMax+j] = graphe->valeur [i*nMax+j];
                tp [i*nMax+j] = i;
            }
        }
    }
    *a = ta;
    *p = tp;
}



void floyd (GrapheMat* graphe)
{
    Matrice a, p;
    int n = graphe->n;
    int nMax = graphe->nMax;

    initFloyd (graphe, &a, &p);


    for (int k=0; k<n; k++)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if ( (a [i*nMax+k] != INFINI) &&
                        (a [k*nMax+j] != INFINI) &&
                        (a [i*nMax+k] + a [k*nMax+j] < a [i*nMax+j]) )
                {
                    a [i*nMax+j] = a [i*nMax+k] + a [k*nMax+j];
                    p [i*nMax+j] = p [k*nMax+j];
                }
            }
        }
        ecrireEtape (a, p, k, n, nMax);
    }
}



void       explorationCU(GrapheMat* graphe, NomSom nom){
    razMarque(graphe);
}

//Noeud fils
static void noeudsFils(GrapheMat* graphe, int a , Liste* li){
        int nMax=graphe->nMax;
        for (int i=0; i<graphe->n; i++){
                if(graphe->element[a*nMax + i]== vrai && !graphe->marque[i]){
                    insererEnFinDeListe(li,(void*)i);
                    //graphe->marque[i]=vrai;
                }
        }
}



// parcours profondeur limite
static booleen trouve=faux;
static booleen trouve2=faux;
static void LimiRecursive(GrapheMat* graphe, int pos , int limit, NomSom but){
    if(!trouve && !graphe->marque[pos]){
        graphe->marque[pos]=vrai;
        printf("%s ->", graphe->nomS[pos]);

        if(strcmp(graphe->nomS[pos],but)==0){
            trouve = vrai;
            printf("********noeud trouve***********\n");
            return;
        }else if(limit > 0){
            Liste* fils = creerListe(0,NULL,NULL);
            noeudsFils(graphe,pos,fils);
            while(!listeVide(fils)){
                int nouveau= (int)extraireEnTeteDeListe(fils);
                LimiRecursive(graphe,nouveau,limit-1,but);
            }

        }

    }
}


void profondeurLimite(GrapheMat* graphe,int limit,NomSom but){
    razMarque(graphe);
    LimiRecursive(graphe,0,limit,but);
    trouve2=trouve;
    if(!trouve){
        printf("\n Noeud introuvable");
    }
    trouve=faux;
}


void profondeurIterativeLimited(GrapheMat* graphe,int limite,NomSom but){
    int p;
    for(p=0;p<limite;p++){
        printf("Recherche pour la profondeur %d\n",p);
        profondeurLimite(graphe,p,but);
        if(trouve2){
            printf("noeud trouve à la profondeur %d\n",p);
            break;
        }
    }
}





void parcoursUniform(GrapheMat* graphe, NomSom but){

    int* queues=(int*) malloc(sizeof(int));
    *queues=0;
    Liste* listParcourt=creerListe(0,NULL,NULL);
    insererEnOrdre(listParcourt,queues);
    razMarque (graphe);
    graphe->marque [0] = vrai;

    //Les sommets
    int* listSommet=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0;j<graphe->n;j++){
        *(listSommet+j)=j;
    }

    //LISTE DES couts
    int* intCout=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0;j<graphe->n;j++){
        *(intCout+j)=0;
    }

    //Liste du dernier sommet visité
    int* intPrec=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0;j<graphe->n;j++){
    *(intPrec+j)=0;
    }


    while(!listeVide(listParcourt)){
    int* ex=(int*)extraireEnTeteDeListe(listParcourt);
    graphe->marque [*ex] = vrai;
    printf("(%s,%d)\t", graphe->nomS[*ex],intCout[*ex]);
    if(strcmp(but,graphe->nomS[*ex])==0)  break;
    for(int j=0;j<graphe->n;j++){
        if ( (graphe->element [(*ex)*graphe->nMax+j] == vrai) && !graphe->marque [j] )
            {
            if(intCout[j]==0){
                intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                insererEnOrdreCout(listParcourt,listSommet+j,intCout);
                intPrec[j]=*ex;
                }
                else if(intCout[j]>intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j]){
                    intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                    insererEnOrdreCout(listParcourt,listSommet+j,intCout);
                    intPrec[j]=*ex;
                }
            }
    }
    }

    int j=rang (graphe, but);
     printf("\n");
    while(j!=0){
        printf("%s<-",graphe->nomS[j]);
        j= intPrec[j] ;
    }
    printf("%s",graphe->nomS[0]);

}














void Aheuristique(GrapheMat* graphe,NomSom but){
    int* queues=(int*) malloc(sizeof(int));
    *queues=0;
    Liste* listParcourt=creerListe(0,NULL,NULL);
    insererEnOrdre(listParcourt,queues);
    razMarque (graphe);
    graphe->marque [0] = vrai;
    //sommet
    int* listSommet=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0;j<graphe->n;j++){
        *(listSommet+j)=j;
    }
    //cout
    int* intCout=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0;j<graphe->n;j++){
        *(intCout+j)=0;
    }
    // fn
    int* fn=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0;j<graphe->n;j++){
        *(fn+j)=0;
    }
    //h(n)
    int* h=(int*)malloc(sizeof(int)*graphe->n);
    *(h)=366;
    *(h+1)=253;
    *(h+2)=329;
    *(h+3)=374;
    *(h+4)=176;
    *(h+5)=380;
    *(h+6)=193;
    *(h+7)=0;
    *(h+8)=160;
    *(h+9)=100;
    // precedent
    int* intPrec=(int*)malloc(sizeof(int)*graphe->n);
    for(int j=0;j<graphe->n;j++){
        *(intPrec+j)=0;
    }
    while(!listeVide(listParcourt)){
        int* ex=(int*)extraireEnTeteDeListe(listParcourt);
        printf("(%s,%d)\t", graphe->nomS[*ex],fn[*ex]);
        if(strcmp(but,graphe->nomS[*ex])==0)  break;
         graphe->marque [*ex] = vrai;
        for(int j=0;j<graphe->n;j++){
        if ( (graphe->element [(*ex)*graphe->nMax+j] == vrai) && !graphe->marque [j] )
                {
                    if(intCout[j]==0){
                        intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                        fn[j]=intCout[j]+h[j];
                        insererEnOrdreCout(listParcourt,listSommet+j,fn);
                        intPrec[j]=*ex;
                    }
                    else if(intCout[j]>=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j]){
                        intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                        fn[j]=intCout[j]+h[j];
                        insererEnOrdreCout(listParcourt,listSommet+j,fn);
                        intPrec[j]=*ex;
                    }
                }
        }
    }

    int j=rang (graphe, but);
     printf("\n");
    while(j!=0){
        printf("%2s<-",graphe->nomS[j]);
        j= *(intPrec+j) ;
    }
    printf("%s",graphe->nomS[0]);
}


void IterativedeepingA(GrapheMat* graphe,NomSom* but){
    int nmax=graphe->nMax;
    bool trouve = false;
    int L = 366;
    while(L != INFINI){

        printf("\n**************La limite est %d***************\n",L);
        if (trouve) break;

        int* depart=(int*) malloc(sizeof(int));
        *depart=0;
        Liste* listParcourt=creerListe(0,NULL,NULL);
        insererEnOrdre(listParcourt,depart);
        graphe->marque [0] = vrai;
        razMarque(graphe);
        //sommets
        int* intSommet=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(intSommet+j)=j;
        }
        //cout
        int* intCout=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(intCout+j)=0;
        }
        // f(n)
        int* fn=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(fn+j)=0;
        }
        //h(n)
        int* h=(int*)malloc(sizeof(int)*graphe->n);
        *(h)=366;
        *(h+1)=253;
        *(h+2)=329;
        *(h+3)=374;
        *(h+4)=176;
        *(h+5)=380;
        *(h+6)=193;
        *(h+7)=0;
        *(h+8)=160;
        *(h+9)=100;
        //vecteur precedent
        int* intPrec=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(intPrec+j)=0;
        }
        int nextf=INFINI;
        while(!listeVide(listParcourt)){
            int* ex=(int*)extraireEnTeteDeListe(listParcourt);
            printf("(%s,%d)\t", graphe->nomS[*ex],fn[*ex]);
            if(strcmp(but,graphe->nomS[*ex])==0) {
                trouve=true;
                break;
            }
            graphe->marque [*ex] = vrai;
            for(int j=0;j<graphe->n;j++){
            if ( (graphe->element [(*ex)*graphe->nMax+j] == vrai) && !graphe->marque [j]){
                        if(intCout[j]==0){
                            intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                            fn[j]=intCout[j]+h[j];
                            if(fn[j]<L){
                            insererEnOrdreCout(listParcourt,intSommet+j,fn);
                            intPrec[j]=*ex;
                            }
                        }
                        else if(intCout[j]>=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j]){
                            intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                            fn[j]=intCout[j]+h[j];
                            if(fn[j]<L){
                            insererEnOrdreCout(listParcourt,intSommet+j,fn);
                            intPrec[j]=*ex;
                            }
                        }
                        nextf = (nextf < fn[j]) ? nextf : fn[j];

                    }
                    L=nextf;

            }
        }
        int j=rang (graphe, but);
        printf("\n");
        while(j!=0){
            printf("%2s<-",graphe->nomS[j]);
            j= *(intPrec+j) ;
        }
        printf("%2s",graphe->nomS[0]);
    }










    /*int nmax=graphe->nMax;
    bool trouve = false;
    int L = 366;
    while(L != INFINI && !trouve){
        int* depart=(int*) malloc(sizeof(int));
        *depart=0;
        Liste* listParcourt=creerListe(0,NULL,NULL);
        insererEnOrdre(listParcourt,depart);
        graphe->marque [0] = vrai;
        razMarque(graphe);
        //sommets
        int* intSommet=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(intSommet+j)=j;
        }
        //cout
        int* intCout=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(intCout+j)=0;
        }
        // f(n)
        int* fn=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(fn+j)=0;
        }
        //h(n)
        int* h=(int*)malloc(sizeof(int)*graphe->n);
        *(h)=366;
        *(h+1)=253;
        *(h+2)=329;
        *(h+3)=374;
        *(h+4)=176;
        *(h+5)=380;
        *(h+6)=193;
        *(h+7)=0;
        *(h+8)=160;
        *(h+9)=100;
        //vecteur precedent
        int* intPrec=(int*)malloc(sizeof(int)*graphe->n);
        for(int j=0;j<graphe->n;j++){
            *(intPrec+j)=0;
        }
        //printf("\n************* Limite = %d\t Les Sommet explore",L);
        int nextf=INFINI;
        printf("\n la limite est %d\n",L);
        while(!listeVide(listParcourt)){
            int* ex=(int*)extraireEnTeteDeListe(listParcourt);
            printf("(%s,%d)\t", graphe->nomS[*ex],fn[*ex]);
            if(strcmp(but,graphe->nomS[*ex])==0) {
                trouve=true;
                break;
            }
            graphe->marque [*ex] = vrai;

            for(int j=0;j<graphe->n;j++){
            if ( (graphe->element [(*ex)*graphe->nMax+j] == vrai) && !graphe->marque [j] && (intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j]+h[j])<nextf){
                        if(intCout[j]==0){
                            intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                            fn[j]=intCout[j]+h[j];
                            insererEnOrdreCout(listParcourt,intSommet+j,fn);
                            intPrec[j]=*ex;
                        }
                        else if(intCout[j]>=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j]){
                            intCout[j]=intCout[*ex]+graphe->valeur[(*ex)*graphe->nMax+j];
                            fn[j]=intCout[j]+h[j];
                            insererEnOrdreCout(listParcourt,intSommet+j,fn);
                            intPrec[j]=*ex;
                        }
                        if(nextf < fn[j]){
                            nextf = fn[j];
                        }

                    }
                    L=nextf;
            }


        //
        }

        int j=rang (graphe, but);
        printf("\n");
        while(j!=0){
            printf("%2s<-",graphe->nomS[j]);
            j= *(intPrec+j) ;
        }
        printf("%2s",graphe->nomS[0]);
    }*/

}


static float coutTrajet(GrapheMat* graphe,int* t)
{
    float valeurTemp=0;
    int nMax=graphe->nMax;
    for(int i=0; i<(graphe->n); i++)
    {
        valeurTemp+= graphe->valeur[*(t+i)*nMax+*(t+i+1)];
    }
    return valeurTemp;
}

static void permut(int* t,int debut,int fin){
    int temp;

    for(int i=debut; i<(fin+debut+1)/2; i++)
    {
        temp=t[i];
        t[i]=t[(fin+1+debut)-i-1];
        t[(fin+1+debut)-i-1]=temp;
    }

}

static void tabtotab(int* t1, int* t2, int size){
    for(int i=0; i<size ; i++){
        *(t1+i)=*(t2+i);
    }
}


void escalade_opt(GrapheMat* graphe){
    // route initial
    int sommets =graphe->n;
    int* rold=(int*)malloc(sizeof(int)*sommets+1);
    int r[] = {0,3,1,2,4,0};
    float min_path = coutTrajet(graphe,r);
    printf("\n cout trajet initial=  %f\n",coutTrajet(graphe,r));
    printf("\n**********************\n");
    //Permutations
    for(int i=1;i<=sommets-2;i++){
        for (int j=i+1; j<=sommets-1 ; j++){
            tabtotab(rold,r,sommets+1);
            printf("(%d , %d) \n",i,j);
            permut(r,i,j);
            for(int i=0 ; i<=sommets ; i++){
                printf("%d",*(r+i));
            }
            printf("\n cout trajet =  %f\n",coutTrajet(graphe,r));
            printf("\n**********************\n");
            if(coutTrajet(graphe,r)<min_path){
                min_path = coutTrajet(graphe,r);
            }else{
                tabtotab(r,rold,sommets+1);
            }

        }

    }
    printf("\n**********************\n");
    printf("le trajet optimal est : \n");
    for(int i=0 ; i<=sommets ; i++){
        printf("%s ->",graphe->nomS[*(r+i)]);
    }
    printf("le cout du trajet optimal est : %f\n",min_path);

}



static bool isequal(int* t1,int* t2 ,int s){
    bool d=1;
    for (int i=0;i<s; i++){
        if(t1[i]!=t2[i]){
            d=0;
            break;
        }
    }
    return d;
}



void perceptron(){
    //conditions t0
    float w1=0.3;
    float w2=-0.1;
    float teta=0.2;
    float mu=0.1;
    int e1[]={0,0,1,1};
    int e2[]={0,1,0,1};
    int de[]={0,0,0,1};
    int* ds=(int*)malloc(sizeof(int)*4);

    //
    int step=1;
    while(!isequal(ds,de,4)){
        for(int i=0; i<4; i++){
            printf("step %d  : e1[%d] = %d e2[%d]=%d desired d[%d] = %d initial weight w1 = %f w2=%f ",step,i,e1[i],i,e2[i],i,de[i],w1,w2);
            float a=(e1[i]*w1+e2[i]*w2)-teta;
            printf("a=%f",a);
            int x = (a>0 ? 1 : 0 );
            ds[i]=x;
            printf("ds[%d] = %d",i,ds[i]);
            if (x!=de[i]){
                w1 = w1 + mu*(de[i]-x)*e1[i];
                w2=  w2 + mu*(de[i]-x)*e2[i];
            }
            printf(" final weight w1=%f w2=%f \n",w1,w2);

        }
        step++;
        printf("\n--------------------------------------------------------------------------------------------------------------------------------------\n");

    }




}



