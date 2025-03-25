#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date{
    char jour[3];
    char mois[3];
    char annee[5];
}date;

typedef struct Produit{
    char nom_produit[100];
    char ref[100];
    float montant;
    date date_achat;
}produit;

typedef struct Liste{
    produit cellule;
    struct Liste *suiv;
}liste;

liste *creerliste_produit(){
    return NULL;
}

int est_vide(liste *debut){
    if(debut==NULL){
        return 1;
    }
    else return 0;
}

liste *creer_produit(){
    liste *nv=(liste*)malloc(sizeof(liste));
    if(nv==NULL){
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    printf("Donner le nom du produit: ");
    scanf("%s",nv->cellule.nom_produit);
    printf("Donner la référence du produit: ");
    scanf("%s",nv->cellule.ref);
    printf("Donner le montant du produit: ");
    scanf("%f",&nv->cellule.montant);
    printf("Donner la date d'achat du produit: \n");
    printf("Jour: ");
    scanf("%s",nv->cellule.date_achat.jour);
    printf("Mois: ");
    scanf("%s",nv->cellule.date_achat.mois);
    printf("Année: ");
    scanf("%s",nv->cellule.date_achat.annee);
    nv->suiv=NULL;
    return nv;
}

void afficher_produit(liste *produit){
    if(est_vide(produit)){
        printf("la liste est vide\n");
    }else{
            printf("Nom du produit: %s\n",produit->cellule.nom_produit);
            printf("Référence du produit: %s\n",produit->cellule.ref);
            printf("Montant du produit: %f\n",produit->cellule.montant);
            printf("Date d'achat du produit: %s/%s/%s\n",produit->cellule.date_achat.jour,produit->cellule.date_achat.mois,produit->cellule.date_achat.annee);
    }
}

liste *ajouter_debut(liste *debut){

    liste *nv=creer_produit();
    if(est_vide(debut)==1){
        debut=nv;
        return debut;}
    else{
        nv->suiv=debut;
        debut=nv;
        return debut;
    }
}


liste *ajouter_fin(liste *debut){
    if(est_vide(debut)==1){
        debut=creer_produit();
        return debut;
    }
    else{
        liste *ptr=debut;
        liste *nv=creer_produit();
        while(ptr->suiv!=NULL){
            ptr=ptr->suiv;
        }
        ptr->suiv=nv;
        return debut;
    }
}

void afficher_produit_liste(liste *debut){
    liste *ptr=debut;
    while(ptr!=NULL){
        afficher_produit(ptr);
        ptr=ptr->suiv;
    }
}

int longueur(liste *debut){
    int c=0;
    liste *ptr=debut;
    for(ptr=debut;ptr!=NULL;ptr=ptr->suiv){
        c++;
    }
    return c;
}

void filtrer_date(liste *debut, date d){
    liste *ptr=debut;
    while(ptr!=NULL){
        if(strcmp(ptr->cellule.date_achat.jour, d.jour) == 0 && strcmp(ptr->cellule.date_achat.mois, d.mois) == 0 && strcmp(ptr->cellule.date_achat.annee, d.annee) == 0){
            afficher_produit(ptr);
        }
        ptr=ptr->suiv;
    }
}

liste *suppD_liste(liste *debut){
    liste *ptr=debut;
    if(est_vide(debut)==1){
        printf("La liste est vide\n");
        return debut;
    }
    else{
        debut=debut->suiv;
        free(ptr);
        return debut;
    }
}

liste *suppF_liste(liste *debut){
    if(est_vide(debut)==1){
        printf("La liste est vide\n");
        return debut;
    }
    else if(debut->suiv == NULL){
        free(debut);
        return NULL;
    }
    else{
        liste *ptr=debut;
                while(ptr->suiv->suiv!=NULL){
                    ptr=ptr->suiv;
                }
                free(ptr->suiv);
                ptr->suiv = NULL;
                return debut;
            }
        }
liste *rembourser_produit(liste *debut, char *ref){
    if(est_vide(debut)){
        printf("La liste est vide\n");
        return debut;
    }

    liste *ptr = debut;
    if(strcmp(debut->cellule.ref, ref) == 0){
        return suppD_liste(debut);
    }

    liste *temp = NULL;
    while(ptr != NULL && strcmp(ptr->cellule.ref, ref) != 0){
        temp = ptr;
        ptr = ptr->suiv;
    }

    if(ptr == NULL){
        return suppF_liste(debut);
        return debut;
    }

    if(ptr->suiv == NULL){
        return suppF_liste(ptr);
    }
    else{
        temp->suiv = ptr->suiv;
        free(ptr);
        return debut;
    }
}

int main() {
    liste *maListe = creerliste_produit();
    int choix;
    char ref[100];
    date d;

    do {
        printf("\nMenu:\n");
        printf("1. Ajouter un produit au début\n");
        printf("2. Ajouter un produit à la fin\n");
        printf("3. Afficher tous les produits\n");
        printf("4. Supprimer le premier produit\n");
        printf("5. Supprimer le dernier produit\n");
        printf("6. Filtrer les produits par date\n");
        printf("7. Rembourser un produit par référence\n");
        printf("8. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                maListe = ajouter_debut(maListe);
                break;
            case 2:
                maListe = ajouter_fin(maListe);
                break;
            case 3:
                afficher_produit_liste(maListe);
                break;
            case 4:
                maListe = suppD_liste(maListe);
                break;
            case 5:
                suppF_liste(maListe);
                break;
            case 6:
                printf("Donner la date à filtrer:\n");
                printf("Jour: ");
                scanf("%s", d.jour);
                printf("Mois: ");
                scanf("%s", d.mois);
                printf("Année: ");
                scanf("%s", d.annee);
                filtrer_date(maListe, d);
                break;
            case 7:
                printf("Donner la référence du produit à rembourser: ");
                scanf("%s", ref);
                maListe = rembourser_produit(maListe, ref);
                break;
            case 8:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 8);

    return 0;
}








