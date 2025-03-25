#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int val;
    struct Noeud* suiv;
} noeud;

noeud *creernoeud(int valeur) {
    noeud *new = (noeud*)malloc(sizeof(noeud));
    if (new == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    new->val = valeur;
    new->suiv = NULL;
    return new;
}

void afficher(noeud *debut) {
    if (debut == NULL) {
        printf("La liste est vide\n");
        return;
    }
    noeud *ptr = debut;
    while (ptr != NULL) {
        printf("La valeur est : %d\n", ptr->val);
        ptr = ptr->suiv;
    }
}

noeud *ajout_debut(noeud *debut, int valeur) {
    noeud *new = creernoeud(valeur);
    new->suiv = debut;
    return new;
}

noeud *ajoutfin(noeud *debut, int valeur) {
    noeud *new = creernoeud(valeur);
    if (debut == NULL) {
        return new;
    }
    noeud *ptr = debut;
    while (ptr->suiv != NULL) {
        ptr = ptr->suiv;
    }
    ptr->suiv = new;
    return debut;
}
int taille(noeud *debut){
    noeud *ptr = debut;
    int i = 0; // Initialize i to 0
    while(ptr != NULL){
        ptr = ptr->suiv;
        i++;
    }
    return i;
}

noeud* insertion(noeud *debut, int pos, int valeur){
    noeud *ptr = debut;
    noeud *new = creernoeud(valeur);
    int t = taille(debut);
    if(pos < 1 || pos > t + 1){
        printf("Position invalide\n");
        return debut;
    }
    if(pos == 1){
        new->suiv = debut;
        return new;
    }
    for(int i = 1; i < pos - 1; i++){
        ptr = ptr->suiv;
    }
    new->suiv = ptr->suiv;
    ptr->suiv = new;
    return debut;
}


void rechercher(noeud *debut, int valeur){
    noeud *ptr = debut;
    while(ptr != NULL){
        if(ptr->val == valeur){
            printf("La valeur est presente.\n");
            return;
        }
        ptr = ptr->suiv;
    }
}

noeud *suppressionD(noeud *debut){
    noeud *ptr=debut;
    noeud *temp=ptr;
    if(debut==NULL){
        printf("La liste est vide.\n");
        return NULL;
    }else{
        debut=debut->suiv;
        free(ptr);
        ptr=NULL;
        return debut;
    }}

noeud* suppressionf(noeud *debut,int valeur){
    noeud *ptr=debut;
    noeud *temp=ptr;
    if(debut==NULL){
        printf("La liste est vide.\n");
        return NULL;
    }
    else{
        while(ptr->suiv!=NULL){
            ptr=ptr->suiv;
            temp=temp->suiv;
        }
        free(ptr);
        temp->suiv=NULL;
        ptr=NULL;
    }
}

noeud* modifierD(noeud *debut,int valeur){
    noeud *ptr=debut;
    if(debut==NULL){
        printf("La liste est vide.\n");
        return NULL;
    }
    else{
        ptr->val=valeur;
        return debut;
    }


}
int main() {
    noeud *liste = NULL;
    liste = ajout_debut(liste, 10);
    liste = ajoutfin(liste, 20);
    liste = ajout_debut(liste, 5);
    liste = modifierD(liste, 15);

    afficher(liste);
    
    return 0;
}
