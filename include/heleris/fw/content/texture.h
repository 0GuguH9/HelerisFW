#ifndef HELERIS_FW_CONTENT_TEXTURE_H
#define HELERIS_FW_CONTENT_TEXTURE_H

#include "../elements/size.h"
#include "../elements/color.h"

typedef struct HRSTexture {
    HRSSize _size;
    glObject_t glTexture;
} HRSTexture;

/*
 * Create a texture based on a byte_t (aka unsigned char) data.
 * You can make (by exemple) a white pixel texture with:
 *     byte_t data[3] = {255, 255, 255};
 *     HRSSize _size = hrssz_create(1, 1);
 *     hrstxt_fromData(_size, data, HRS_COLOR_RGB, 0);
 */
HRSTexture hrstxt_fromData(HRSSize _size, byte_t *data, enum HRSColorTypes _colorType, int minimapLevel);

#endif