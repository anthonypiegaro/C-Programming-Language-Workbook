#include <stdio.h>
#define MAXSIZE 1000

int main() {
    int c;
    char line[MAXSIZE];
    int last_valid_idx;

    c = 0;
    while (c != EOF) {
        last_valid_idx = -1;
        for (int i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
            if (c != '\t' && c != ' ') {
                last_valid_idx = i;
            }
            line[i] = c;
        }

        if (last_valid_idx == -1) {
            printf("\n");
        }

        line[last_valid_idx + 1] = '\n';
        line[last_valid_idx + 2] = '\0';

        printf("%s", line);
    }

    return 0;
}
