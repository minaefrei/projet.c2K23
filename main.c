#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fichier.h"
//#include "timer.h"


int main() {

    t_d_list list = createEmptyList(4);
    printf("Liste après création :\n");
    displayAllLevels(list);


    insertOrdered(&list, createCell(91, 1));
    insertOrdered(&list, createCell(67, 1));
    insertOrdered(&list, createCell(88, 2));
    insertOrdered(&list, createCell(22, 3));
    insertOrdered(&list, createCell(5, 4));

    displayAllLevels(list);


    uint64_t val;
    printf("Entrez une valeur à rechercher dans le niveau 0 : ");
    scanf("%lu", &val);

    int resultat = searchLevel0(list, val);

    if (resultat != 0) {
        printf("La valeur %lu a été trouvée dans le niveau.\n", val);
    } else {
        printf("La valeur %lu n'a pas été trouvée dans le niveau.\n", val);
    }


    searchHLevels(list, 67, 3);





    destroy_list(&list);


    return 0;
}
