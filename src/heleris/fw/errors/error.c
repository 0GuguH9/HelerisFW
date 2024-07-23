#include "heleris/fw/errors/error.h"

#include <stdlib.h>

void hrserr_print(HRSError *_error) {

    fprintf(stderr, "\n[Error] ->\n");
    fprintf(stderr, "Error cause: %s;\n", _error->cause);
    fprintf(stderr, "Error description: %s;\n", _error->description);
    fprintf(stderr, "Error id: %d.\n", _error->id);
}

void hrserr_printAndStopProgram(HRSError *_error) {

    fprintf(stderr, "\n[Error] caused program interruption ->\n");
    fprintf(stderr, "Error cause: %s;\n", _error->cause);
    fprintf(stderr, "Error description: %s;\n", _error->description);
    fprintf(stderr, "Error id: %d.\n", _error->id);
    exit(_error->id);
}

