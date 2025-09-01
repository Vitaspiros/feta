#pragma once

#include <wchar.h>

typedef struct {
    int count;
    int (*segments)[2];
} syllable_info_t;

syllable_info_t syllable_count(wchar_t* word);