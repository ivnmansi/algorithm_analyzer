/**
 * @file errors.h
 * @brief Codigos y utilidades de manejo de errores de la aplicacion.
 */

#ifndef ERRORS_H
#define ERRORS_H

/**
 * @brief Codigos de error disponibles en la aplicacion.
 */
typedef enum {
    ERROR_INVALID_DATA_AMOUNT = 1,
    ERROR_INVALID_RANKING_AMOUNT = 2,
    ERROR_NO_DATA_LOADED = 3,
    ERROR_FILE_CREATE_FAILED = 4,
    ERROR_MEMORY_ALLOCATION_FAILED = 5,
    ERROR_BENCHMARK_DATA_LOAD_FAILED = 6,
    ERROR_UNKNOWN_OPTION = 7,
    ERROR_NOT_IMPLEMENTED = 8,
    ERROR_DEPORTISTA_NOT_FOUND = 9
} ErrorCode;

/**
 * @brief Imprime un error centralizado a partir de un codigo documentado.
 *
 * @param errorCode Codigo del error a imprimir.
 * @param detail Texto adicional opcional para complementar el mensaje.
 */
void print_error(ErrorCode errorCode, const char *detail);

#endif
