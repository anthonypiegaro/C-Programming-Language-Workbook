#include <stdio.h>

#define MAX_WORD_SIZE 1000
#define TAB_SPACE 8
#define VALID_LINE_LENGTH 80
#define TRUE 1
#define FALSE 0

int main() {
    int c;
    int wc;
    int line_length;
    int word_length;
    int blank_seen;
    char current_word[MAX_WORD_SIZE];

    blank_seen = FALSE;
    word_length = 0;
    while ((c = getchar()) != EOF) {
        ++line_length;

        if (c == ' ') {
            blank_seen = TRUE;
            for (int i = 0; i < word_length; ++i) {
                putchar(current_word[i]);
            }
            putchar(' ');
            word_length = 0;
        } else if (c == '\t') {
            line_length = ((line_length - 1) / TAB_SPACE) * TAB_SPACE + TAB_SPACE;
            putchar('\t');
            word_length = 0;
            blank_seen = TRUE;
        } else if (c == '\n') {
            for (int i = 0; i < word_length; ++i) {
                putchar(current_word[i]);
            }
            putchar('\n');

            blank_seen = FALSE;
            word_length = 0;
            line_length = 0;
        } else {
            ++word_length;
            current_word[word_length - 1] = c;

            if (blank_seen && line_length > VALID_LINE_LENGTH) {
                putchar('\n');

                for (int i = 0; i < word_length; ++i) {
                    putchar(current_word[i]);
                }

                word_length = 0;
                blank_seen = FALSE;
                line_length = 0;
            }
        }
    }

    return 0;
}
