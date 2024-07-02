#ifndef HELERIS_ELEMENTS_CLICK_CONTEXT_H
#define HELERIS_ELEMENTS_CLICK_CONTEXT_H

#include "vector2.h"
#include "../../input/mouse/headers/mouse_click.h"

typedef struct HRSClickContext {
    enum EHRSMouseClickType type;
    HRSVector2 position;
} HRSClickContext;

HRSClickContext hrscct_create(enum EHRSMouseClickType type, HRSVector2 position);

#endif