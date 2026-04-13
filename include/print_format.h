#ifndef PRINT_FORMAT_H
#define PRINT_FORMAT_H

#include "deportista.h"

#define BOLD "\033[1m"
#define DIM "\033[2m"
#define UNDERLINE "\033[4m"
#define NORMAL "\033[0m"
#define RESET "\033[0m"

// Reset parcial: vuelve a los colores por defecto sin tocar otras propiedades
#define FG_DEFAULT "\033[39m"
#define BG_DEFAULT "\033[49m"
#define NO_BG "\033[49m"

// Control de terminal
#define CLEAR_LINE "\033[2K"      // limpia línea actual
#define CURSOR_HOME "\r"          // vuelve al inicio de la línea
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

// ASCII helpers
#define ASCII_HR "-------------------------------------------------------------------"
#define ASCII_HR_WIDE "---------------------------------------------------------------------------------------------------------------"
#define ASCII_OK "[OK]"
#define ASCII_FAIL "[FAIL]"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Bright (high-intensity) foreground colors
#define BRIGHT_BLACK "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

// Background colors
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// 256-color
#define ORANGE "\033[38;5;208m"
#define PINK "\033[38;5;205m"
#define PURPLE "\033[38;5;141m"
#define TEAL "\033[38;5;37m"
#define GRAY "\033[38;5;245m"

// Combinados comunes
#define BOLD_GREEN "\033[1m\033[32m"
#define BOLD_RED "\033[1m\033[31m"
#define BOLD_YELLOW "\033[1m\033[33m"
#define BOLD_BLUE "\033[1m\033[34m"

void printDeportistasArray(Deportista *deportistas, int rankingAmount);

void print_error(const char* message);


#endif