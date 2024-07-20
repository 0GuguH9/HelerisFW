#ifndef HRS_ERROR_PRESETS_H
#define HRS_ERROR_PRESETS_H

#include "../types.h"
#include "error.h"

#define QUICK_DESCRIPTION(format, value) char description[256]; \
    snprintf(description, sizeof(description), format, value) \

#define QUICK_PRINT_AND_STOP(cause, id) HRSError error = {cause, description, id}; \
    hrserr_printAndStopProgram(&error) \

void errpre_malloc(string_t objectType);

void errpre_realloc(string_t objectType);

void errpre_nullptr(string_t nullType);

void errpre_initialize(string_t objectType);

void errpre_invalidArgument(string_t argument);

void errpre_invalidState(string_t state);

void errpre_load(string_t resourceType);

void errpre_incompatibility(string_t feature, string_t requirement);

#endif