#include "heleris/fw/content/content_loader.h"

#include "heleris/fw/content/texture.h"
#include "heleris/fw/elements/color.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/types.h"

#include "stb/stb_image.h"

#include <stdlib.h>
#include <string.h>

const int HRS_MIN_TEXTURE_UNIT_LIMIT = 16;
const int HRS_MIN_TEXTURE_BOUND_LIMIT = 48;

// Heap manipulation

HRSContentLoader* hrscld_create(string_t path) {

    HRSContentLoader *loader = malloc(sizeof(HRSContentLoader));

    if (loader == nullptr)
        errpre_nullptr("HRSContentLoader");

    loader->path = path;

    stbi_set_flip_vertically_on_load(true);

    return loader;
}

void hrscld_assert(HRSContentLoader *loader) {

    if (loader == nullptr)
        errpre_nullptr("HRSContentLoader");
}

void hrscld_free(HRSContentLoader *loader) {

    free(loader);
    loader = nullptr;
}

// Texture loading

HRSTexture hrscld_loadTextureFrom(HRSContentLoader *loader, string_t path, int minimapLevel) {

    // Heap alloc for making a full path
    /* The size for:
     * strlen(loader->path) + strlen(path) -> size of the two peaces of full path
     * '+ 2' is for null byte at the end and the PATH_SEPARATOR ('/' in Linux and '\' in Windows)
     */
    // calloc create a heap object with all bytes with the value '0', making a full null string
    string_t restrict fullPath = calloc(strlen(loader->path) + strlen(path) + 2, sizeof(char));

    // Addind strings for the full path
    strcat(fullPath, loader->path);
    strcat(fullPath, PATH_SEPARATOR);
    strcat(fullPath, path);

    // Loading texture
    // Color Channels can define if the file is a jpg or a png
    int width, height, colorChannels;
    byte_t *data = stbi_load(fullPath, &width, &height, &colorChannels, 0);

    // Fre heap memory
    free(fullPath);

    // Creating texture object
    // We can't swap "HRSTexture texture =" with return, we need to free "data" heap object
    HRSTexture texture = hrstxt_fromData(hrssz_create(width, height), data, colorChannels == 3 ? HRS_COLOR_RGB : HRS_COLOR_RGBA, minimapLevel);

    // Free the data, to avoid memory leaks
    stbi_image_free(data);
    
    return texture;
}
