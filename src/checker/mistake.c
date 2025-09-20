#include "mistake.h"
#include <stdio.h>

mistake_t mistakes[2048];
static int count = 0;

const char* mistakeMessages[] = {
    "no accute accent although it's needed", "excess accute accent"
};

void mistake_add(mistake_type_t type, unsigned long position, wchar_t* word) {
    mistakes[count].type = type;
    mistakes[count].position = position;
    wcscpy(mistakes[count].word, word);
    count++;
}

void mistake_summary() {
    for (int i = 0; i < count; i++) {
        printf("Mistake: %s\n", mistakeMessages[mistakes[i].type]);
        printf("\tIn word %ls at position %ld\n\n", mistakes[i].word, mistakes[i].position);
    }
}

int mistake_get_count() {
    return count;
}