/**
 * @file benchmarks.c
 * @brief 
 * 
 */

#include "base.h"
#include "csv.h"
#include "deportista.h"
#include "sorting.h"
#include "print_format.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Limpia la línea actual en la consola y mueve el cursor al inicio de la línea. Utilizada para actualizar la barra de progreso durante los benchmarks sin imprimir nuevas líneas.
 * 
 */
static void progress_clear_line(void)
{
    printf(CURSOR_HOME CLEAR_LINE);
    fflush(stdout);
}

/**
 * @brief Actualiza barra de progreso por consola, mostrando el nombre del benchmark, el intervalo actual, el tamaño de datos, la repetición actual y la etapa del proceso. Utilizada para mostrar el progreso durante los benchmarks de búsqueda y ordenamiento.
 * 
 * @param benchmarkName Nombre del benchmark (ej: "search" o "sort")
 * @param intervalIndex Índice del intervalo actual
 * @param intervalCount Cantidad de intervalos
 * @param n Tamaño de los datos
 * @param repeatIndex Índice de la repetición actual
 * @param repeatCount Cantidad de repeticiones
 * @param stage Etapa del proceso
 */
static void progress_update_line(const char *benchmarkName, int intervalIndex, int intervalCount, int n, int repeatIndex, int repeatCount, const char *stage)
{
    printf(
        CURSOR_HOME CLEAR_LINE DIM"%s | %d/%d | n=%d | rep %d/%d | %s" RESET,
        benchmarkName,
        intervalIndex,
        intervalCount,
        n,
        repeatIndex,
        repeatCount,
        stage
    );
    fflush(stdout);
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

static void memoryError(Deportista* baseArray, int count, FILE* out){
    progress_clear_line();
    printf(SHOW_CURSOR);
    print_error("No se pudieron cargar deportistas para el benchmark");
    freeDeportistasArray(baseArray, count);
    fclose(out);
    exit(1);
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
 * @brief Funcion que registra el tiempo de ejecucion de los algoritmos de busqueda secuencial y binaria para diferentes tamaños de datos, guardando los resultados en un archivo CSV y mostrando un resumen por consola
 */
void run_search_benchmark()
{
    // carga inicial de deportistas
    int count = 0; // Almacena cantidad de deportistas cargados
    Deportista* baseArray = loadDeportistasArray(&count);
    if(baseArray == NULL || count <= 0){
        if(baseArray != NULL){
            freeDeportistasArray(baseArray, count);
        }
        print_error("No se pudieron cargar deportistas para el benchmark");
        return;
    }

    // calculo de tamaños segun cantidad de deportistas cargados
    int intervals = (count < INTERVAL_SIZE) ? count : INTERVAL_SIZE;
    int step_size = count / intervals;
    if (step_size <= 0){
        step_size = 1;
    }

    // crear archivo CSV para guardar resultados
    FILE *out = fopen(SEARCH_BENCHMARK_ROUTE, "w");
    if(out == NULL){
        printf("No se pudo crear archivo\n");
        freeDeportistasArray(baseArray, count);
        return;
    }

    fprintf(out, "n,promedio_secuencial_s,promedio_binaria_s\n");

    printf(BOLD_BLUE "\n=== Search benchmark ===\n" RESET);
    printf(DIM "Archivo: %s | intervalos: %d | repeticiones: %d\n\n" RESET, SEARCH_BENCHMARK_ROUTE, intervals, EXPERIMENT_REPEATS);

    printf("n \t | \t secuencial(s) \t | \t binaria(s)\n");
    printf(ASCII_HR "\n");

    printf(HIDE_CURSOR);

    // inicio de experimento
    for(int i = 0; i < intervals; i++){
        int n = (i == intervals - 1) ? count : (step_size * (i + 1));
        double total_seq = 0;
        double total_bin = 0;

        for(int j = 0; j < EXPERIMENT_REPEATS; j++){
            int targetId;
            clock_t start, end;

            progress_update_line("search", i + 1, intervals, n, j + 1, EXPERIMENT_REPEATS, "clonando");

            Deportista* work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                memoryError(baseArray, count, out);
            }

            // Se toma el ID del ultimo elemento arbitrariamente (asi se asegura que existe)
            targetId = work[n - 1]->ID;

            progress_update_line("search", i + 1, intervals, n, j + 1, EXPERIMENT_REPEATS, "secuencial");
            start = clock();
            sequential_search_by_id(work, n, targetId);
            end = clock();
            total_seq += (double)(end - start) / CLOCKS_PER_SEC;

            // binary search necesita que el arreglo esté ordenado
            insertion_sort_deportistas(work, n, SORT_BY_ID, ASCENDING);

            progress_update_line("search", i + 1, intervals, n, j + 1, EXPERIMENT_REPEATS, "binaria");

            start = clock();
            binary_search_by_id(work, n, targetId);
            end = clock();
            total_bin += (double)(end - start) / CLOCKS_PER_SEC;

            freeDeportistasArray(work, n);
        }

        double avgSeq = total_seq / EXPERIMENT_REPEATS;
        double avgBin = total_bin / EXPERIMENT_REPEATS;

        fprintf(out, "%d,%.10f,%.10f\n", n, avgSeq, avgBin);
        progress_clear_line();
        printf("%d \t | \t %.10f \t | \t %.10f\n", n, avgSeq, avgBin);

    }

    progress_clear_line();
    printf(SHOW_CURSOR);

    fclose(out);
    freeDeportistasArray(baseArray, count);
    printf(BG_GREEN"\nBenchmark guardado correctamente en %s\n"RESET, SEARCH_BENCHMARK_ROUTE);
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
         print_error("No se pudieron cargar deportistas para el benchmark");
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

    printf(BOLD_BLUE "\n=== Sort benchmark ===\n" RESET);
    printf(DIM "Archivo: %s | intervalos: %d | repeticiones: %d\n\n" RESET, SORT_BENCHMARK_ROUTE, intervals, EXPERIMENT_REPEATS);

    printf("n \t | \t insertion(s) \t | \t bubble(s) \t | \t selection(s) \t | \t cocktail(s)\n");
    printf(ASCII_HR_WIDE "\n");

    printf(HIDE_CURSOR);

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
            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "insertion");
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                memoryError(baseArray, count, out);
            }
            start = clock();
            insertion_sort_deportistas(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalIns += (double)(end - start) / CLOCKS_PER_SEC;
            freeDeportistasArray(work, n);

            // bubble sort optimizado
            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "bubble");
            
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                memoryError(baseArray, count, out);
            }
            start = clock();
            optimized_bubble_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalBub += (double)(end - start) / CLOCKS_PER_SEC;
            freeDeportistasArray(work, n);

            // selection sort
            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "selection");
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                memoryError(baseArray, count, out);
            }
            start = clock();
            selection_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalSel += (double)(end - start) / CLOCKS_PER_SEC;
            freeDeportistasArray(work, n);
            
            // cocktail shaker sort
            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "cocktail");
            work = clone_deportistas_array(baseArray, n);
            if(work == NULL){
                memoryError(baseArray, count, out);
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

        progress_clear_line();
        printf(
            "%d \t | \t %.10f \t | \t %.10f \t | \t %.10f \t | \t %.10f\n",
            n,
            totalIns,
            totalBub,
            totalSel,
            totalCoc
        );
    }

    progress_clear_line();
    printf(SHOW_CURSOR);

    fclose(out);
    freeDeportistasArray(baseArray, count);
    printf(BG_GREEN"\nBenchmark de ordenamiento guardado con exito en %s"RESET"\n", SORT_BENCHMARK_ROUTE);
}

