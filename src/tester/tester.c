#include <ncurses.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>

#include <syllable.h>

#define PASSED_COLOR 2
#define FAILED_COLOR 3

int main(int argc, const char** argv) {
    if (argc < 2) {
        printf("Usage: %s <path to dictionary>\n", argv[0]);
        return -1;
    }

    setlocale(LC_ALL, "el_GR.UTF-8");

    FILE* dict = fopen(argv[1], "r");
    if (!dict) {
        printf("Couldn't open dictionary: %s\n", strerror(errno));
        return -1;
    }

    // get the size of the dictionary
    fseek(dict, 0, SEEK_END);
    int dictSize = ftell(dict);
    fseek(dict, 0, SEEK_SET);

    // count words (newlines in the dictionary)
    int totalWords = 0;
    int charsFromNewline = 0;
    int ignoredChars = 0;
    bool ignoreLine = false;
    char c;
    for (int i = 0; i < dictSize; i++) {
        c = getc(dict);
        if (charsFromNewline == 0 && c == '#') ignoreLine = true; // ignore comment lines

        if (ignoreLine) ignoredChars++;
        charsFromNewline++;
        if (c == '\n') {
            if (!ignoreLine) totalWords++;
            charsFromNewline = 0;
            ignoreLine = false;
        }
    }
    fseek(dict, ignoredChars, SEEK_SET);

    FILE* failedOut = fopen("failed.txt", "w");

    initscr();
    cbreak();

    start_color();
    init_pair(PASSED_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(FAILED_COLOR, COLOR_RED, COLOR_BLACK);

    int passedTests = 0;
    int failedTests = 0;

    mvaddstr(0, 0, "Syllable counter tester program");
    move(1, 0);
    printw("Testing %d words", totalWords);

    mvaddstr(8, 0, "Press any key to start the testing");
    getch();
    clrtoeol();

    wchar_t word[64];
    wchar_t syllables[64];
    wchar_t generatedSyllables[64];
    for (int i = 0; i < totalWords; i++) {
        fscanf(dict, "%ls %ls", word, syllables);

        syllable_info_t info = syllable_count(word);

        int pos = 0;
        for (int j = 0; j < info.count; j++) {
            for (int k = info.segments[j][0]; k <= info.segments[j][1]; k++) {
                wcscpy(&generatedSyllables[pos], info.letterInfo[k].letter);
                pos += wcslen(info.letterInfo[k].letter);
                if (info.letterInfo[k].isLast) break;
            }
            if (j != info.count - 1) generatedSyllables[pos++] = L'-';
        }
        generatedSyllables[pos] = L'\0';
        
        if (!wcscmp(syllables, generatedSyllables)) {
            passedTests++;
        }
        else {
            failedTests++;
            fprintf(failedOut, "%ls %ls\n", word, generatedSyllables);
        }

        move(3, 0);
        attron(COLOR_PAIR(PASSED_COLOR));
        printw("%06d tests passed (%06.2f%%)", passedTests, (float)passedTests / totalWords * 100.0f);
        attroff(COLOR_PAIR(PASSED_COLOR));
        move(4, 0);
        attron(COLOR_PAIR(FAILED_COLOR));
        printw("%06d tests failed (%06.2f%%)", failedTests, (float)failedTests / totalWords * 100.0f);
        attroff(COLOR_PAIR(FAILED_COLOR));
        move(5, 0);
        printw("%06d of tests completed (%06.2f%%)", passedTests + failedTests, (float)(passedTests + failedTests) / totalWords * 100.0f);
        refresh();
    }

    mvaddstr(7, 0, "All tests have completed. Press any key to exit.");
    getch();

    endwin();

    fclose(dict);
    fclose(failedOut);
    return 0;
}