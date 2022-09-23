
#include "Graphe.h"
#include "fifo.h"

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num)
{

    printf(" sommet %d :\n",num);

    pArc arc=sommet[num]->arc;

    while(arc!=NULL)
    {
        printf("%d ",arc->sommet);
        arc=arc->arc_suivant;
    }

}

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while(!(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// creer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));
    Newgraphe->nbIndicateur = 0 ;

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->predecesseur= -1;
        Newgraphe->pSommet[i]->indicateur= 0;
        Newgraphe->pSommet[i]->arc=NULL;
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->numeroSommet = i ;
        Newgraphe->pSommet[i]->nombreAction = 0 ;
    }
    return Newgraphe;
}


/* La construction du reseau peut se faire a partir d'un fichier dont le nom est passe en parametre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, orientation, ordre, s1, s2;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs,"%d",&ordre);

    graphe=CreerGraphe(ordre); // creer le graphe d'ordre sommets

    fscanf(ifs,"%d",&taille);
    fscanf(ifs,"%d",&orientation);

    graphe->orientation=orientation;
    graphe->ordre=ordre;

    // creer les aretes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d",&s1,&s2);
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2);

        if(!orientation)
            graphe->pSommet=CreerArete(graphe->pSommet, s2, s1);
    }

    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    if(graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n",graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}

                   /////// BFS ///////
File fileBFS(Graphe* graphe, int sommetInitiale, int verifier) {
    //initialisation
    File file = fileVide();
    int i = sommetInitiale ;
    graphe->nbIndicateur ++ ;
    ///INITIALISER LA 1ER CELLULE
    enfiler(file, i);
    graphe->pSommet[sommetInitiale]->indicateur = graphe->nbIndicateur ;
    int etat = 0 ;

    ///AFIN DE PARCOURIR LA FILE SANS LA CHANGER
    Cellule newCell = file->tete ;
    File newFile = file ;

    ///AFFICHAGE
    if(verifier == 1) {
        printf("Etat de la file : ");
        afficherFile(file);
    }

    while (newFile->queue->suivant != newFile->tete) {
        pSommet temp = graphe->pSommet[i];
        while (temp->arc != NULL) {
            int p = temp->arc->sommet;
            if (graphe->pSommet[p]->indicateur == 0) { //Enfiler un sommet adjacent aux sommets en tête de file.
                enfiler(file, p);
                if(temp->arc != NULL && graphe->pSommet[temp->arc->sommet]->predecesseur != 1) {
                    graphe->pSommet[temp->arc->sommet]->predecesseur = temp->numeroSommet; //Mettre les predecesseurs
                }
            }

            ///POUR PASSER AU SOMMET ADJACENT
            graphe->pSommet[p]->indicateur = graphe->nbIndicateur;
            temp->arc = temp->arc->arc_suivant;
        }
        if(verifier == 1) {
            printf("Etat de la file: ");
            afficherFile(file);
        }
        i = newCell->numSommet ;
        etat++ ;
        if(newCell->suivant != NULL) {
            newCell = newCell->suivant;
        }
        newFile->tete = newFile->tete->suivant ;
   }
    return file;
}
void afficherParcoursBFS(Graphe* g, int sommetInitiale) {
    for(int i = 0 ; i < g->ordre ; i++) { //Parcour des sommets
        if (i != sommetInitiale && g->pSommet[i]->indicateur == g->nbIndicateur) { //Conditions à verifier afin d'afficher le parcours (à cause des composantes connexes, on verifie la indicateur de chaque sommet)
            printf("%d <--", i);
            if (g->pSommet[i]->predecesseur == sommetInitiale) {
                printf(" %d\n", sommetInitiale);
            }
            else {
                int p = g->pSommet[i]->predecesseur;
                do {
                    printf(" %d <--", p);
                    p = g->pSommet[p]->predecesseur;
                } while (p != sommetInitiale);
                printf(" %d\n", sommetInitiale);
            }
        }
    }
}



                   /////// DFS ///////
int fileDFS(pSommet * sommet, int num,int pre)
{
    int tab[80]={-1};
    int i=0;
    sommet[sommet[0]->nombreAction]->predecesseur=pre;
    if (sommet[sommet[0]->nombreAction]->predecesseur==-1){
        sommet[sommet[0]->nombreAction]->predecesseur=num;

    }
    pArc arc=sommet[num]->arc;
    sommet[num]->couleur=10;
    while(arc!=NULL)
    {
        i=i+1;
        tab[i]=arc->sommet;
        arc=arc->arc_suivant;
    }
    if (sommet[tab[i]]->couleur!=10 && tab[i]!=-1) {
        sommet[0]->nombreAction=sommet[0]->nombreAction+1;
        fileDFS(sommet, tab[i],tab[i]);
    }
    else if(sommet[tab[i-1]]->couleur!=10 && tab[i-1]!=-1){
        sommet[0]->nombreAction=sommet[0]->nombreAction+1;
        fileDFS(sommet, tab[i-1],tab[i-1]);
    }
    else if(sommet[tab[1]]->couleur!=10 && tab[1]!=-1) {
        sommet[0]->nombreAction=sommet[0]->nombreAction+1;
        fileDFS(sommet, tab[1],tab[1]);
    }
    else{
        for (int k=0;k<sommet[0]->nombreAction-2;k++){
            if (sommet[k]->couleur!=10){
                sommet[0]->nombreAction=sommet[0]->nombreAction+1;
                fileDFS(sommet, sommet[k]->predecesseur,-1);
            }
        }
    }
}
int afficherDFS(pSommet * sommet,int j,int somDepart){
    for (j;j>0;j--){
        if (sommet[j]->predecesseur!=-1){
            if(sommet[j]->predecesseur != somDepart) {
                printf("%d <- ", sommet[j]->predecesseur);
            }
        }
    }
    printf("%d  ",sommet[somDepart]->valeur);
    printf("\n");
}
int dfs(Graphe* graphe, int somDepart){
    fileDFS(graphe->pSommet, somDepart,somDepart);
    for (int i=0;i<graphe->pSommet[0]->nombreAction+1;i++ ){
        afficherDFS(graphe->pSommet,i,somDepart);
    }
}




void afficherComposantesConnexes(Graphe* g, int sommetInitiale) {
    int verifierNbSommet = 0 ;
    while (verifierNbSommet == 0) {
        for(int j = 0; j < g->ordre ; j++) {
            if(g->pSommet[j]->indicateur == 0) {
                fileBFS(g, j, 0);
                for (int i = 0; i < g->ordre; i++) {
                    if (g->pSommet[i]->indicateur == 1) {
                        verifierNbSommet++;
                    }
                }
                if (verifierNbSommet == g->ordre) {
                    verifierNbSommet = 1;
                } else {

                }
            }
        }
    }
    for(int i = 0; i < g->nbIndicateur ; i++) {
        printf("Composantes Connexes %d :", i + 1);
        for(int j = 0; j < g->ordre ; j++) {
            if (g->pSommet[j]->indicateur == i + 1) {
                printf(" %d,", j);
            }
        }
        printf("\n") ;
    }

}



int main()
{
    Graphe * g=lire_graphe("graphe1_TP2.txt");

    ///appel de la methode pour afficher le graphe

    ///saisie du numero du sommet initial pour lancer un BFS
    printf("numero du sommet initial : \n");

    /// afficher le graphe
    graphe_afficher(g);

    int numSommetInitiale = 0 ;
    printf("Quel est le numero du sommet initiale lors des parcours ?\n") ;
    scanf("%d", &numSommetInitiale) ;

    int choix ;
    do {
        printf("BFS(1) ou DFS(2) ?\n");
        scanf("%d", &choix);
    }while(choix != 1 && choix !=2) ;

    if(choix == 1) {
        //Exemple d'utilisation de file, a vous d'adapter a vos besoins...
        printf("\n----- Etat de la file------\n");
        File maFile = fileBFS(g, numSommetInitiale, 1);
        printf("\n-----Arborescence du graphe------\n");
        afficherParcoursBFS(g, numSommetInitiale);
        printf("\n-----Composantes connexes------\n");
        afficherComposantesConnexes(g, numSommetInitiale);
    }
    else {
        dfs(g, numSommetInitiale) ;
    }

    //exemple_vider_file(maFile);

    return 0;
}
