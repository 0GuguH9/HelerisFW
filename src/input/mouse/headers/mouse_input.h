#ifndef HELERIS_INPUT_MOUSE_H
#define HELERIS_INPUT_MOUSE_H

#include "mouse_click.h"
#include "../../../elements/headers/vector2.h"

typedef struct HRSMouseInput {
    HRSVector2 position;
    enum EHRSMouseClickType clickType;
} HRSMouseInput;

#endif