#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fichier.h"
#include "timer.h"


t_d_cell* createCell(uint64_t value, int level) {
    t_d_cell* newcell = (t_d_cell*)malloc(sizeof(t_d_cell));
    newcell->value = value;
    newcell->level = level;
    newcell->nexts = (t_d_cell**)malloc(level * sizeof(t_d_cell*));
    return newcell;
}


t_d_list createEmptyList(int max_level) {
    t_d_list list;
    if (max_level <= 0) {
        max_level = 0;
    }
    list.max_level = max_level;
    list.heads = (t_d_cell **)malloc(max_level * sizeof(t_d_cell*));
    for (int i = 0; i < max_level; i++) {
        list.heads[i] = NULL;
    }
    return list;
}



void insertHead(t_d_list* list, t_d_cell* cell) {
    if (list->heads[0] == NULL) {
        for (int i = 0; i < cell->level; i++) {
            list->heads[i] = cell;
        }
        return;
    }
    for (int i = 0; i < cell->level; i++) {
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;
    }
}



void displayCellLevel(t_d_list list, int level) {
    printf("[list head_%d @-] -->", level);
    t_d_cell* temp = list.heads[level];
    while (temp != NULL) {
        printf(" [ %lu|@-] -->", temp->value);
        temp = temp->nexts[level];
    }
    printf(" NULL\n");
}


void displayAllLevels(t_d_list list) {
    for (int i = 0; i < list.max_level; i++) {
        displayCellLevel(list, i);
    }
}

void destroy_cell(t_d_cell* cell) {
    for (int i = 0; i < cell->level; i++) {
        free(cell->nexts[i]);
    }
    free(cell->nexts);
    free(cell);
}

void destroy_list(t_d_list* ls) {
    for (int i = 0; i < ls->max_level; i++) {
        t_d_cell* cur = ls->heads[i];
        while (cur != NULL) {
            t_d_cell* temp = cur;
            cur = cur->nexts[i];
            destroy_cell(temp);
        }
    }
    free(ls->heads);
}



void insertOrdered(t_d_list *list, t_d_cell* cell) {
    t_d_cell* temp = NULL;
    int i = cell->level - 1;

    for (; i >= 0; --i) {
        if (list->heads[i] == NULL || list->heads[i]->value >= cell->value) {
            cell->nexts[i] = list->heads[i];
            list->heads[i] = cell;
        } else {
            temp = list->heads[i];
            while ((temp->nexts[i] != NULL) && (temp->nexts[i]->value < cell->value)) {
                temp = temp->nexts[i];
            }
            cell->nexts[i] = temp->nexts[i];
            temp->nexts[i] = cell;
        }
    }
}


// Partie 2

int searchCellLevel0(t_d_cell* cell, uint64_t val) {
    while (cell != NULL) {
        if (cell->value == val) {
            return 1;
        }
        cell = cell->nexts[0];
    }
    return 0;
}


int searchLevel0(t_d_list list, uint64_t val) {
    return searchCellLevel0(list.heads[0], val);
}


int searchHLevels(t_d_list list, uint64_t val) {
    for (int level = list.max_level; level >= 0; level--) {
        t_d_cell* temp = list.heads[level];
        while (temp != NULL) {
            if (temp->value == val) {
                return 1;
            }
            temp = temp->nexts[level];
        }
    }
    return 0;
}


// Partie 3


char *SaisirStr() {
    char buffer[100];
    scanf("%99s", buffer);
    return strdup(buffer);
}

t_rendez_vous *CreerRendezVous() {
    t_rendez_vous *rdv = (t_rendez_vous *)malloc(sizeof(t_rendez_vous));
    printf("Saisir la date du rendez-vous (jj mm aaaa) : ");
    scanf("%d %d %d", &rdv->date.jour, &rdv->date.mois, &rdv->date.annee);
    printf("Saisir l'heure du rendez-vous (hh mm) : ");
    scanf("%d %d", &rdv->heureDebut.heure, &rdv->heureDebut.minute);
    printf("Saisir la durée du rendez-vous (hh mm) : ");
    scanf("%d %d", &rdv->duree.heure, &rdv->duree.minute);
    printf("Saisir l'objet du rendez-vous : ");
    rdv->objet = SaisirStr();
    rdv->next = NULL;
    return rdv;
}

t_contact *CreerContact() {
    t_contact *contact = (t_contact *)malloc(sizeof(t_contact));
    printf("Saisir le nom du contact : ");
    contact->nom = SaisirStr();
    printf("Saisir le prénom du contact : ");
    contact->prenom = SaisirStr();
    contact->listeRendezVous = NULL;
    return contact;
}

void PlannifierRendezVous(t_contact *contact, t_rendez_vous *rdv) {
    rdv->next = contact->listeRendezVous;
    contact->listeRendezVous = rdv;
}

void AfficherRendezVous(t_contact *contact) {
    t_rendez_vous *rdv = contact->listeRendezVous;
    while (rdv != NULL) {
        printf("Rendez-vous le %2d/%2d/%4d à %2d:%2d, d'une durée de %2d:%2d, objet : %s\n",
               rdv->date.jour, rdv->date.mois, rdv->date.annee,
               rdv->heureDebut.heure, rdv->heureDebut.minute,
               rdv->duree.heure, rdv->duree.minute, rdv->objet);
        rdv = rdv->next;
    }
}

void InsererAgendaEntry(t_agenda **agenda, t_contact *contact) {
    t_agenda *newEntry = (t_agenda *)malloc(sizeof(t_agenda));
    newEntry->contact = *contact;
    newEntry->next = *agenda;
    *agenda = newEntry;
}



t_agenda *RechercherContact(t_agenda *agenda, char *nom_prenom) {
    while (agenda != NULL) {
        if (strcmp(agenda->contact.nom, nom_prenom) == 0) {
            return agenda;
        }
        agenda = agenda->next;
    }
    return NULL;
}
