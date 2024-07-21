#ifndef HELERIS_TYPES_H
#error This header cannot be included separately. Use "#include <heleris/fw.h>" or, if you are developing the Heleris FW, use "#include "(path)types.h""
#endif

#ifndef HELERIS_TYPES_PRIMITIVES_H
#define HELERIS_TYPES_PRIMITIVES_H

#include <stdint.h>

typedef uint8_t byte_t;

#define BYTE_T_MIN 0x00
#define BYTE_T_MAX 0xFF

typedef uint32_t glObject_t;

#define GL_OBJECT_T_MIN 0x00000000
#define GL_OBJECT_T_MAX 0xFFFFFFFF

#endif