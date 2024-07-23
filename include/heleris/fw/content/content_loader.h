#ifndef HELERIS_FW_CONTENT_LOADER_H
#define HELERIS_FW_CONTENT_LOADER_H

#include "../types.h"
#include "texture.h"

#ifdef __linux
    #define PATH_SEPARATOR "/"
#elif  defined(__WIN32)
    #define PATH_SEPARATOR "\\"
#endif

extern const int HRS_MIN_TEXTURE_UNIT_LIMIT;
extern const int HRS_MIN_TEXTURE_BOUND_LIMIT;

typedef struct HRSContentLoader {
    string_t path;
    int maxTextureUnits;
    int maxTextureBound;
} HRSContentLoader;

// Heap manipulation

/*
 * Create a Content Loader
 */
HRSContentLoader* hrscld_create(string_t contentPath);

/*
 * Assert that the HRSContentLoader object is not nullptr and has been initialized
 */
void hrscld_assert(HRSContentLoader *loader);

/*
 * Free a Content Loader
 */
void hrscld_free(HRSContentLoader *loader);

// Limits

/*
 * Get max unit textures limit
 * Try to use the constant 'HRS_MIN_TEXTURE_UNIT_LIMIT' instead
 */
int hrscld_getTextureUnitLimit(HRSContentLoader *loader);

/*
 * Get max bound textures limit
 * Try to use the constant 'HRS_MIN_TEXTURE_BOUND_LIMIT' instead
 */
int hrscld_getTextureBoundLimit(HRSContentLoader *loader);

// Texture loading

/*
 * Load a texture from a archive
 */
HRSTexture hrscld_loadTextureFrom(HRSContentLoader *loader, string_t path, int minimapLevel);

#endif