#include "heleris/fw/errors/error_presets.h"

#include "heleris/fw/errors/error_codes.h"

#include <stdio.h>

void errpre_nullptr(string_t nullType) {

    QUICK_DESCRIPTION("There was an attempt to use a nullptr of type \"%s\" in a certain function or context where a concrete type was needed", nullType);
    
    QUICK_PRINT_AND_STOP("Attempting to use a nullptr", HRS_ERROR_TRY_TO_USE_NULL);
}

void errpre_malloc(string_t objectType) {

    QUICK_DESCRIPTION("Memory allocation failed for object of type \"%s\"", objectType);
    
    QUICK_PRINT_AND_STOP("Memory allocation failed", HRS_ERROR_MALLOC_ERROR);
}

void errpre_realloc(string_t objectType) {

    QUICK_DESCRIPTION("Memory reallocation failed for object of type \"%s\"", objectType);
    
    QUICK_PRINT_AND_STOP("Memory reallocation failed", HRS_ERROR_REALLOC_ERROR);
}

void errpre_initialize(string_t objectType) {

    QUICK_DESCRIPTION("Initialization failed for object of type \"%s\"", objectType);

    QUICK_PRINT_AND_STOP("Initialization failed", HRS_ERROR_FAILED_INITIALIZE);
}

void errpre_invalidArgument(string_t argument) {

    QUICK_DESCRIPTION("Invalid argument: \"%s\"", argument);

    QUICK_PRINT_AND_STOP("Invalid argument", HRS_ERROR_INCOMPATIBLE_STATUS);
}

void errpre_invalidState(string_t state) {

    QUICK_DESCRIPTION("Invalid state: \"%s\"", state);

    QUICK_PRINT_AND_STOP("Invalid state", HRS_ERROR_INCOMPATIBLE_STATUS);
}

void errpre_load(string_t resourceType) {
    
    QUICK_DESCRIPTION("Failed to load resource of type \"%s\"", resourceType);

    QUICK_PRINT_AND_STOP("Resource load failed", HRS_ERROR_HRSCLD_LOAD_FAILED);
}

void errpre_incompatibility(string_t feature, string_t requirement) {

    char description[256];
    snprintf(description, sizeof(description), "incompatibility detected. Feature: \"%s\" requires: \"%s\"", feature, requirement);

    QUICK_PRINT_AND_STOP("Incompatibility detected", HRS_ERROR_INCOMPATIBILITY);
}
