#ifndef HELERIS_TYPES_H
#error This header cannot be included separately. Use "#include <heleris/fw.h>" or, if you are developing the heleris framework, use "#include "(path)types.h""
#endif

#ifndef HELERIS_TYPES_STRING_H
#define HELERIS_TYPES_STRING_H

#include <stdio.h>

typedef struct HRSString {
    char *_chars;
    size_t _chars_s;
} HRSString;

typedef HRSString string_t;

string_t str_fromPrimitive(char *_chars);

string_t str_fromSizedPrimitive(char *_chars, size_t _chars_s);

void str_append(string_t *base, string_t stringToAppend);

char str_getCharAt(string_t *base, size_t index);

void str_setCharAt(string_t *base, size_t index, char _char);

string_t str_getFromTo(string_t *base, size_t from, size_t to);

void str_setFromTo(string_t *base, size_t from, size_t to, char _char);

#endif