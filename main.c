#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fichier.h"
#include "timer.h"



void freeStrings(char **time_lvl0, char **time_all_levels) {
    if (*time_lvl0 != NULL) {
        free(*time_lvl0);
        *time_lvl0 = NULL;
    }

    if (*time_all_levels != NULL) {
        free(*time_all_levels);
        *time_all_levels = NULL;
    }
}

int main() {
    FILE *log_file = fopen("log.txt", "w");
    if (log_file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier log.txt\n");
        return 1;
    }

    char format[] = "%d\t%s\t%s\n";
    char *time_lvl0 = NULL;
    char *time_all_levels = NULL;

    for (int level = 7; level <= 16; level++) {
        t_d_list list = createEmptyList(level);

        for (int n = 1000; n <= 100000; n *= 10) {
            startTimer();
            for (int i = 0; i < n; ++i) {
                uint64_t val = rand() % (uint64_t)-1;
                searchLevel0(list, val);
            }
            stopTimer();
            freeStrings(&time_lvl0, &time_all_levels);
            time_lvl0 = getTimeAsString();

            startTimer();
            for (int i = 0; i < n; ++i) {
                uint64_t val = rand() % (uint64_t)-1;
                searchHLevels(list, val);
            }
            stopTimer();
            freeStrings(&time_lvl0, &time_all_levels);
            time_all_levels = getTimeAsString();

            fprintf(log_file, format, level, time_lvl0, time_all_levels);
        }
    }

    fclose(log_file);

    return 0;
}
