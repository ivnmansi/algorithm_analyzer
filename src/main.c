/**
 * @file main.c
 * @brief 
 * 
 */

#include "base.h"

int main(int argc, char **argv) {

    srand(time(0));

    int opt;
    while((opt = getopt(argc, argv, "hg:")) != -1) {
        switch (opt) {
            case 'h':
                printf("imprimir ayuda");
                return 0;
            case 'g':
                printf("generar %d datos", atoi(optarg));
                break;
            case '?':
                printf("Opción desconocida: -%c\n", optopt);
                return 1;
        }
    }

    return 0;
}
