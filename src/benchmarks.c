/**
 * @file benchmarks.c
 * @brief 
 * 
 */

#include "base.h"
#include "csv.h"
#include "sorting.h"
#include "print_format.h"
#include <stdio.h>

/**
 * @brief Funcion que registra el tiempo de ejecucion de los algoritmos de busqueda secuencial y binaria para diferentes tamaños de datos, guardando los resultados en un archivo CSV y mostrando un resumen por consola
 */
void run_search_benchmark()
{
    const int sizes[] = {10, 100, 1000, 10000};
    const int num_sizes = (int)(sizeof(sizes) / sizeof(sizes[0]));
    const int repeats = 20; // cantidad de veces que se repite cada prueba para promediar resultados

    FILE *out = fopen(SEARCH_BENCHMARK_ROUTE, "w");
    if(out == NULL){
        printf("No se pudo crear archivo\n");
        return;
    }

    fprintf(out, "n,repeticiones,promedio_secuencial_s,promedio_binaria_s\n");
    printf("n | repeticiones | secuencial(s) | binaria(s)\n");
    printf("-------------------------------------------------\n");

    for(int i = 0; i < num_sizes; i++){
        int n = sizes[i];
        double total_seq = 0;
        double total_bin = 0;
        int validRuns = 0;

        for(int j = 0; j < repeats; j++){
            int count = 0;
            Deportista *deportistas;
            int targetId;
            clock_t start, end;

            createDeportistasCSV(n);
            deportistas = loadDeportistasArray(&count);
            if(deportistas == NULL || count <= 0){
                if(deportistas != NULL){
                    freeDeportistasArray(deportistas, count);
                }
                continue;
            }

            // Se toma el ID del ultimo elemento arbitrariamente (asi se asegura que existe)
            targetId = deportistas[count - 1]->ID;

            start = clock();
            sequential_search_by_id(deportistas, count, targetId);
            end = clock();
            total_seq += (double)(end - start) / CLOCKS_PER_SEC;

            // Insertion sort necesita tener el arreglo ordenado
            insertion_sort_deportistas(deportistas, count, SORT_BY_ID, ASCENDING);

            start = clock();
            binary_search_by_id(deportistas, count, targetId);
            end = clock();
            total_bin += (double)(end - start) / CLOCKS_PER_SEC;

            validRuns++;
            freeDeportistasArray(deportistas, count);
        }

        if(validRuns == 0){ //Si no se pudo ejecutar ninguna prueba, se escribe 0 en los tiempos para ese tamaño
            fprintf(out, "%d,%d,0,0\n", n, repeats);
            printf("%d | %d | 0 | 0\n", n, repeats);
            continue;
        }


        double avgSeq = total_seq / validRuns;
        double avgBin = total_bin / validRuns;

        fprintf(out, "%d,%d,%.10f,%.10f\n", n, validRuns, avgSeq, avgBin);
        printf("%d | %d | %.10f | %.10f\n", n, validRuns, avgSeq, avgBin);

    }

    fclose(out);
    printf("\nBenchmark guardado correctamente\n");
}


/**
 * @brief Funcion que duplica una cadena de caracteres, utilizada para clonar los datos de deportistas en los benchmarks.
 * @param srcString String a duplicar.
 * @return char* Cadena duplicada o NULL si hubo un error.
 */
static char *duplicate_string_bench(const char *srcString)
{
    size_t len;
    char *copy;

    if(srcString == NULL){
        return NULL;
    }

    len = strlen(srcString);
    copy = malloc(len + 1);
    if(copy == NULL){
        return NULL;
    }

    memcpy(copy, srcString, len + 1);
    return copy;
}

/**
 * @brief Funcion que clona un arreglo de deportistas, creando nuevas instancias de cada deportista con los mismos datos. Utilizada para los benchmarks de ordenamiento para evitar modificar el mismo arreglo base.
 * @param srcArray Arreglo a clonar.
 * @param count Cantidad de elementos a clonar
 * @return Deportista* Arreglo de deportistas clonados o NULL si hubo un error.
 */
static Deportista *clone_deportistas_array(Deportista *srcArray, int count)
{
    Deportista *deportistas;

    if(srcArray == NULL || count < 0){
        return NULL;
    }

    deportistas = malloc(sizeof(Deportista) * count);
    if(deportistas == NULL){
        return NULL;
    }

    for(int i = 0; i < count; i++){
        char *nombre;
        char *equipo;

        if(srcArray[i] == NULL){
            deportistas[i] = NULL;
            continue;
        }

        nombre = duplicate_string_bench(srcArray[i]->Nombre);
        equipo = duplicate_string_bench(srcArray[i]->Equipo);

        if(nombre == NULL || equipo == NULL){
            free(nombre);
            free(equipo);
            for(int j = 0; j < i; j++){
                if(deportistas[j] != NULL){
                    deleteDeportista(deportistas[j]);
                }
            }
            free(deportistas);
            return NULL;
        }

        deportistas[i] = createDeportista(
            srcArray[i]->ID,
            nombre,
            equipo,
            srcArray[i]->Puntaje,
            srcArray[i]->Competencias
        );

        if(deportistas[i] == NULL){
            free(nombre);
            free(equipo);
            for(int j = 0; j < i; j++){
                if(deportistas[j] != NULL){
                    deleteDeportista(deportistas[j]);
                }
            }
            free(deportistas);
            return NULL;
        }
    }

    return deportistas;
}

/**
 * @brief Funcion encargada de ejecutar una operacion de ordenamiento o ranking, preguntando al usuario por el criterio, orden y algoritmo a utilizar, y mostrando los resultados por consola.
 */
void run_sort_benchmark()
{   
    // carga inicial de deportistas
    int count = 0; // Almacena cantidad de deportistas cargados
    Deportista* baseArray = loadDeportistasArray(&count);
    if(baseArray == NULL || count <= 0){
        if(baseArray != NULL){
            freeDeportistasArray(baseArray, count);
        }
        printf("No se pudieron cargar deportistas para el benchmark\n");
        return;
    }

    

    // calculo de tamaños segun cantidad de deportistas cargados
    int intervals = (count < INTERVAL_SIZE) ? count : INTERVAL_SIZE;
    int step_size = count / intervals;
    if (step_size <= 0){
        step_size = 1;
    }

    // generar archivo CSV para guardar resultados
    FILE *out = fopen(SORT_BENCHMARK_ROUTE, "w");
    if(out == NULL){
        printf("No se pudo crear archivo\n");
        freeDeportistasArray(baseArray, count);
        return;
    }
    fprintf(out, "n,promedio_insertion_s,promedio_bubble_s,promedio_selection_s,promedio_cocktail_s\n");
    printf("n \t | \t insertion(s) \t | \t bubble(s) \t | \t selection(s) \t | \t cocktail(s)\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    // inicio de benchmark
    for(int i = 0; i < intervals; i++){
        int n = (i == intervals - 1) ? count : (step_size * (i + 1));
        double totalIns = 0.0;
        double totalBub = 0.0;
        double totalSel = 0.0;
        double totalCoc = 0.0;

        for(int r = 0; r < EXPERIMENT_REPEATS; r++){
            Deportista* work;
            clock_t start, end;

            // insertion sort
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                printf("No se pudieron clonar deportistas para el benchmark\n");
                freeDeportistasArray(baseArray, count);
                fclose(out);
                return;
            }
            start = clock();
            insertion_sort_deportistas(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalIns += (double)(end - start) / CLOCKS_PER_SEC;
            freeDeportistasArray(work, n);

            // bubble sort optimizado
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                printf("No se pudieron clonar deportistas para el benchmark\n");
                freeDeportistasArray(baseArray, count);
                fclose(out);
                return;
            }
            start = clock();
            optimized_bubble_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalBub += (double)(end - start) / CLOCKS_PER_SEC;
            freeDeportistasArray(work, n);

            // selection sort
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                printf("No se pudieron clonar deportistas para el benchmark\n");
                freeDeportistasArray(baseArray, count);
                fclose(out);
                return;
            }
            start = clock();
            selection_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalSel += (double)(end - start) / CLOCKS_PER_SEC;
            freeDeportistasArray(work, n);
            
            // cocktail shaker sort
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                printf("No se pudieron clonar deportistas para el benchmark\n");
                freeDeportistasArray(baseArray, count);
                fclose(out);
                return;
            }
            start = clock();
            cocktail_shaker_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalCoc += (double)(end - start) / CLOCKS_PER_SEC;
            freeDeportistasArray(work, n);
        }

        totalIns /= EXPERIMENT_REPEATS;
        totalBub /= EXPERIMENT_REPEATS;
        totalSel /= EXPERIMENT_REPEATS;
        totalCoc /= EXPERIMENT_REPEATS;

        fprintf(
            out,
            "%d,%.10f,%.10f,%.10f,%.10f\n",
            n,
            totalIns,
            totalBub,
            totalSel,
            totalCoc
        );

        printf(
            "%d \t | \t %.10f \t | \t %.10f \t | \t %.10f \t | \t %.10f\n",
            n,
            totalIns,
            totalBub,
            totalSel,
            totalCoc
        );
    }

    fclose(out);
    freeDeportistasArray(baseArray, count);
    printf(BG_GREEN"\nBenchmark de ordenamiento guardado con exito en %s"RESET"\n", SORT_BENCHMARK_ROUTE);
}

