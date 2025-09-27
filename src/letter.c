#include "letter.h"
#include "tables.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

#include "win32.h"

letter_info_t* get_letters_from_word(wchar_t* word) {
    int wordLength = wcslen(word);
    letter_info_t* info = calloc(wordLength, sizeof(letter_info_t));

    int infoCount = 0;
    int i;
    for (i = 0; i < wordLength; i++) {
        bool isVowel = false;
        wchar_t c = towlower(word[i]);
        for (int j = 0; j < 7; j++) {
            if (c == vowelsAccent[j]) {
                // set as vowel
                wcsncpy(info[infoCount].letter, &word[i], 1); // copy the letter into the struct
                info[infoCount].type = LETTER_TYPE_VOWEL;
                info[infoCount].isDigraph = false;
                info[infoCount].hasAccent = true;
                isVowel = true;
                break;
            } else if (c == vowels[j]) {
                if (i != wordLength - 1) { // if this isn't the last letter
                    // we check if the letter composes a diphthong
                    // diphthongs are composed of two letters and count as one vowel
                    bool found = false;
                    int diphthongLength;
                    int k;
                    for (k = 0; k < 28; k++) {
                        if (!wcsncasecmp(&word[i], diphthongs[k], wcslen(diphthongs[k]))) {
                            found = true;
                            diphthongLength = wcslen(diphthongs[k]);
                            break;
                        }
                    }

                    if (found) {
                        wcsncpy(info[infoCount].letter, &word[i], diphthongLength); // copy all letters into the struct
                        info[infoCount].type = LETTER_TYPE_VOWEL;
                        info[infoCount].isDigraph = true;
                        // check if k is in the range of diphthongs with an accute accent (this happens to be 0-8 and 22-28)
                        info[infoCount].hasAccent = k < 9 || k > 22;
                        i += diphthongLength - 1; // advance i, so we do not double count the next letter
                        isVowel = true;
                        break;
                    }
                }
                // else, this is a single vowel
                wcsncpy(info[infoCount].letter, &word[i], 1); // copy the letter into the struct
                info[infoCount].type = LETTER_TYPE_VOWEL;
                info[infoCount].isDigraph = false;
                info[infoCount].hasAccent = false;
                isVowel = true;
                break;
            }
        }

        if (!isVowel) {
            bool isConsonantDigraph = false;
            if (i != wordLength - 1) { // if this isn't the last letter
                // we check if the letter composes a consonant digraph
                // this is two consonants counted as a single consonant

                wchar_t nextChar = towlower(word[i + 1]);
                for (int j = 0; j < 6; j++) {
                    if (c == digraphs[j][0] && nextChar == digraphs[j][1]) {
                        isConsonantDigraph = true;
                        break;
                    }
                }

                if (isConsonantDigraph) {
                    wcsncpy(info[infoCount].letter, &word[i], 2); // copy both letters into the struct
                    info[infoCount].type = LETTER_TYPE_CONSONANT;
                    info[infoCount].isDigraph = true;
                    i++; // advance i, so we do not double count the next letter
                }
            }

            if (!isConsonantDigraph) {
                wcsncpy(info[infoCount].letter, &word[i], 1); // copy the letter into the struct
                info[infoCount].type = LETTER_TYPE_CONSONANT;
                info[infoCount].isDigraph = false;
            }
            info[infoCount].hasAccent = false;
        }
        info[infoCount].isCapital = iswupper(word[i]);
        infoCount++;
    }
    info[infoCount - 1].isLast = true;

    return info;
}

void letters_debug(wchar_t* word) {
    letter_info_t* info = get_letters_from_word(word);

    int i = 0;

    while (true) {
        if (info[i].type == LETTER_TYPE_VOWEL) putchar('v');
        else putchar('c');

        if (info[i++].isLast) break;
    }
    putchar('\n');
    fflush(stdout);

    free(info);

}