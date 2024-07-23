#ifndef HRS_ERROR_H
#define HRS_ERROR_H

#include "../types.h"

typedef struct HRSError {
    string_t cause;
    string_t description;
    int id;
} HRSError;

void hrserr_print(HRSError *_error);

void hrserr_printAndStopProgram(HRSError *_error);

#endif