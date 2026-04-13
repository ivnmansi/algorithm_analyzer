/**
 * @file main.c
 * @brief
 *
 */

#include "base.h"

int main(int argc, char **argv)
{
    static struct option longOptions[] = {
        {"id", required_argument, 0, 'i'},
        {0, 0, 0, 0}
    };

    srand(time(0));

    if(argc == 1){
        print_help(argv[0]);
        return 0;
    }

    if(argc >= 3 && strcmp(argv[1], "-id") == 0){
        search_by_id(atoi(argv[2]));
        return 0;
    }

    int opt;
    while((opt = getopt_long(argc, argv, "hg:tr:bs", longOptions, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_help(argv[0]);
                return 0;
            case 'g': // Aca poner -g *cantidad de datos a generar*
            {
                int cantidadDatos = atoi(optarg);
                if (MIN_DATA > cantidadDatos  || cantidadDatos > MAX_DATA)
                {
                    printf("Cantidad de datos debe estar entre 10 y 100000\n");
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
            case 'i':
            {
                search_by_id(atoi(optarg));
                break;
            }
            case 'r':
            {
                int rankingAmount = atoi(optarg);
                if(rankingAmount <= 0){
                    printf("La cantidad del ranking debe ser mayor que 0\n");
                    return 1;
                }
                show_ranking(rankingAmount);
                break;
            }
            case 'b':
            {
                run_search_benchmark();
                break;
            }
            case 's':
            {   
                run_sort_benchmark();
                break;
            }
            case '?':
            {
                char detail[2];
                detail[0] = (char)optopt;
                detail[1] = '\0';
                printf("Opcion desconocida: -%s\n", detail);
                return 1;
            }
        }
    }

    return 0;
}
