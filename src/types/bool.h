#ifndef HELERIS_TYPES_H
#error This header cannot be included separately. Use "#include <heleris/fw.h>" or, if you are developing the heleris framework, use "#include "(path)types.h""
#endif

#ifndef HELERIS_TYPES_BOOL_H
#define HELERIS_TYPES_BOOL_H

typedef enum EHRSBool {
    FALSE = 0,
    TRUE = 1,
} EBool;

typedef EBool bool_t;

#endif