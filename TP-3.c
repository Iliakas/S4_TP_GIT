#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noeud {
    int valeur;
    struct noeud* suiv;
    struct noeud* prec;
} noeud;

noeud* creer(int int_valeur) {
    noeud* new = (noeud*)malloc(sizeof(noeud));
    if (new == NULL) {
        printf("Erreur allocation memoire\n");
        exit(1);
    }
    new->valeur = int_valeur;
    new->suiv = NULL;
    new->prec = NULL;
    return new;
}

void afficherD(noeud* debut) {
    noeud* ptr = debut;
    if (debut == NULL) {
        printf("La liste est vide\n");
    } else {
        while (ptr != NULL) {
            printf("%d ", ptr->valeur);
            ptr = ptr->suiv;
        }
        printf("\n");
    }
}

void afficherI(noeud* debut) {
    noeud* ptr = debut;
    if (debut == NULL) {
        printf("la liste est vide\n");
    } else {
        while (ptr->suiv != NULL) {
            ptr = ptr->suiv;
        }
        while (ptr != NULL) {
            printf("%d ", ptr->valeur);
            ptr = ptr->prec;
        }
        printf("\n");
    }
}

noeud* ajouterD(noeud* debut, int _valeur) {
    noeud* new = creer(_valeur);
    if (debut == NULL) {
        debut = new;
    } else {
        debut->prec = new;
        new->suiv = debut;
        debut = new;
    }
    return debut;
}

noeud* ajouterF(noeud* debut, int _valeur) {
    noeud* new = creer(_valeur);
    if (debut == NULL) {
        debut = new;
    } else {
        noeud* ptr = debut;
        while (ptr->suiv != NULL) {
            ptr = ptr->suiv;
        }
        ptr->suiv = new;
        new->prec = ptr;
    }
    return debut;
}

int taille(noeud* debut) {
    noeud* ptr = debut;
    int i = 0;
    if (debut == NULL) {
        return 0;
    } else {
        while (ptr != NULL) {
            i++;
            ptr = ptr->suiv;
        }
    }
    return i;
}

noeud* insertion(noeud* debut, int pos, int _valeur) {
    noeud* new = creer(_valeur);
    noeud* ptr = debut;
    if (debut == NULL) {
        debut = new;
    } else {
        if (pos == 0) {
            debut = ajouterD(debut, _valeur);
        } else if (pos == taille(debut)) {
            debut = ajouterF(debut, _valeur);
        } else if (pos > 0 && pos < taille(debut)) {
            for (int i = 0; i < pos - 1; i++) {
                ptr = ptr->suiv;
            }
            new->suiv = ptr->suiv;
            if (ptr->suiv != NULL) {
                ptr->suiv->prec = new;
            }
            ptr->suiv = new;
            new->prec = ptr;
        }
    }
    return debut;
}

noeud* rechercher(noeud* debut, int _valeur) {
    noeud* ptr = debut;
    if (debut == NULL) {
        printf("La liste est vide\n");
    } else {
        while (ptr != NULL) {
            if (ptr->valeur == _valeur) {
                return ptr;
            }
            ptr = ptr->suiv;
        }
    }
    return NULL;
}

noeud* suppressionD(noeud* debut) {
    noeud* ptr = debut;
    if (debut == NULL) {
        printf("La liste est vide\n");
    } else {
        debut = debut->suiv;
        if (debut != NULL) {
            debut->prec = NULL;
        }
        free(ptr);
    }
    return debut;
}

noeud* suppressionF(noeud* debut) {
    noeud* ptr = debut;
    if (debut == NULL) {
        printf("La liste est vide\n");
    } else {
        while (ptr->suiv != NULL) {
            ptr = ptr->suiv;
        }
        if (ptr->prec != NULL) {
            ptr->prec->suiv = NULL;
        } else {
            debut = NULL;
        }
        free(ptr);
    }
    return debut;
}

noeud* suppressionP(noeud* debut, int _valeur) {
    noeud* ptr = debut;
    if (debut == NULL) {
        printf("La liste est vide\n");
    } else {
        while (ptr != NULL) {
            if (ptr->valeur == _valeur) {
                if (ptr == debut) {
                    debut = suppressionD(debut);
                    break;
                } else if (ptr->suiv == NULL) {
                    debut = suppressionF(debut);
                    break;
                } else {
                    ptr->prec->suiv = ptr->suiv;
                    ptr->suiv->prec = ptr->prec;
                    free(ptr);
                    break;
                }
            }
            ptr = ptr->suiv;
        }
    }
    return debut;
}

noeud* modifier(noeud* debut, int _valeur) {
    noeud* ptr = debut;
    if (debut == NULL) {
        printf("La liste est vide\n");
    } else {
        while (ptr != NULL) {
            if (ptr->valeur == _valeur) {
                printf("Entrez la nouvelle valeur:");
                scanf("%d", &_valeur);
                ptr->valeur = _valeur;
                break;
            }
            ptr = ptr->suiv;
        }
    }
    return debut;
}

int main() {
    noeud* debut = NULL;
    int choix, valeur, pos;
    do {
        printf("1.Ajouter debut\n");
        printf("2.Ajouter fin\n");
        printf("3.Insertion\n");
        printf("4.Rechercher\n");
        printf("5.Suppression\n");
        printf("6.Modifier\n");
        printf("7.Afficher de debut a fin\n");
        printf("8.Afficher de fin a debut\n");
        printf("9.Quitter\n");
        printf("Entrez votre choix:");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                printf("Entrez la valeur a ajouter:");
                scanf("%d", &valeur);
                debut = ajouterD(debut, valeur);
                break;
            case 2:
                printf("Entrez la valeur a ajouter:");
                scanf("%d", &valeur);
                debut = ajouterF(debut, valeur);
                break;
            case 3:
                printf("Entrez la position et la valeur:");
                scanf("%d %d", &pos, &valeur);
                debut = insertion(debut, pos, valeur);
                break;
            case 4: {
                printf("Entrez la valeur a rechercher:");
                scanf("%d", &valeur);
                noeud* resultat = rechercher(debut, valeur);
                if (resultat != NULL) {
                    printf("Valeur trouvee: %d\n", resultat->valeur);
                } else {
                    printf("Valeur non trouvee\n");
                }
                break;
            }
            case 5:
                printf("Entrez la valeur a supprimer:");
                scanf("%d", &valeur);
                debut = suppressionP(debut, valeur);
                break;
            case 6:
                printf("Entrez la valeur a modifier:");
                scanf("%d", &valeur);
                debut = modifier(debut, valeur);
                break;
            case 7:
                printf("Affichage de la liste de debut a fin:\n");
                afficherD(debut);
                break;
            case 8:
                printf("Affichage de la liste de fin a debut:\n");
                afficherI(debut);
                break;
            case 9:
                printf("Au revoir!\n");
                break;
        }
    } while (choix != 9);
    return 0;
}
