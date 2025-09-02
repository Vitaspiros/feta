#include "syllable.h"
#include "letter.h"
#include "tables.h"
#include <stdlib.h>

/*
    Rules of syllable counting:
        1)  When there is a consonant between two vowels (vcv), the consonant forms a syllable 
            with the second vowel (vcv -> v-cv).
        2)  When there are two consonants between two vowels (vccv), if the two consonants are in the
            startingSyllables table, the consonants form a syllable with the second vowel (vccv -> v-ccv).
            If they do not exist in the table, the first consonant forms a syllable with the first vowel,
            and the second consonant forms a syllable with the second vowel (vccv -> vc-cv).

*/

static void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sort_by_start_index(int array[16][2], int size) {
    while (1) {
        int swapCount = 0;
        for (int j = 0; j < size - 1; j++) {
            int* a = &array[j][0];
            int* b = &array[j + 1][0];
            if (*a > *b) {
                swap(&array[j][0], &array[j + 1][0]);
                swap(&array[j][1], &array[j + 1][1]);
                swapCount++;
            }
        }
        if (swapCount == 0) break;
    }
}

syllable_info_t syllable_count(wchar_t* word) {
    letter_info_t* info = get_letters_from_word(word);
    int (*syllables)[2] = malloc(sizeof(int[16][2]));
    int vowelIndices[32] = {0};
    int syllableCount = 0;

    int i = 0;
    int j = 0;
    while (1) {
        letter_info_t currentLetter = info[i];
        if (currentLetter.type == LETTER_TYPE_VOWEL) vowelIndices[j++] = i;
        i++;
        if (currentLetter.isLast) break;
    }

    int wordSize = i;

    // for rule 1 we check for two vowels, two letters apart.
    // this means we have one consonant between two vowels (vcv)
    // for rule 2 we check for two vowels three letters apart.
    int prevIndex = 0;
    for (int i = 0; i < 16; i++) {
        if (vowelIndices[i] - prevIndex < 0) break; // no more vowels
        if (vowelIndices[i] - prevIndex == 2) { // rule 1
            syllables[syllableCount][0] = vowelIndices[i] - 1;

            // the syllable will end at the next vowel
            int offset = 0;
            letter_info_t nextLetterInfo = info[vowelIndices[i] + 1];
            if (nextLetterInfo.type == LETTER_TYPE_CONSONANT && nextLetterInfo.isLast && vowelIndices[i] != wordSize - 1) offset = 1;
            syllables[syllableCount][1] = vowelIndices[i] + offset;
            syllableCount++;
        }

        else if (vowelIndices[i] - prevIndex == 3) { // rule 2
            wchar_t consonants[3];
            if (info[vowelIndices[i] - 1].isDigraph || info[prevIndex + 1].isDigraph) {
                // TODO: Rule 3
            } else {
                // put the two consonants in the array
                consonants[0] = info[prevIndex + 1].letter[0];
                consonants[1] = info[vowelIndices[i] - 1].letter[0];
                consonants[2] = '\0';

                bool found = false;
                for (int j = 0; j < 49; j++) {
                    if (!wcscasecmp(consonants, startingSyllables[j])) {
                        found = true;
                        break;
                    }
                }

                if (found)
                    syllables[syllableCount][0] = prevIndex + 1;
                else
                    syllables[syllableCount][0] = vowelIndices[i] - 1;

                syllables[syllableCount][1] = vowelIndices[i];
                syllableCount++;
            }
        }

        prevIndex = vowelIndices[i];
    }

    // add left over segments as syllables

    // check if the start of the word is included
    if (syllables[0][0] != 0) { // if the first syllable does not start from the start of the word
        // add one that starts from 0 up to that syllable
        syllables[syllableCount][0] = 0;
        syllables[syllableCount][1] = syllables[0][0] - 1;
        syllableCount++;
    }
    
    sort_by_start_index(syllables, syllableCount);
    // check if the end of the word is included
    if (syllables[syllableCount - 1][1] != wordSize - 1) {
        // add one that starts from the end of the last syllable up to the end of the word
        syllables[syllableCount][0] = syllables[syllableCount - 1][1] + 1;
        syllables[syllableCount][1] = wordSize;
        syllableCount++;
    }
    
    int* prevSegment = syllables[0];
    int currentSyllableCount = syllableCount;
    for (int i = 1; i < currentSyllableCount; i++) {
        int* thisSegment = syllables[i];

        if (thisSegment[0] - 1 == prevSegment[1]) {
            prevSegment = syllables[i];
            continue;
        }

        syllables[syllableCount][0] = prevSegment[1] + 1;
        syllables[syllableCount][1] = thisSegment[0] - 1;
        syllableCount++;


        prevSegment = syllables[i];
    }

    sort_by_start_index(syllables, syllableCount);

    syllable_info_t ret;
    ret.count = syllableCount;
    ret.segments = &syllables[0];
    ret.letterInfo = info;
    return ret;
}