#ifndef HELERIS_ELEMENTS_CLICK_CONTEXT_H
#define HELERIS_ELEMENTS_CLICK_CONTEXT_H

#include "vector2.h"

typedef struct HRSClickContext {
    int type;
    HRSVector2 position;
} HRSClickContext;

HRSClickContext hrscct_create(int type, HRSVector2 position);

#endif