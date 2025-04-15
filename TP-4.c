#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant {
    int id;
    char nom[20];
    float moyenne;
    struct Etudiant *suiv;
    struct Etudiant *prec;
} etudiant;

etudiant *creer() {
    etudiant *nv = (etudiant *)malloc(sizeof(etudiant));
    if (nv == NULL) {
        printf("Erreur d'allocation\n");
        return NULL;
    }
    printf("Entrer l'id de l'etudiant: ");
    scanf("%d", &nv->id);
    printf("Entrer le nom de l'etudiant: ");
    scanf("%s", nv->nom);
    printf("Entrer la moyenne de l'etudiant: ");
    scanf("%f", &nv->moyenne);
    nv->suiv = NULL;
    nv->prec = NULL;
    return nv;
}

int longueur(etudiant *debut) {
    int i = 0;
    etudiant *ptr = debut;
    while (ptr != NULL) {
        i++;
        ptr = ptr->suiv;
    }
    return i;
}

etudiant* ajout_pos(etudiant *debut, etudiant *nv, int pos) {
    if (nv == NULL) {
        return debut;
    }

    int p = 0;
    int max = longueur(debut);
    etudiant *ptr = debut;

    if (pos < 0) {
        return debut;
    }

    if (debut == NULL || pos == 0) {
        nv->suiv = debut;
        nv->prec = NULL;
        if (debut != NULL) {
            debut->prec = nv;
        }
        return nv;
    }

    if (pos >= max) {
        while (ptr->suiv != NULL) {
            ptr = ptr->suiv;
        }
        ptr->suiv = nv;
        nv->prec = ptr;
        nv->suiv = NULL;
        return debut;
    }

    while (ptr != NULL && p < pos - 1) {
        ptr = ptr->suiv;
        p++;
    }

    if (ptr == NULL) {
        return debut;
    }

    nv->suiv = ptr->suiv;
    nv->prec = ptr;

    if (ptr->suiv != NULL) {
        ptr->suiv->prec = nv;
    }

    ptr->suiv = nv;

    return debut;
}

etudiant *sup_pos(etudiant *debut, int position) {
    int i = 0;
    etudiant *ptr = debut;
    if (debut == NULL) {
        return NULL;
    }
    if (position < 0 || position >= longueur(debut)) {
        return debut;
    }
    if (position == 0) {
        debut = debut->suiv;
        if (debut != NULL) {
            debut->prec = NULL;
        }
        free(ptr);
        return debut;
    }
    while (ptr != NULL && i < position) {
        i++;
        ptr = ptr->suiv;
    }
    if (ptr->suiv != NULL) {
        ptr->suiv->prec = ptr->prec;
    }
    if (ptr->prec != NULL) {
        ptr->prec->suiv = ptr->suiv;
    }
    free(ptr);
    return debut;
}

void afficher(etudiant *debut) {
    if (debut == NULL) {
        return;
    } else {
        printf("Liste des etudiants:\n");
        printf("id=%d\n nom=%s\n moyenne=%f\n", debut->id, debut->nom, debut->moyenne);
        afficher(debut->suiv);
    }
}

etudiant *derniere_cellule(etudiant *debut) {
    etudiant *ptr = debut;
    if (debut == NULL) {
        return NULL;
    }
    while (ptr->suiv != NULL) {
        ptr = ptr->suiv;
    }
    return ptr;
}

void afficher_inv(etudiant *debut) {
    etudiant *ptr = derniere_cellule(debut);
    if (ptr == NULL) {
        return;
    }
    printf("Liste des etudiants (inversée):\n");
    while (ptr != NULL) {
        printf("id=%d\n nom=%s\n moyenne=%f\n", ptr->id, ptr->nom, ptr->moyenne);
        ptr = ptr->prec;
    }
}

int chercher(etudiant *debut, int ID) {
    etudiant *ptr = debut;
    while (ptr != NULL) {
        if (ptr->id == ID) {
            printf("Etudiant trouve:\n");
            printf("id=%d\n nom=%s\n moyenne=%f\n", ptr->id, ptr->nom, ptr->moyenne);
            return 1;
        }
        ptr = ptr->suiv;
    }
    return 0;
}

etudiant *tri(etudiant *debut) {
    if (debut == NULL || debut->suiv == NULL) {
        return debut;
    }

    etudiant *ptr1, *ptr2;
    int temp_id;
    char temp_nom[20];
    float temp_moyenne;

    for (ptr1 = debut; ptr1->suiv != NULL; ptr1 = ptr1->suiv) {
        for (ptr2 = ptr1->suiv; ptr2 != NULL; ptr2 = ptr2->suiv) {
            if (ptr1->moyenne > ptr2->moyenne) {
                temp_id = ptr1->id;
                strcpy(temp_nom, ptr1->nom);
                temp_moyenne = ptr1->moyenne;

                ptr1->id = ptr2->id;
                strcpy(ptr1->nom, ptr2->nom);
                ptr1->moyenne = ptr2->moyenne;

                ptr2->id = temp_id;
                strcpy(ptr2->nom, temp_nom);
                ptr2->moyenne = temp_moyenne;
            }
        }
    }
    return debut;
}

etudiant *modifier_moy(etudiant *tete, float nv_moyenne) {
    int position;
    printf("Entrer la position de l'etudiant a modifier: ");
    scanf("%d", &position);

    if (tete == NULL || position < 0 || position >= longueur(tete)) {
        printf("Position invalide ou liste vide\n");
        return tete;
    }

    etudiant *ptr = tete;
    int i = 0;

    while (ptr != NULL && i < position) {
        ptr = ptr->suiv;
        i++;
    }

    if (ptr != NULL) {
        ptr->moyenne = nv_moyenne;
        printf("Moyenne modifiee avec succes.\n");
    }

    return tete;
}


int main() {
    etudiant *debut = NULL;
    etudiant *nv = NULL;
    int choix, pos, ID;
    do {
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher la liste des etudiants\n");
        printf("3. Afficher la liste des etudiants (inversée)\n");
        printf("4. Supprimer un etudiant\n");
        printf("5. Chercher un etudiant par ID\n");
        printf("6. Trier la liste des etudiants par moyenne\n");
        printf("7. Modifier la moyenne d'un etudiant\n");
        printf("8. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                nv = creer();
                if (nv != NULL) {
                    printf("Entrer la position d'insertion: ");
                    scanf("%d", &pos);
                    debut = ajout_pos(debut, nv, pos);
                }
                break;
            case 2:
                afficher(debut);
                break;
            case 3:
                afficher_inv(debut);
                break;
            case 4:
                printf("Entrer la position de l'etudiant a supprimer: ");
                scanf("%d", &pos);
                debut = sup_pos(debut, pos);
                break;
            case 5:
                printf("Entrer l'ID de l'etudiant a chercher: ");
                scanf("%d", &ID);
                chercher(debut, ID);
                break;
            case 6:
                debut = tri(debut);
                break;
            case 7:
                printf("Entrer la nouvelle moyenne: ");
                float nv_moyenne;
                scanf("%f", &nv_moyenne);
                debut = modifier_moy(debut, nv_moyenne);
                break;
            case 8:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 8);

    return 0;
}
