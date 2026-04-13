/**
 * @file benchmarks.c
 * @brief Implementacion de benchmarks de busqueda y ordenamiento.
 */

#include "base.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Limpia la linea actual en la consola.
 */
static void progress_clear_line(void)
{
    printf(CURSOR_HOME CLEAR_LINE);
    fflush(stdout);
}

/**
 * @brief Actualiza la barra de progreso de un benchmark.
 *
 * @param benchmarkName Nombre del benchmark (ej: "search" o "sort")
 * @param intervalIndex Indice del intervalo actual
 * @param intervalCount Cantidad de intervalos
 * @param n Tamano de los datos
 * @param repeatIndex Indice de la repeticion actual
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
 * @brief Duplica una cadena para los benchmarks.
 *
 * @param srcString String a duplicar.
 * @return char* Cadena duplicada o NULL si hubo un error.
 */
static char *duplicate_string_bench(const char *srcString)
{
    size_t len;
    char *copy;

    if(srcString == NULL) {
        return NULL;
    }

    len = strlen(srcString);
    copy = malloc(len + 1);
    if(copy == NULL) {
        return NULL;
    }

    memcpy(copy, srcString, len + 1);
    return copy;
}

/**
 * @brief Maneja un error de memoria durante la ejecucion de benchmarks.
 *
 * @param baseArray Arreglo base cargado desde el CSV.
 * @param count Cantidad de deportistas del arreglo base.
 * @param out Archivo de salida del benchmark.
 */
static void handle_benchmark_memory_error(Deportista *baseArray, int count, FILE *out)
{
    progress_clear_line();
    printf(SHOW_CURSOR);

    if(out != NULL) {
        fclose(out);
    }

    free_deportistas_array(baseArray, count);
    print_error(ERROR_MEMORY_ALLOCATION_FAILED, "durante el benchmark");
    exit(EXIT_FAILURE);
}

/**
 * @brief Clona un arreglo de deportistas para ejecutar benchmarks.
 *
 * @param srcArray Arreglo a clonar.
 * @param count Cantidad de elementos a clonar
 * @return Deportista* Arreglo de deportistas clonados o NULL si hubo un error.
 */
static Deportista *clone_deportistas_array(Deportista *srcArray, int count)
{
    Deportista *deportistas;

    if(srcArray == NULL || count < 0) {
        return NULL;
    }

    deportistas = malloc(sizeof(Deportista) * count);
    if(deportistas == NULL) {
        return NULL;
    }

    for(int i = 0; i < count; i++) {
        char *nombre;
        char *equipo;

        if(srcArray[i] == NULL) {
            deportistas[i] = NULL;
            continue;
        }

        nombre = duplicate_string_bench(srcArray[i]->nombre);
        equipo = duplicate_string_bench(srcArray[i]->equipo);

        if(nombre == NULL || equipo == NULL) {
            free(nombre);
            free(equipo);

            for(int j = 0; j < i; j++) {
                if(deportistas[j] != NULL) {
                    delete_deportista(deportistas[j]);
                }
            }

            free(deportistas);
            return NULL;
        }

        deportistas[i] = create_deportista(
            srcArray[i]->id,
            nombre,
            equipo,
            srcArray[i]->puntaje,
            srcArray[i]->competencias
        );

        if(deportistas[i] == NULL) {
            free(nombre);
            free(equipo);

            for(int j = 0; j < i; j++) {
                if(deportistas[j] != NULL) {
                    delete_deportista(deportistas[j]);
                }
            }

            free(deportistas);
            return NULL;
        }
    }

    return deportistas;
}

/**
 * @brief Ejecuta el benchmark de busqueda y guarda sus resultados en CSV.
 */
void run_search_benchmark()
{
    int count = 0;
    Deportista *baseArray = load_deportistas_array(&count);

    if(baseArray == NULL || count <= 0) {
        if(baseArray != NULL) {
            free_deportistas_array(baseArray, count);
        }

        print_error(ERROR_BENCHMARK_DATA_LOAD_FAILED, NULL);
        return;
    }

    int intervals = (count < INTERVAL_SIZE) ? count : INTERVAL_SIZE;
    int stepSize = count / intervals;

    if(stepSize <= 0) {
        stepSize = 1;
    }

    FILE *out = fopen(SEARCH_BENCHMARK_ROUTE, "w");

    if(out == NULL) {
        print_error(ERROR_FILE_CREATE_FAILED, SEARCH_BENCHMARK_ROUTE);
        free_deportistas_array(baseArray, count);
        return;
    }

    fprintf(out, "n,promedio_secuencial_s,promedio_binaria_s\n");

    printf(BOLD_BLUE "\n=== Search benchmark ===\n" RESET);
    printf(DIM "Archivo: %s | intervalos: %d | repeticiones: %d\n\n" RESET, SEARCH_BENCHMARK_ROUTE, intervals, EXPERIMENT_REPEATS);

    printf("n \t | \t secuencial(s) \t | \t binaria(s)\n");
    printf(ASCII_HR "\n");

    printf(HIDE_CURSOR);

    for(int i = 0; i < intervals; i++) {
        int n = (i == intervals - 1) ? count : (stepSize * (i + 1));
        double totalSeq = 0.0;
        double totalBin = 0.0;

        for(int j = 0; j < EXPERIMENT_REPEATS; j++) {
            int targetId;
            clock_t start;
            clock_t end;
            Deportista *work;

            progress_update_line("search", i + 1, intervals, n, j + 1, EXPERIMENT_REPEATS, "clonando");

            work = clone_deportistas_array(baseArray, n);
            if(work == NULL) {
                handle_benchmark_memory_error(baseArray, count, out);
            }

            targetId = work[n - 1]->id;

            progress_update_line("search", i + 1, intervals, n, j + 1, EXPERIMENT_REPEATS, "secuencial");
            start = clock();
            sequential_search_by_id(work, n, targetId);
            end = clock();
            totalSeq += (double)(end - start) / CLOCKS_PER_SEC;

            insertion_sort_deportistas(work, n, SORT_BY_ID, ASCENDING);

            progress_update_line("search", i + 1, intervals, n, j + 1, EXPERIMENT_REPEATS, "binaria");

            start = clock();
            binary_search_by_id(work, n, targetId);
            end = clock();
            totalBin += (double)(end - start) / CLOCKS_PER_SEC;

            free_deportistas_array(work, n);
        }

        double avgSeq = totalSeq / EXPERIMENT_REPEATS;
        double avgBin = totalBin / EXPERIMENT_REPEATS;

        fprintf(out, "%d,%.10f,%.10f\n", n, avgSeq, avgBin);
        progress_clear_line();
        printf("%d \t | \t %.10f \t | \t %.10f\n", n, avgSeq, avgBin);
    }

    progress_clear_line();
    printf(SHOW_CURSOR);

    fclose(out);
    free_deportistas_array(baseArray, count);
    printf(BG_GREEN "\nBenchmark guardado correctamente en %s\n" RESET, SEARCH_BENCHMARK_ROUTE);
}

/**
 * @brief Ejecuta el benchmark de ordenamiento y guarda sus resultados en CSV.
 */
void run_sort_benchmark()
{
    int count = 0;
    Deportista *baseArray = load_deportistas_array(&count);

    if(baseArray == NULL || count <= 0) {
        if(baseArray != NULL) {
            free_deportistas_array(baseArray, count);
        }

        print_error(ERROR_BENCHMARK_DATA_LOAD_FAILED, NULL);
        return;
    }

    int intervals = (count < INTERVAL_SIZE) ? count : INTERVAL_SIZE;
    int stepSize = count / intervals;

    if(stepSize <= 0) {
        stepSize = 1;
    }

    FILE *out = fopen(SORT_BENCHMARK_ROUTE, "w");

    if(out == NULL) {
        print_error(ERROR_FILE_CREATE_FAILED, SORT_BENCHMARK_ROUTE);
        free_deportistas_array(baseArray, count);
        return;
    }

    fprintf(out, "n,promedio_insertion_s,promedio_bubble_s,promedio_selection_s,promedio_cocktail_s\n");

    printf(BOLD_BLUE "\n=== Sort benchmark ===\n" RESET);
    printf(DIM "Archivo: %s | intervalos: %d | repeticiones: %d\n\n" RESET, SORT_BENCHMARK_ROUTE, intervals, EXPERIMENT_REPEATS);

    printf("n \t | \t insertion(s) \t | \t bubble(s) \t | \t selection(s) \t | \t cocktail(s)\n");
    printf(ASCII_HR_WIDE "\n");

    printf(HIDE_CURSOR);

    for(int i = 0; i < intervals; i++) {
        int n = (i == intervals - 1) ? count : (stepSize * (i + 1));

        double totalInsertion = 0.0;
        double totalBubble = 0.0;
        double totalSelection = 0.0;
        double totalCocktail = 0.0;

        for(int r = 0; r < EXPERIMENT_REPEATS; r++) {
            Deportista *work;
            clock_t start;
            clock_t end;

            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "insertion");
            work = clone_deportistas_array(baseArray, n);

            if(work == NULL) {
                handle_benchmark_memory_error(baseArray, count, out);
            }

            start = clock();
            insertion_sort_deportistas(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalInsertion += (double)(end - start) / CLOCKS_PER_SEC;
            free_deportistas_array(work, n);

            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "bubble");
            work = clone_deportistas_array(baseArray, n);

            if(work == NULL) {
                handle_benchmark_memory_error(baseArray, count, out);
            }

            start = clock();
            optimized_bubble_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalBubble += (double)(end - start) / CLOCKS_PER_SEC;
            free_deportistas_array(work, n);

            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "selection");
            work = clone_deportistas_array(baseArray, n);

            if(work == NULL) {
                handle_benchmark_memory_error(baseArray, count, out);
            }

            start = clock();
            selection_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalSelection += (double)(end - start) / CLOCKS_PER_SEC;
            free_deportistas_array(work, n);

            progress_update_line("sort", i + 1, intervals, n, r + 1, EXPERIMENT_REPEATS, "cocktail");
            work = clone_deportistas_array(baseArray, n);

            if(work == NULL) {
                handle_benchmark_memory_error(baseArray, count, out);
            }

            start = clock();
            cocktail_shaker_sort(work, n, SORT_BY_ID, ASCENDING);
            end = clock();
            totalCocktail += (double)(end - start) / CLOCKS_PER_SEC;
            free_deportistas_array(work, n);
        }

        totalInsertion /= EXPERIMENT_REPEATS;
        totalBubble /= EXPERIMENT_REPEATS;
        totalSelection /= EXPERIMENT_REPEATS;
        totalCocktail /= EXPERIMENT_REPEATS;

        fprintf(
            out,
            "%d,%.10f,%.10f,%.10f,%.10f\n",
            n,
            totalInsertion,
            totalBubble,
            totalSelection,
            totalCocktail
        );

        progress_clear_line();
        printf(
            "%d \t | \t %.10f \t | \t %.10f \t | \t %.10f \t | \t %.10f\n",
            n,
            totalInsertion,
            totalBubble,
            totalSelection,
            totalCocktail
        );
    }

    progress_clear_line();
    printf(SHOW_CURSOR);

    fclose(out);
    free_deportistas_array(baseArray, count);
    printf(BG_GREEN "\nBenchmark de ordenamiento guardado con exito en %s\n" RESET, SORT_BENCHMARK_ROUTE);
}
