#pragma once

#include <wchar.h>
#include <stdbool.h>


typedef enum {
    LETTER_TYPE_VOWEL,
    LETTER_TYPE_CONSONANT
} letter_type_t;

typedef struct {
    wchar_t letter[3]; // can include up to two actual letters
    letter_type_t type;
    bool isLast;
} letter_info_t;


letter_info_t* get_letters_from_word(wchar_t* word);
void letters_debug(wchar_t* word);