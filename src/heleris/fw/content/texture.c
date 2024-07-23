#include "heleris/fw/content/texture.h"

#include "heleris/fw/elements/color.h"
#include "heleris/fw/types.h"

HRSTexture hrstxt_fromData(HRSSize _size, byte_t *data, enum HRSColorTypes _colorType, int minimapLevel) {

    glObject_t _glObject;

    glGenTextures(1, &_glObject);

    glBindTexture(GL_TEXTURE_2D, _glObject);

    glTexImage2D(GL_TEXTURE_2D, minimapLevel, _colorType, _size.width, _size.height, 0, _colorType, GL_UNSIGNED_BYTE, data);

    HRSTexture _texture = {_size, _glObject};

    return _texture;
}
