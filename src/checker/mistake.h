#pragma once
#include <wchar.h>

typedef enum {
    MISTAKE_TYPE_NO_ACCENT,
    MISTAKE_TYPE_EXCESS_ACCENT,
} mistake_type_t;

typedef struct {
    mistake_type_t type;
    unsigned long position;
    wchar_t word[32];
} mistake_t;

void mistake_add(mistake_type_t, unsigned long, wchar_t* word);
int mistake_get_count();
void mistake_summary();