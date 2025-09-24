#include "feta.h"
#include "letter.h"
#include "syllable.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "mistake.h"

FILE* file;
wchar_t word[65];

bool needsAccuteAccent(syllable_info_t info) {
    letter_info_t* letters = info.letterInfo;

    // count the capital letters
    int i = 0;
    int capitalLetters = 0;
    while (1) {
        letter_info_t letter = letters[i];

        if (letter.isCapital) capitalLetters++;
        if (letter.isLast) break;
        i++;
    }

    // a word needs accute accent only if all letters are lowercase or all letters are lowercase except the first
    if (capitalLetters == 0) return true;
    else if (capitalLetters == 1 && letters[0].isCapital) return true;
    return false;
}

int main(int argc, const char** argv) {
    setlocale(LC_ALL, "el_GR.UTF-8");

    printf("feta-check with libfeta v%s by Vitabytes\n", LIBFETA_VERSION);

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    file = fopen(argv[1], "r");
    if (!file) {
        perror("Couldn't open file");
        return -1;
    }

    char terminator[65];
    bool endOfSentence = false;
    int words = 0;
    while (1) {
        int ret = fscanf(file, "%64l[^!;:., \n]%64[!;:., \n]", word, terminator);
        if (ret == EOF) break;

        printf("\rAnalyzing... (%d words processed)", words);

        endOfSentence = terminator[0] != ' ' && terminator[0] != ',';
        
        syllable_info_t syllableInfo = syllable_count(word);
        if (!needsAccuteAccent(syllableInfo)) continue;

        int i = 0;
        int accentCount = 0;
        while (1) {
            if (syllableInfo.letterInfo[i].hasAccent) accentCount++;
            if (syllableInfo.letterInfo[i++].isLast) break;
        }

        // only words with multiple syllables can have accent
        if (syllableInfo.count == 1 && accentCount != 0) mistake_add(MISTAKE_TYPE_EXCESS_ACCENT, ftell(file), word);
        else if (syllableInfo.count > 1 && accentCount == 0) mistake_add(MISTAKE_TYPE_NO_ACCENT, ftell(file), word);

        free(syllableInfo.letterInfo);
        words++;
    }
    fclose(file);

    printf("\nSUMMARY:\n");
    printf("%d mistakes found.\n\n", mistake_get_count());
    mistake_summary();
    return 0;
}