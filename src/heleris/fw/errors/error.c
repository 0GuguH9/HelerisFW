#include "headers/error.h"

#include <stdlib.h>

void hrserr_print(HRSError *error) {

    fprintf(stderr, "\n[Error] ->\n");
    fprintf(stderr, "Error cause: %s;\n", error.cause);
    fprintf(stderr, "Error description: %s;\n", error.description);
    fprintf(stderr, "Error id: %d.\n", error.id);
}

void hrserr_printAndStopProgram(HRSError *error) {

    fprintf(stderr, "\n[Error] caused program interruption ->\n");
    fprintf(stderr, "Error cause: %s;\n", error.cause);
    fprintf(stderr, "Error description: %s;\n", error.description);
    fprintf(stderr, "Error id: %d.\n", error.id);
    exit(error->id);
}
