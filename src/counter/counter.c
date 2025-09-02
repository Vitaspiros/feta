#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include <syllable.h>


int main(int argc, const char** argv) {
    setlocale(LC_ALL, "el_GR.UTF-8");

    if (argc < 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return -1;
    }

    int cWordSize = strlen(argv[1]);
    wchar_t word[cWordSize];
    mbstowcs(word, argv[1], cWordSize);

    syllable_info_t syllableInfo = syllable_count(word);
    for (int i = 0; i < syllableInfo.count; i++) {
        for (int j = syllableInfo.segments[i][0]; j <= syllableInfo.segments[i][1]; j++) {
            printf("%ls", syllableInfo.letterInfo[j].letter);
        }
        if (i != syllableInfo.count - 1) printf("-");
    }
    putchar('\n');
    fflush(stdout);

    free(syllableInfo.segments);
    free(syllableInfo.letterInfo);
    return 0;
}