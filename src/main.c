/**
 * @file main.c
 * @brief
 *
 */

#include "base.h"
#include "linked_list.h"
#include "csv.h"

int main(int argc, char **argv) {

    srand(time(0));

    int opt;
    while((opt = getopt(argc, argv, "hg:t:")) != -1) {
        switch (opt) {
            case 'h':
                printf("imprimir ayuda");
                return 0;
            case 'g': // Aca poner -g *cantidad de datos a generar*
            {
                int cantidadDatos = atoi(optarg);
                if (MIN_DATA > cantidadDatos  || cantidadDatos > MAX_DATA)
                {
                    printf("Cantidad de datos debe estar entre %d y %d\n", MIN_DATA, MAX_DATA);
                    return 1;
                }
                printf("Cantidad de datos a generar: %d\n", atoi(optarg));
                createDeportistasCSV(cantidadDatos);
                break;
            }
            case 't':
            {
                runExperiment();
                break;
            }
            case '?':
                printf("Opción desconocida: -%c\n", optopt);
                return 1;
        }
    }

    return 0;
}
