#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

// Structure représentant une liste
typedef struct {
    int *array;     // Tableau dynamique contenant les éléments de la liste
    int size;       // Taille actuelle de la liste
    int capacity;   // Capacité totale du tableau
} List;

// Initialise une liste avec une capacité initiale
void initialisation(List *list) {
    list->array = (int *)malloc(INITIAL_CAPACITY * sizeof(int)); // Alloue de la mémoire pour le tableau
    list->size = 0;     // Initialise la taille à zéro
    list->capacity = INITIAL_CAPACITY; // Initialise la capacité initiale
}

// Affiche les éléments de la liste
void afficher(List *list) {
    printf("Liste: ");
    for (int i = 0; i < list->size; ++i) {
        printf("%d ", list->array[i]); // Affiche chaque élément du tableau
    }
    printf("\n");
}

// Ajoute un élément au début de la liste
void ajouterdebut(List *list, int element) {
    if (list->size >= list->capacity) {
        list->capacity *= 2; // Double la capacité du tableau si nécessaire
        list->array = (int *)realloc(list->array, list->capacity * sizeof(int)); // Réalloue de la mémoire si nécessaire
    }
    for (int i = list->size; i > 0; --i) {
        list->array[i] = list->array[i - 1]; // Déplace les éléments vers la droite pour faire de la place pour le nouvel élément
    }
    list->array[0] = element; // Place le nouvel élément au début de la liste
    list->size++; // Incrémente la taille de la liste
}

// Ajoute un élément à une position donnée dans la liste
void ajouterposition(List *list, int element, int position) {
    if (position >= 0 && position <= list->size) {
        if (list->size >= list->capacity) {
            list->capacity *= 2;
            list->array = (int *)realloc(list->array, list->capacity * sizeof(int));
        }
        for (int i = list->size; i > position; --i) {
            list->array[i] = list->array[i - 1];
        }
        list->array[position] = element;
        list->size++;
    }
}

// Ajoute un élément à la fin de la liste
void ajouterfin(List *list, int element) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->array = (int *)realloc(list->array, list->capacity * sizeof(int));
    }
    list->array[list->size++] = element;
}

// Supprime le premier élément de la liste
void supprimerdebut(List *list) {
    if (list->size > 0) {
        for (int i = 0; i < list->size - 1; ++i) {
            list->array[i] = list->array[i + 1];
        }
        list->size--;
    }
}

// Supprime l'élément à une position donnée dans la liste
void supprimerposition(List *list, int position) {
    if (position >= 0 && position < list->size) {
        for (int i = position; i < list->size - 1; ++i) {
            list->array[i] = list->array[i + 1];
        }
        list->size--;
    }
}

// Supprime le dernier élément de la liste
void supprimerfin(List *list) {
    if (list->size > 0) {
        list->size--;
    }
}

// Recherche un élément dans la liste
int recherche(List *list, int element) {
    for (int i = 0; i < list->size; ++i) {
        if (list->array[i] == element) {
            return 1; // Retourne vrai si l'élément est trouvé
        }
    }
    return 0; // Retourne faux si l'élément n'est pas trouvé
}

// Écrit les éléments de la liste dans un fichier
void ecriturefichier(List *list, char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < list->size; ++i) {
        fprintf(fichier, "%d ", list->array[i]); // Écrit chaque élément dans le fichier
    }

    fclose(fichier);
    printf("Liste écrite dans le fichier avec succès.\n");
}

// Lit les éléments d'un fichier et les affiche
void lecturefichier(char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s \n",nom_fichier);
        return;
    }

    int valeur;
    printf("Liste lue depuis le fichier %s :",nom_fichier);
    while (fscanf(fichier, "%d", &valeur) != EOF) {
        printf("%d ", valeur); // Affiche chaque élément lu depuis le fichier
    }
    printf("\n");

    fclose(fichier);
}

// Réinitialise la liste en libérant la mémoire allouée et en la réinitialisant
void reinitialiser(List *list) {
    free(list->array); // Libère la mémoire allouée pour le tableau
    initialisation(list); // Réinitialise la liste avec une capacité initiale
}

// Fonction principale
int main() {
    List maListe;
    initialisation(&maListe); // Initialise la liste

    int choix, valeur, position, element;
    char fichier[100];

    while (1) {
        // Affiche le menu d'options
        printf("\nBonjour, opération à effectuer ?\n");
        printf("0 – Afficher\n");
        printf("1 – Insérer un élément au début de la liste\n");
        printf("2 – Insérer un élément dans la liste à une position saisie\n");
        printf("3 – Ajouter un élément à la fin de la liste\n");
        printf("4 – Supprimer un élément au début de la liste\n");
        printf("5 – Supprimer un élément dans la liste à une position saisie\n");
        printf("6 – Supprimer un élément à la fin de la liste\n");
        printf("7 – Rechercher si un élément est dans la liste\n");
        printf("8 – Écrire la liste dans un fichier\n");
        printf("9 – Lire la liste depuis un fichier\n");
        printf("10 – Réinitialiser la liste\n");
        printf("11 – Quitter le programme\n");
        printf("Opération ? ");
        scanf("%d", &choix);

        switch (choix) {
            case 0:
                afficher(&maListe); // Affiche la liste
                break;            
            case 1:
                printf("Valeur de l'élément à insérer au début de la liste : ");
                scanf("%d", &valeur);
                ajouterdebut(&maListe, valeur); // Insère un élément au début de la liste
                break;
            case 2:
                printf("Position de l'élément à insérer : ");
                scanf("%d", &position);
                printf("Valeur de l'élément à insérer : ");
                scanf("%d", &valeur);
                ajouterposition(&maListe, valeur, position); // Insère un élément à une position donnée
                break;
            case 3:
                printf("Valeur à ajouter : ");
                scanf("%d", &valeur);
                ajouterfin(&maListe, valeur); // Ajoute un élément à la fin de la liste
                printf("Valeur ajoutée à la fin de la liste.\n");
                break;
            case 4:
                supprimerdebut(&maListe); // Supprime le premier élément de la liste
                break;
            case 5:
                printf("Position de l'élément à supprimer : ");
                scanf("%d", &position);
                supprimerposition(&maListe, position); // Supprime l'élément à une position donnée
                break;
            case 6:
                supprimerfin(&maListe); // Supprime le dernier élément de la liste
                break;
            case 7:
                printf("Entrez l'élément à rechercher : ");
                scanf("%d", &element);
                if (recherche(&maListe, element)) {
                    printf("L'élément %d est présent dans la liste.\n", element); // Vérifie si un élément est présent dans la liste
                } else {
                    printf("L'élément %d n'est pas présent dans la liste.\n", element);
                }
                break;
            case 8:
                printf("Entrez le nom du fichier pour écrire la liste : ");
                scanf("%s", fichier);
                ecriturefichier(&maListe, fichier); // Écrit la liste dans un fichier
                break;
            case 9:
                printf("Entrez le nom du fichier pour lire la liste : ");
                scanf("%s", fichier);
                lecturefichier(fichier); // Lit la liste depuis un fichier
                break;
            case 10:
                reinitialiser(&maListe); // Réinitialise la liste
                printf("La liste a été réinitialisée.\n");
                break;
            case 11:
                free(maListe.array); // Libère la mémoire allouée pour le tableau
                return 0; // Quitte le programme
            default:
                printf("Choix invalide.\n"); // Affiche un message en cas de choix invalide
        }
    }

    return 0;
}
