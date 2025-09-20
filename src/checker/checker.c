#include "letter.h"
#include "syllable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

FILE* file;
wchar_t word[64];

void mistake(const char* message) {
    printf("Mistake: %s\n", message);
    printf("\tAt word %ls at position %ld\n\n", word, ftell(file));
}

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
    while (1) {
        int ret = fscanf(file, "%l[^!;:. \n]%2[!;:. \n]", word, terminator);
        if (ret == EOF) break;

        endOfSentence = terminator[0] != ' ';
        
        syllable_info_t syllableInfo = syllable_count(word);

        int i = 0;
        int accentCount = 0;
        while (1) {
            if (syllableInfo.letterInfo[i].hasAccent) accentCount++;
            if (syllableInfo.letterInfo[i++].isLast) break;
        }

        // only words with multiple syllables can have accent
        if (syllableInfo.count == 1 && accentCount != 0) mistake("excess accute accent");
        else if (syllableInfo.count > 1 && accentCount == 0) mistake("no accute accent although it is needed");

        free(syllableInfo.letterInfo);
    }

    fclose(file);
    return 0;
}