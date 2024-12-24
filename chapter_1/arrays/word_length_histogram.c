#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX_WORD_LENGTH 8

main() {
    int length_counts[MAX_WORD_LENGTH + 1];
    int c;
    int state;
    int curr_length;

    for (int i = 0; i <= MAX_WORD_LENGTH; ++i) {
        length_counts[i] = 0;
    }
    state = OUT;
    curr_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                state = OUT;
                ++length_counts[curr_length];
                curr_length = 0;
            }
        } else {
            if (state == OUT) {
                state = IN;
            }
            if (curr_length < 20) {
                ++curr_length;
            }
        }
    }

    for (int i = 1; i <= MAX_WORD_LENGTH; ++i) {
        printf("\n");
        for (int j = 1; j <= length_counts[i]; ++j) {
            printf("*");
        }
    }
}