#include "print_format.h"

void print_error(const char* message) {
    fprintf(stderr, RED BOLD "\n[ERROR]" RESET RED " %s\n\n" RESET, message);
}