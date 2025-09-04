#pragma once

#include "letter.h"
#include <wchar.h>

typedef struct {
    int count;
    int (*segments)[2];
    letter_info_t* letterInfo;
} syllable_info_t;

syllable_info_t syllable_count(wchar_t* word);
void syllable_get_string(syllable_info_t, wchar_t*);