#pragma once

#include <wchar.h>
#include <stdbool.h>


typedef enum {
    LETTER_TYPE_VOWEL,
    LETTER_TYPE_CONSONANT
} letter_type_t;

typedef struct {
    wchar_t letter[4]; // can include up to three actual letters
    letter_type_t type;
    bool isDigraph; // false if the struct contains one letter, true if it contains two
    bool isCapital;
    bool hasAccent;

    bool isLast;
} letter_info_t;


letter_info_t* get_letters_from_word(wchar_t* word);
void letters_debug(wchar_t* word);