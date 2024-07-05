#ifndef HELERIS_TYPES_H
#error This header cannot be included separately. Use "#include <heleris/fw.h>" or, if you are developing the heleris framework, use "#include "(path)types.h""
#endif

#ifndef HELERIS_TYPES_STRING_H
#define HELERIS_TYPES_STRING_H

#include <stdio.h>

#ifdef __cplusplus
#include <string>
typedef std::string string_t;
#else
typedef char * string_t;
#endif

typedef struct HRSString {
    string_t _string;
    size_t _chars_s;
} HRSString;

typedef HRSString ustring_t;

ustring_t str_fromPrimitive(string_t _string);

ustring_t str_fromSizedPrimitive(string_t _string, size_t _chars_s);

void str_append(ustring_t *base, ustring_t stringToAppend);

char str_getCharAt(ustring_t *base, size_t index);

void str_setCharAt(ustring_t *base, size_t index, char _char);

ustring_t str_getFromTo(ustring_t *base, size_t from, size_t to);

void str_setFromTo(ustring_t *base, size_t from, size_t to, char _char);

#endif