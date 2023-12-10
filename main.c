#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fichier.h"
#include "timer.h"

int main() {
    FILE *log_file = fopen("log.txt", "w");
    if (log_file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier log.txt\n");
        return 1;
    }

    char format[] = "%d\t%s\t%s\n";
    char *time_lvl0;
    char *time_all_levels;

    for (int level = 7; level <= 10; level++) {
        printf("Niveau testé : %d\n", level);

        t_d_list list = createEmptyList(level);

        for (int nb = 1000; nb <= 100000; nb *= 10) {
            printf("Nombre de recherches : %d\n", nb);

            startTimer();
            for (int i = 0; i < nb; ++i) {
                uint64_t val = rand() % (uint64_t)-1;
                searchLevel0(list, val);
            }
            stopTimer();
            time_lvl0 = getTimeAsString();
            printf("Temps (niveau 0) : %s\n", time_lvl0);

            startTimer();
            for (int i = 0; i < nb; ++i) {
                uint64_t val = rand() % (uint64_t)-1;
                searchHLevels(list, val);
            }
            stopTimer();
            time_all_levels = getTimeAsString();
            printf("Temps (multi-niveaux) : %s\n", time_all_levels);

            fprintf(log_file, format, level, time_lvl0, time_all_levels);

            free(time_lvl0);
            free(time_all_levels);
        }
    }

    fclose(log_file);

    return 0;
}
