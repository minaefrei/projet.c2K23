#ifndef FICHIER_H
#define FICHIER_H

#include <stdint.h>

typedef struct s_d_cell {
    uint64_t value;
    struct s_d_cell** nexts;
    int level;
} t_d_cell;

typedef struct s_d_list {
    t_d_cell** heads;
    int max_level;
} t_d_list;

// Partie 1

t_d_cell* createCell(uint64_t, int);
t_d_list createEmptyList(int);

void insertHead(t_d_list*, t_d_cell*);

void displayCellLevel(t_d_list, int);
void displayAllLevels(t_d_list);
void printAlignedLevels(t_d_list*);

void insertOrdered(t_d_list*, t_d_cell*);

void destroy_cell(t_d_cell*);
void destroy_list(t_d_list*);

// Partie 2

int searchCellLevel0(t_d_cell*, uint64_t);
int searchLevel0(t_d_list, uint64_t);
int searchHLevels(t_d_list, uint64_t, int);


// Partie 3


typedef struct {
    int jour;
    int mois;
    int annee;
} t_date;

typedef struct {
    int heure;
    int minute;
} t_heure;

typedef struct s_rendez_vous {
    t_date date;
    t_heure heureDebut;
    t_heure duree;
    char *objet;
    struct s_rendez_vous *next;
} t_rendez_vous;

typedef struct {
    char *nom;
    char *prenom;
    t_rendez_vous *listeRendezVous;
} t_contact;

typedef struct s_agenda {
    t_contact contact;
    struct s_agenda *next;
} t_agenda;



char *SaisirStr();
t_rendez_vous *CreerRendezVous();
t_contact *CreerContact();
void PlannifierRendezVous(t_contact *contact, t_rendez_vous *rdv);
void AfficherRendezVous(t_contact *contact);
void InsererAgendaEntry(t_agenda **agenda, t_contact *contact);
t_agenda *RechercherContact(t_agenda *agenda, char *nom_prenom);




#endif
