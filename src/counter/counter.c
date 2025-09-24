#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include <feta.h>


int main(int argc, const char** argv) {
    setlocale(LC_ALL, "el_GR.UTF-8");

    printf("feta-counter with libfeta v%s by Vitabytes\n", LIBFETA_VERSION);

    if (argc < 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return -1;
    }

    int cWordSize = strlen(argv[1]);
    wchar_t word[cWordSize];
    mbstowcs(word, argv[1], cWordSize);

    syllable_info_t syllableInfo = syllable_count(word);
    wchar_t outputString[64];
    syllable_get_string(syllableInfo, outputString);

    printf("%ls\n", outputString);
    fflush(stdout);

    free(syllableInfo.segments);
    free(syllableInfo.letterInfo);
    return 0;
}