#include "letter.h"
#include "syllable.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "mistake.h"

FILE* file;
wchar_t word[64];

int main(int argc, const char** argv) {
    setlocale(LC_ALL, "el_GR.UTF-8");

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    file = fopen(argv[1], "r");
    if (!file) {
        perror("Couldn't open file");
        return -1;
    }

    char terminator[4];
    bool endOfSentence = false;
    int words = 0;
    while (1) {
        int ret = fscanf(file, "%l[^!;:., \n]%2[!;:., \n]", word, terminator);
        if (ret == EOF) break;

        printf("\rAnalyzing... (%d words processed)", words);

        endOfSentence = terminator[0] != ' ' && terminator[0] != ',';
        
        syllable_info_t syllableInfo = syllable_count(word);

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