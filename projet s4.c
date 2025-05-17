#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct d {
    int j;
    int m;
    int y;
} d;

typedef struct maladie {
    char *nom;
    char *symptomes;
    char *traitement;
    char *description;
    char *categorie;
    d date;
    struct maladie *suiv;
    struct maladie *prec;
} mal;

typedef struct patient {
    char nom[50];
    char prenom[50];
    char sexe[10];
    mal *maladie;
    struct patient *suiv;
    struct patient *prec;
} pat;

mal *creermaladie() {
    mal *nv = (mal *)malloc(sizeof(mal));
    if (nv == NULL) {
        printf("Erreur d'allocation memoire pour la maladie !!\n");
        return NULL;
    }

    nv->nom = (char *)malloc(100);
    nv->symptomes = (char *)malloc(256);
    nv->traitement = (char *)malloc(256);
    nv->description = (char *)malloc(512);
    nv->categorie = (char *)malloc(100);

    if (!nv->nom || !nv->symptomes || !nv->traitement || !nv->description || !nv->categorie) {
        printf("Erreur d'allocation memoire pour les champs de maladie !!\n");
        free(nv->nom); free(nv->symptomes); free(nv->traitement); free(nv->description); free(nv->categorie);
        free(nv);
        return NULL;
    }

    nv->suiv = NULL;
    nv->prec = NULL;

    printf("Saisir le nom de votre maladie : ");
    fgets(nv->nom, 100, stdin);
    nv->nom[strcspn(nv->nom, "\n")] = 0;

    printf("Saisir les symptomes de votre maladie (séparés par /) : ");
    fgets(nv->symptomes, 256, stdin);
    nv->symptomes[strcspn(nv->symptomes, "\n")] = 0;

    printf("Saisir le traitement de votre maladie : ");
    fgets(nv->traitement, 256, stdin);
    nv->traitement[strcspn(nv->traitement, "\n")] = 0;

    printf("Saisir la description de votre maladie : ");
    fgets(nv->description, 512, stdin);
    nv->description[strcspn(nv->description, "\n")] = 0;

    printf("Saisir la date d'ajout de votre maladie :\n");
    printf("JOUR : ");
    scanf("%d", &nv->date.j);
    getchar();
    printf("MOIS : ");
    scanf("%d", &nv->date.m);
    getchar();
    printf("ANNEE : ");
    scanf("%d", &nv->date.y);
    getchar();

    printf("Saisir la categorie de votre maladie :\n Cardiovasculaire / Infectieuse / Respiratoire / Autres\n ");
    fgets(nv->categorie, 100, stdin);
    nv->categorie[strcspn(nv->categorie, "\n")] = 0;

    return nv;
}

mal *ajoutD(mal *debut, mal *nv) {
    if (nv == NULL) return debut;
    if (debut == NULL)
        return nv;
    nv->suiv = debut;
    debut->prec = nv;
    return nv;
}

mal *ajoutF(mal *debut, mal *nv) {
    if (nv == NULL) return debut;
    if (debut == NULL)
        return nv;
    mal *ptr = debut;
    while (ptr->suiv != NULL) {
        ptr = ptr->suiv;
    }
    ptr->suiv = nv;
    nv->prec = ptr;
    return debut;
}

mal *ajout_A(mal *debut, mal *nv, char maladie_cible[256]) {
    if (nv == NULL) return debut;

    mal *ptr = debut;
    while (ptr != NULL) {
        if (strcmp(ptr->nom, maladie_cible) == 0) {
            nv->suiv = ptr->suiv;
            nv->prec = ptr;
            if (ptr->suiv != NULL) {
                ptr->suiv->prec = nv;
            }
            ptr->suiv = nv;
            printf("Maladie ajoutée après '%s'.\n", maladie_cible);
            return debut;
        }
        ptr = ptr->suiv;
    }

    printf("Maladie '%s' non trouvée. Impossible d'ajouter après.\n", maladie_cible);
    free(nv->nom);
    free(nv->symptomes);
    free(nv->traitement);
    free(nv->description);
    free(nv->categorie);
    free(nv);
    return debut;
}

void affichage(mal *debut) {
    if (debut == NULL) {
        printf("La liste des maladies est vide !!\n");
        return;
    }
    mal *ptr = debut;
    int i = 1;
    while (ptr != NULL) {
        printf("MALADIE %d :\n", i);
        printf(" \t NOM : %s\n", ptr->nom);
        printf(" \t SYMPTOMES : %s\n", ptr->symptomes);
        printf(" \t TRAITEMENT : %s\n", ptr->traitement);
        printf(" \t DESCRIPTION : %s\n", ptr->description);
         printf(" \t CATEGORIE : %s\n", ptr->categorie);
        printf(" \t DATE : %d/%d/%d\n", ptr->date.j, ptr->date.m, ptr->date.y);
        printf("\n");
        i++;
        ptr = ptr->suiv;
    }
}

void affichage_cat(mal *debut, char cat[100]) {
    if (debut == NULL) {
        printf("Aucune maladie n'est enregistrée pour filtrer !!\n");
        return;
    }
    mal *ptr = debut;
    int i = 1;
    int found = 0;
    while (ptr != NULL) {
        if (strcmp(ptr->categorie, cat) == 0) {
            printf("MALADIE %d :\n", i);
            printf(" \t NOM : %s\n", ptr->nom);
            printf(" \t SYMPTOMES : %s\n", ptr->symptomes);
            printf(" \t TRAITEMENT : %s\n", ptr->traitement);
            printf(" \t DESCRIPTION : %s\n", ptr->description);
            printf(" \t DATE : %d/%d/%d\n", ptr->date.j, ptr->date.m, ptr->date.y);
            printf("\n");
            i++;
            found = 1;
        }
        ptr = ptr->suiv;
    }
    if (!found) {
        printf("Aucune maladie trouvée dans la catégorie '%s' !!\n", cat);
    }
}

mal *recherche_mal_nom(mal *debut, char maladie[256]) {
    if (debut == NULL) {
        printf("La liste des maladies est vide. Aucune recherche possible !!\n");
        return NULL;
    }
    mal *ptr = debut;
    while (ptr != NULL) {
        if (strcmp(ptr->nom, maladie) == 0) {
            return ptr;
        }
        ptr = ptr->suiv;
    }
    printf("Aucune maladie n'est enregistrée avec le nom '%s' !!\n", maladie);
    return NULL;
}

mal *recherche_mal_date(mal *debut, d date) {
    if (debut == NULL) {
        printf("La liste des maladies est vide. Aucune recherche possible !!\n");
        return NULL;
    }
    mal *ptr = debut;
    while (ptr != NULL) {
        if (ptr->date.j == date.j && ptr->date.m == date.m && ptr->date.y == date.y) {
            return ptr;
        }
        ptr = ptr->suiv;
    }
    printf("Aucune maladie n'est enregistrée à la date %d/%d/%d !!\n", date.j, date.m, date.y);
    return NULL;
}

mal *recherche_mal_description(mal *debut, char description[512]) {
    if (debut == NULL) {
        printf("La liste des maladies est vide. Aucune recherche possible !!\n");
        return NULL;
    }
    mal *ptr = debut;
    while (ptr != NULL) {
        if (strcmp(ptr->description, description) == 0) {
            return ptr;
        }
        ptr = ptr->suiv;
    }
    printf("Aucune maladie n'est enregistrée avec cette description !!\n");
    return NULL;
}

mal *recherche_mal_traitement(mal *debut, char traitement[256]) {
    if (debut == NULL) {
        printf("La liste des maladies est vide. Aucune recherche possible !!\n");
        return NULL;
    }
    mal *ptr = debut;
    while (ptr != NULL) {
        if (strcmp(ptr->traitement, traitement) == 0) {
            return ptr;
        }
        ptr = ptr->suiv;
    }
    printf("Aucune maladie n'est enregistrée avec ce traitement !!\n");
    return NULL;
}

mal *modif_mal(mal *debut, char maladie[256]) {
    mal *ptr = debut;
    if (debut == NULL) {
        printf("Aucune maladie n'est enregistrée pour modifier !!\n");
        return NULL;
    }
    while (ptr != NULL) {
        if (strcmp(ptr->nom, maladie) == 0) {
            printf("Maladie '%s' trouvée. Veuillez saisir les nouveaux details:\n", maladie);
            printf("Saisir les nouveaux symptomes de votre maladie (séparés par /) : \n");
            fgets(ptr->symptomes, 256, stdin);
            ptr->symptomes[strcspn(ptr->symptomes, "\n")] = 0;

            printf("Saisir le nouveau traitement:\n");
            fgets(ptr->traitement, 256, stdin);
             ptr->traitement[strcspn(ptr->traitement, "\n")] = 0;

            printf("Saisir la nouvelle description:\n");
            fgets(ptr->description, 512, stdin);
            ptr->description[strcspn(ptr->description, "\n")] = 0;

            printf("Maladie modifiée avec succès.\n");
            return ptr;
        }
        ptr = ptr->suiv;
    }
    printf("Maladie '%s' non trouvée. Aucune modification effectuée !!\n", maladie);
    return NULL;
}

mal *supp_D(mal *debut) {
    if (debut == NULL) {
        printf("La liste des maladies est vide. Aucune suppression possible !!\n");
        return NULL;
    }
    mal *ptr = debut;
    debut = debut->suiv;
    if (debut != NULL) {
        debut->prec = NULL;
    }
    free(ptr->nom);
    free(ptr->symptomes);
    free(ptr->traitement);
    free(ptr->description);
    free(ptr->categorie);
    free(ptr);
    printf("Première maladie supprimée avec succès.\n");
    return debut;
}

void supp_F(mal **debut) {
    if (*debut == NULL) {
        printf("La liste des maladies est vide. Aucune suppression possible!!\n");
        return;
    }

    mal *ptr = *debut;

    if (ptr->suiv == NULL) {
        free(ptr->nom);
        free(ptr->symptomes);
        free(ptr->traitement);
        free(ptr->description);
        free(ptr->categorie);
        free(ptr);
        *debut = NULL;
        printf("Dernière maladie supprimée avec succès (la liste est maintenant vide).\n");
        return;
    }

    while (ptr->suiv != NULL) {
        ptr = ptr->suiv;
    }

    ptr->prec->suiv = NULL;

    free(ptr->nom);
    free(ptr->symptomes);
    free(ptr->traitement);
    free(ptr->description);
    free(ptr->categorie);
    free(ptr);
    printf("Dernière maladie supprimée avec succès.\n");
}

mal *supp_pos(mal *debut, char maladie[256]) {
    mal *ptr = debut;
    if (debut == NULL) {
        printf("La liste des maladies est vide. Aucune suppression possible !!\n");
        return NULL;
    }
    while (ptr != NULL) {
        if (strcmp(ptr->nom, maladie) == 0) {
            if (ptr->prec != NULL) {
                ptr->prec->suiv = ptr->suiv;
            } else {
                debut = ptr->suiv;
            }
            if (ptr->suiv != NULL) {
                ptr->suiv->prec = ptr->prec;
            }
            free(ptr->nom);
            free(ptr->symptomes);
            free(ptr->traitement);
            free(ptr->description);
            free(ptr->categorie);
            free(ptr);
            printf("Maladie '%s' supprimée avec succès.\n", maladie);
            return debut;
        }
        ptr = ptr->suiv;
    }
    printf("Maladie '%s' non trouvée. Aucune suppression effectuée !!\n", maladie);
    return debut;
}

void freeMaladieList(mal *debut) {
    mal *current = debut;
    mal *next;
    while (current != NULL) {
        next = current->suiv;
        free(current->nom);
        free(current->symptomes);
        free(current->traitement);
        free(current->description);
        free(current->categorie);
        free(current);
        current = next;
    }
    printf("Mémoire de la liste des maladies libérée.\n");
}


pat *creerPatient() {
    pat *nv = (pat *)malloc(sizeof(pat));
    if (nv == NULL) {
        printf("Erreur d'allocation memoire pour le patient !!\n");
        return NULL;
    }

    nv->maladie = NULL; // Le patient est créé sans maladie liée par défaut
    nv->suiv = NULL;
    nv->prec = NULL;

    printf("Saisir le nom du patient : ");
    fgets(nv->nom, 50, stdin);
    nv->nom[strcspn(nv->nom, "\n")] = 0;

    printf("Saisir le prenom du patient : ");
    fgets(nv->prenom, 50, stdin);
    nv->prenom[strcspn(nv->prenom, "\n")] = 0;

    printf("Saisir le sexe du patient : ");
    fgets(nv->sexe, 10, stdin);
    nv->sexe[strcspn(nv->sexe, "\n")] = 0;

    printf("Patient créé en mémoire.\n");

    return nv;
}

pat *ajoutDebutPatient(pat *debut, pat *nv) {
    if (nv == NULL) return debut;
    if (debut == NULL) return nv;
    nv->suiv = debut;
    debut->prec = nv;
    return nv;
}

pat *ajoutFinPatient(pat *debut, pat *nv) {
    if (nv == NULL) return debut;
    if (debut == NULL) return nv;
    pat *ptr = debut;
    while (ptr->suiv != NULL) {
        ptr = ptr->suiv;
    }
    ptr->suiv = nv;
    nv->prec = ptr;
    return debut;
}

pat *ajoutApresPatient(pat *debut, pat *nv, char nomPatient[50]) {
     if (nv == NULL) return debut;

    pat *ptr = debut;
    while (ptr != NULL) {
        if (strcmp(ptr->nom, nomPatient) == 0) {
            nv->suiv = ptr->suiv;
            nv->prec = ptr;
            if (nv->suiv != NULL) {
                nv->suiv->prec = nv;
            }
            ptr->suiv = nv;
            printf("Patient ajouté après '%s'.\n", nomPatient);
            return debut;
        }
        ptr = ptr->suiv;
    }
    printf("Patient '%s' non trouvé. Impossible d'ajouter après.\n", nomPatient);
    free(nv);
    return debut;
}


pat *suppDebutPatient(pat *debut) {
    if (debut == NULL) {
        printf("La liste des patients est vide. Aucune suppression possible !\n");
        return NULL;
    }
    pat *ptr = debut;
    debut = debut->suiv;
    if (debut != NULL) {
        debut->prec = NULL;
    }
    free(ptr);
    printf("Premier patient supprimé avec succès.\n");
    return debut;
}

void suppFinPatient(pat **debut) {
    if (*debut == NULL) {
        printf("La liste des patients est vide. Aucune suppression possible !\n");
        return;
    }

    pat *ptr = *debut;

     if (ptr->suiv == NULL) {
        free(ptr);
        *debut = NULL;
        printf("Dernier patient supprimé avec succès (la liste est maintenant vide).\n");
        return;
    }

    while (ptr->suiv != NULL) {
        ptr = ptr->suiv;
    }

    ptr->prec->suiv = NULL;

    free(ptr);
    printf("Dernier patient supprimé avec succès.\n");
}

pat *suppPatientSpecifique(pat *debut, char nomPatient[50]) {
    pat *ptr = debut;
    if (debut == NULL) {
        printf("La liste des patients est vide. Aucune suppression possible !\n");
        return NULL;
    }
    while (ptr != NULL) {
        if (strcmp(ptr->nom, nomPatient) == 0) {
            if (ptr->prec != NULL) {
                ptr->prec->suiv = ptr->suiv;
            } else {
                debut = ptr->suiv;
            }
            if (ptr->suiv != NULL) {
                ptr->suiv->prec = ptr->prec;
            }
            free(ptr);
            printf("Patient '%s' supprimé avec succès.\n", nomPatient);
            return debut;
        }
        ptr = ptr->suiv;
    }
    printf("Patient '%s' non trouvé. Aucune suppression effectuée !\n", nomPatient);
    return debut;
}

pat *recherchePatientParNom(pat *debut, char nomPatient[50]) {
    if (debut == NULL) {
        printf("La liste des patients est vide. Aucune recherche possible !\n");
        return NULL;
    }
    pat *ptr = debut;
    while (ptr != NULL) {
        if (strcmp(ptr->nom, nomPatient) == 0) {
            return ptr;
        }
        ptr = ptr->suiv;
    }
    printf("Patient '%s' non trouvé !\n", nomPatient);
    return NULL;
}

pat *recherchePatientParMaladie(pat *debut, char nomMaladie[256]) {
    if (debut == NULL) {
        printf("La liste des patients est vide. Aucune recherche possible !\n");
        return NULL;
    }
    pat *ptr = debut;
    while (ptr != NULL) {
        if (ptr->maladie != NULL && strcmp(ptr->maladie->nom, nomMaladie) == 0) {
            return ptr;
        }
        ptr = ptr->suiv;
    }
    printf("Aucun patient atteint de la maladie '%s' !\n", nomMaladie);
    return NULL;
}


void affichagePatients(pat *debut) {
    if (debut == NULL) {
        printf("Aucun patient enregistré !\n");
        return;
    }

    pat *ptr = debut;
    int i = 1;

    printf("\n----- Liste de tous les patients -----\n");

    while (ptr != NULL) {
        printf("PATIENT %d :\n", i);
        printf("\t NOM : %s\n", ptr->nom);
        printf("\t PRENOM : %s\n", ptr->prenom);
        printf("\t SEXE : %s\n", ptr->sexe);

        if (ptr->maladie != NULL) {
            printf("\t MALADIE ASSOCIÉE : %s\n", ptr->maladie->nom);
        } else {
            printf("\t Aucun historique médical\n");
        }

        printf("\n");
        i++;
        ptr = ptr->suiv;
    }
}

void affichagePatientNom(pat *debut, char nomPatient[50]) {
    pat *foundPatient = recherchePatientParNom(debut, nomPatient);

    if (foundPatient != NULL) {
        printf("\n----- Informations du Patient '%s' -----\n", nomPatient);
        printf("Nom : %s\n", foundPatient->nom);
        printf("Prénom : %s\n", foundPatient->prenom);
        printf("Sexe : %s\n", foundPatient->sexe);

        if (foundPatient->maladie != NULL) {
            printf("Maladie associée : %s\n", foundPatient->maladie->nom);
            printf("Symptômes : %s\n", foundPatient->maladie->symptomes);
            printf("Traitement : %s\n", foundPatient->maladie->traitement);
             printf("Catégorie : %s\n", foundPatient->maladie->categorie);
             printf("Date d'ajout de la maladie: %d/%d/%d\n", foundPatient->maladie->date.j, foundPatient->maladie->date.m, foundPatient->maladie->date.y);
        } else {
            printf("Aucune maladie enregistrée pour ce patient.\n");
        }
    }
}

void affichagePatientMaladie(pat *debut, char nomMaladie[256]) {
    if (debut == NULL) {
        printf("Aucun patient enregistré pour filtrer !\n");
        return;
    }

    pat *ptr = debut;
    int trouve = 0;

     printf("\n----- Patients atteints de la maladie '%s' -----\n", nomMaladie);

    while (ptr != NULL) {
        if (ptr->maladie != NULL && strcmp(ptr->maladie->nom, nomMaladie) == 0) {
            printf("Nom : %s\n", ptr->nom);
            printf("Prénom : %s\n", ptr->prenom);
            printf("Sexe : %s\n", ptr->sexe);
            printf("---\n");
            trouve = 1;
        }
        ptr = ptr->suiv;
    }

    if (!trouve) {
        printf("Aucun patient trouvé atteint de cette maladie !\n");
    }
}

void freePatientList(pat *debut) {
    pat *current = debut;
    pat *next;
    while (current != NULL) {
        next = current->suiv;
        free(current);
        current = next;
    }
    printf("Mémoire de la liste des patients libérée.\n");
}


// La fonction savePatientToFile a été retirée.


int main() {
    int choix, sous_choix, sous_sous_choix;
    mal *listeMaladies = NULL;
    pat *listePatients = NULL;
    char maladie_nom[256], patient_nom[50], categorie_nom[100];
    d date_recherche;
    // patientFilePath n'est plus nécessaire


    do {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("1 -> Gestion des maladies\n");
        printf("2 -> Gestion des patients\n");
        printf("3 -> Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1: // Début du bloc pour la gestion des maladies
                do {
                    printf("\n----- Gestion des Maladies -----\n");
                    printf("1 -> Ajout de maladie\n");
                    printf("2 -> Modification de maladie\n");
                    printf("3 -> Suppression de maladie\n");
                    printf("4 -> Recherche des maladies\n");
                    printf("5 -> Affichage de toutes les maladies\n");
                    printf("6 -> Affichage des maladies par catégories\n");
                    printf("7 -> Retour au menu principal\n");
                    printf("Choix : ");
                    scanf("%d", &sous_choix);
                    getchar();

                    switch (sous_choix) {
                        case 1:
                            do {
                                printf("\n----- Ajout Maladie -----\n");
                                printf("1 -> Ajout au début\n");
                                printf("2 -> Ajout à la fin\n");
                                printf("3 -> Ajout après une maladie spécifique (par nom)\n");
                                printf("4 -> Retour\n");
                                scanf("%d", &sous_sous_choix);
                                getchar();

                                mal *nvMaladie = NULL;

                                switch (sous_sous_choix) {
                                    case 1:
                                        nvMaladie = creermaladie();
                                        if (nvMaladie != NULL) {
                                            listeMaladies = ajoutD(listeMaladies, nvMaladie);
                                            printf("Maladie ajoutée au début.\n");
                                        }
                                        break;
                                    case 2:
                                        nvMaladie = creermaladie();
                                        if (nvMaladie != NULL) {
                                            listeMaladies = ajoutF(listeMaladies, nvMaladie);
                                             printf("Maladie ajoutée à la fin.\n");
                                        }
                                        break;
                                    case 3:
                                        printf("Saisir le nom de la maladie après laquelle ajouter : ");
                                        fgets(maladie_nom, 256, stdin);
                                        maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                                        nvMaladie = creermaladie();
                                        listeMaladies = ajout_A(listeMaladies, nvMaladie, maladie_nom);
                                        break;
                                    case 4:
                                        break;
                                    default:
                                        printf("Choix invalide.\n");
                                        break;
                                }
                            } while (sous_sous_choix != 4);
                            break;

                         case 2:
                            printf("\n----- Modification Maladie -----\n");
                            printf("Saisir le nom de la maladie à modifier : ");
                            fgets(maladie_nom, 256, stdin);
                            maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                            modif_mal(listeMaladies, maladie_nom);
                            break;


                        case 3:
                            do {
                                printf("\n----- Suppression Maladie -----\n");
                                printf("1 -> Suppression au début\n");
                                printf("2 -> Suppression à la fin\n");
                                printf("3 -> Suppression par nom\n");
                                printf("4 -> Retour\n");
                                scanf("%d", &sous_sous_choix);
                                getchar();

                                switch (sous_sous_choix) {
                                    case 1:
                                        listeMaladies = supp_D(listeMaladies);
                                        break;
                                    case 2:
                                        supp_F(&listeMaladies);
                                        break;
                                    case 3:
                                        printf("Saisir le nom de la maladie à supprimer : ");
                                        fgets(maladie_nom, 256, stdin);
                                        maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                                        listeMaladies = supp_pos(listeMaladies, maladie_nom);
                                        break;
                                    case 4:
                                        break;
                                    default:
                                        printf("Choix invalide.\n");
                                        break;
                                }
                            } while (sous_sous_choix != 4);
                            break;

                        case 4:
                            do {
                                printf("\n----- Recherche Maladie -----\n");
                                printf("1 -> Recherche par nom\n");
                                printf("2 -> Recherche par date\n");
                                printf("3 -> Recherche par description\n");
                                printf("4 -> Recherche par traitement\n");
                                printf("5 -> Retour\n");
                                scanf("%d", &sous_sous_choix);
                                getchar();

                                mal *foundMaladie = NULL;

                                switch (sous_sous_choix) {
                                    case 1:
                                        printf("Saisir le nom de la maladie à rechercher : ");
                                        fgets(maladie_nom, 256, stdin);
                                        maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                                        foundMaladie = recherche_mal_nom(listeMaladies, maladie_nom);
                                        if (foundMaladie != NULL) {
                                            printf("\nMaladie trouvée :\n");
                                            printf(" \t NOM : %s\n", foundMaladie->nom);
                                            printf(" \t SYMPTOMES : %s\n", foundMaladie->symptomes);
                                            printf(" \t TRAITEMENT : %s\n", foundMaladie->traitement);
                                            printf(" \t DESCRIPTION : %s\n", foundMaladie->description);
                                             printf(" \t CATEGORIE : %s\n", foundMaladie->categorie);
                                            printf(" \t DATE : %d/%d/%d\n", foundMaladie->date.j, foundMaladie->date.m, foundMaladie->date.y);
                                        }
                                        break;
                                    case 2:
                                         printf("Saisir la date de la maladie (JJ MM AAAA):\n");
                                         printf("JOUR : ");
                                         scanf("%d", &date_recherche.j);
                                         getchar();
                                         printf("MOIS : ");
                                         scanf("%d", &date_recherche.m);
                                         getchar();
                                         printf("ANNEE : ");
                                         scanf("%d", &date_recherche.y);
                                         getchar();
                                         foundMaladie = recherche_mal_date(listeMaladies, date_recherche);
                                         if (foundMaladie != NULL) {
                                            printf("\nMaladie trouvée :\n");
                                            printf(" \t NOM : %s\n", foundMaladie->nom);
                                            printf(" \t SYMPTOMES : %s\n", foundMaladie->symptomes);
                                            printf(" \t TRAITEMENT : %s\n", foundMaladie->traitement);
                                            printf(" \t DESCRIPTION : %s\n", foundMaladie->description);
                                             printf(" \t CATEGORIE : %s\n", foundMaladie->categorie);
                                            printf(" \t DATE : %d/%d/%d\n", foundMaladie->date.j, foundMaladie->date.m, foundMaladie->date.y);
                                        }
                                        break;
                                    case 3:
                                        printf("Saisir la description de la maladie à rechercher : ");
                                        fgets(maladie_nom, 512, stdin);
                                        maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                                        foundMaladie = recherche_mal_description(listeMaladies, maladie_nom);
                                         if (foundMaladie != NULL) {
                                            printf("\nMaladie trouvée :\n");
                                            printf(" \t NOM : %s\n", foundMaladie->nom);
                                            printf(" \t SYMPTOMES : %s\n", foundMaladie->symptomes);
                                            printf(" \t TRAITEMENT : %s\n", foundMaladie->traitement);
                                            printf(" \t DESCRIPTION : %s\n", foundMaladie->description);
                                             printf(" \t CATEGORIE : %s\n", foundMaladie->categorie);
                                            printf(" \t DATE : %d/%d/%d\n", foundMaladie->date.j, foundMaladie->date.m, foundMaladie->date.y);
                                        }
                                        break;
                                    case 4:
                                        printf("Saisir le traitement de la maladie à rechercher : ");
                                        fgets(maladie_nom, 256, stdin);
                                        maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                                        foundMaladie = recherche_mal_traitement(listeMaladies, maladie_nom);
                                         if (foundMaladie != NULL) {
                                            printf("\nMaladie trouvée :\n");
                                            printf(" \t NOM : %s\n", foundMaladie->nom);
                                            printf(" \t SYMPTOMES : %s\n", foundMaladie->symptomes);
                                            printf(" \t TRAITEMENT : %s\n", foundMaladie->traitement);
                                            printf(" \t DESCRIPTION : %s\n", foundMaladie->description);
                                             printf(" \t CATEGORIE : %s\n", foundMaladie->categorie);
                                            printf(" \t DATE : %d/%d/%d\n", foundMaladie->date.j, foundMaladie->date.m, foundMaladie->date.y);
                                        }
                                        break;
                                    case 5:
                                        break;
                                    default:
                                        printf("Choix invalide.\n");
                                        break;
                                }
                            } while (sous_sous_choix != 5);
                             break;

                        case 5:
                            affichage(listeMaladies);
                            break;

                        case 6:
                            printf("\n----- Affichage par Catégorie -----\n");
                            printf("Saisir la catégorie (Cardiovasculaire / Infectieuse / Respiratoire / Autres) : ");
                            fgets(categorie_nom, 100, stdin);
                            categorie_nom[strcspn(categorie_nom, "\n")] = 0;
                            affichage_cat(listeMaladies, categorie_nom);
                            break;

                        case 7:
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                            break;
                    }
                } while (sous_choix != 7);
                break; // Fin du bloc pour la gestion des maladies

            case 2: // Début du bloc pour la gestion des patients
                 do {
                        printf("\n----- Gestion des Patients -----\n");
                        printf("1 -> Ajout de patient\n");
                        printf("2 -> Suppression de patient (par nom)\n");
                        printf("3 -> Recherche de patient\n");
                        printf("4 -> Affichage de tous les patients\n");
                        printf("5 -> Retour au menu principal\n");
                        printf("Choix : ");
                        scanf("%d", &sous_choix);
                        getchar();

                        switch (sous_choix) {
                            case 1: // Ajout de patient
                                {
                                pat *nvPatient = creerPatient(); // Crée le patient (nom, prénom, sexe, maladie=NULL)
                                if (nvPatient != NULL) {
                                    listePatients = ajoutDebutPatient(listePatients, nvPatient);
                                    printf("Patient ajouté au début de la liste en mémoire.\n");

                                    // --- LOGIQUE DE LIAISON INTERACTIVE RESTAURÉE ---
                                    char link_maladie_choice;
                                    printf("Voulez-vous lier une maladie a ce patient maintenant? (o/n): ");
                                     if (scanf(" %c", &link_maladie_choice) == 1) {
                                        getchar();
                                        if (link_maladie_choice == 'o' || link_maladie_choice == 'O') {
                                            printf("Saisir le nom de la maladie a lier : ");
                                            fgets(maladie_nom, 256, stdin);
                                            maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                                            mal *linkedMaladie = recherche_mal_nom(listeMaladies, maladie_nom);
                                            if (linkedMaladie != NULL) {
                                                nvPatient->maladie = linkedMaladie; // Liaison en mémoire si trouvée
                                                printf("Maladie '%s' liée au patient '%s %s'.\n", linkedMaladie->nom, nvPatient->prenom, nvPatient->nom);
                                            } else {
                                                 // recherche_mal_nom a déjà affiché un message si non trouvé
                                                printf("Aucune maladie liée pour le moment.\n");
                                            }
                                        } else {
                                            // L'utilisateur a répondu 'n', le pointeur maladie reste NULL
                                            printf("Aucune maladie n'a été liée au patient.\n");
                                        }
                                    } else {
                                         fprintf(stderr, "Erreur de lecture pour le choix de lier une maladie.\n");
                                         while (getchar() != '\n' && !feof(stdin));
                                         printf("Aucune maladie n'a été liée en raison d'une erreur de saisie.\n");
                                    }
                                    // --- FIN LOGIQUE LIAISON ---

                                    // NOTE : La sauvegarde dans le fichier n'est PAS appelée ici.

                                }
                                // Gérer l'erreur si creerPatient a retourné NULL
                                else {
                                     printf("La création du patient a échoué.\n");
                                }
                                } // Fin du bloc pour case 1 Ajout patient
                                break;

                           case 2: // Suppression de patient
                                printf("\n----- Suppression Patient -----\n");
                                printf("Saisir le nom du patient à supprimer : ");
                                fgets(patient_nom, 50, stdin);
                                patient_nom[strcspn(patient_nom, "\n")] = 0;
                                listePatients = suppPatientSpecifique(listePatients, patient_nom);
                                break;

                            case 3: // Recherche de patient
                                do {
                                        printf("\n----- Recherche Patient -----\n");
                                        printf("1 -> Par nom\n");
                                        printf("2 -> Par maladie associée\n");
                                        printf("3 -> Retour\n");
                                        scanf("%d", &sous_sous_choix);
                                        getchar();

                                        switch (sous_sous_choix) {
                                            case 1:
                                                printf("Saisir le nom du patient : ");
                                                fgets(patient_nom, 50, stdin);
                                                patient_nom[strcspn(patient_nom, "\n")] = 0;
                                                affichagePatientNom(listePatients, patient_nom);
                                                break;
                                            case 2:
                                                printf("Saisir le nom de la maladie associée : ");
                                                fgets(maladie_nom, 256, stdin);
                                                maladie_nom[strcspn(maladie_nom, "\n")] = 0;
                                                affichagePatientMaladie(listePatients, maladie_nom);
                                                break;
                                            case 3:
                                                break;
                                            default:
                                                 printf("Choix invalide.\n");
                                                 break;
                                        }
                                    } while (sous_sous_choix != 3);
                                break;

                            case 4: // Affichage de tous les patients
                                affichagePatients(listePatients);
                                break;

                            case 5: // Retour
                                break;
                            default:
                                printf("Choix invalide. Veuillez réessayer.\n");
                                break;
                        }
                    } while (sous_choix != 5);
                break; // Fin du bloc pour la gestion des patients


            case 3: // Quitter
                printf("Programme terminé. Libération de la mémoire...\n");
                freeMaladieList(listeMaladies);
                freePatientList(listePatients);
                break;

            default: // Choix invalide menu principal
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 3); // Boucle du menu principal

    return 0;
}