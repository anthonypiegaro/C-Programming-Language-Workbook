#include <stdio.h>

int strend(char *s, char *t);

int main() {
    char *s, *t;
    int expected_output;

    s = "";
    t = "";
    expected_output = 1;
    printf("Test 1:\nInput: s=\"%s\", t=\"%s\"\tExpected Output: %d\tOutput: %d\t result: %s\n\n", s, t, expected_output, strend(s, t), (strend(s, t) == expected_output) ? "Pass" : "Fail");

    s = "Hello World";
    t = "";
    expected_output = 1;
    printf("Test 2:\nInput: s=\"%s\", t=\"%s\"\tExpected Output: %d\tOutput: %d\t result: %s\n\n", s, t, expected_output, strend(s, t), (strend(s, t) == expected_output) ? "Pass" : "Fail");

    s = "";
    t = "Hello World";
    expected_output = 0;
    printf("Test 3:\nInput: s=\"%s\", t=\"%s\"\tExpected Output: %d\tOutput: %d\t result: %s\n\n", s, t, expected_output, strend(s, t), (strend(s, t) == expected_output) ? "Pass" : "Fail");

    s = "Hi";
    t = "i";
    expected_output = 1;
    printf("Test 4:\nInput: s=\"%s\", t=\"%s\"\tExpected Output: %d\tOutput: %d\t result: %s\n\n", s, t, expected_output, strend(s, t), (strend(s, t) == expected_output) ? "Pass" : "Fail");

    s = "Hello World";
    t = "World";
    expected_output = 1;
    printf("Test 5:\nInput: s=\"%s\", t=\"%s\"\tExpected Output: %d\tOutput: %d\t result: %s\n\n", s, t, expected_output, strend(s, t), (strend(s, t) == expected_output) ? "Pass" : "Fail");


    s = "Hello World";
    t = "Hello";
    expected_output = 0;
    printf("Test 6:\nInput: s=\"%s\", t=\"%s\"\tExpected Output: %d\tOutput: %d\t result: %s\n\n", s, t, expected_output, strend(s, t), (strend(s, t) == expected_output) ? "Pass" : "Fail");

    s = "Hello";
    t = "Hello";
    expected_output = 1;
    printf("Test 7:\nInput: s=\"%s\", t=\"%s\"\tExpected Output: %d\tOutput: %d\t result: %s\n\n", s, t, expected_output, strend(s, t), (strend(s, t) == expected_output) ? "Pass" : "Fail");

    return 0;
}

/* returns 1 if the string t occurs at the end of the string s, and zero otherwise */
int strend(char *s, char *t) {
    int s_len, t_len;
    s_len = t_len = 0;

    while (*s) {
        ++s_len;
        ++s;
    }
    
    while (*t) {
        ++t_len;
        ++t;
    }
    
    if (t_len > s_len)
        return 0;
    
    for (; t_len >= 0; --t_len) {
        if (*s-- != *t--)
            return 0;
    }

    return 1;
}
