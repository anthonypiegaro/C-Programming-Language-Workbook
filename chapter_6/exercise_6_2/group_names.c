#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXWORDS 20000
#define MAXGROUP 100

struct key {
    char *word;
} keytab[] = {
    "char",
    "double",
    "double",
    "float",
    "int",
    "long",
    "short",
    "signed",
    "unsigned",
    "void",
};

struct tnode {
    char *variables[MAXGROUP];
    int variablesp;
    struct tnode *left;
    struct tnode *right;
};

#define NKEYS (sizeof keytab / sizeof(keytab[0]))

int getword(char *, int);
int binsearch(char *, struct key *, int);
struct tnode *addtree(struct tnode *p, char *w, int pattern_length);
struct tnode *talloc(void);
char *strdup_(char *s);
void print_groups(struct tnode *tree, int pattern_length);
void print_vars(char *s[], int length);

int main(int argc, char *argv[]) {
    int n;
    char word[MAXWORD];
    int pattern_length = 6;

    if (argc > 1) {
        pattern_length = atoi(argv[1]);
    }

    struct tnode *root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                getword(word, MAXWORD);
                if (isalpha(word[0])) {
                    root = addtree(root, word, pattern_length);
                }
            }

    printf("Variable groups with same pattern to index %d\n\n", pattern_length);
    print_groups(root, pattern_length);
    return 0;
}

int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
} 

int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (c == '#')
        while ((c = getch()) != EOF && c != '\n')
            ;
    if (c == '/')
        if ((c = getch()) == '/') {
            while ((c = getch()) != EOF && c != '\n')
                ;
        } else if (c == '*') {
            while ((c = getch()) != EOF) {
                if (c == '*') {
                    if ((c = getch()) == '/') {
                        break;
                    } else {
                        ungetch(c);
                    }
                }
            }
        } else {
            ungetch(c);
            c = '/';
        }
    if (c == '\"') {
        while ((c = getch()) != EOF && c != '\"')
            ;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
    }
    *w = '\0';
    return word[0];
}

#define STORAGE (MAXWORDS * MAXWORD)

int buffer[STORAGE];
int bufferp = 0;

int getch(void) {
    return (bufferp) ? buffer[--bufferp] : getchar(); 
}

void ungetch(int c) {
    if (bufferp == STORAGE)
        printf("error: not enough storage to store \"%c\" in buffer\n", c);
    else
        buffer[bufferp++] = c;
}

struct tnode *addtree(struct tnode *p, char *w, int pattern_length) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->variables[p->variablesp++] = strdup_(w);
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->variables[0], pattern_length)) > 0) {
        p->right = addtree(p->right, w, pattern_length);
    } else if (cond < 0) {
        p->left = addtree(p->left, w, pattern_length);
    } else {    
        p->variables[p->variablesp++] = strdup_(w);
    }

    return p;
}

char *strdup_(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

void print_vars(char *s[], int length) {
    for (int i = 0; i < length; ++i) {
        printf((i == length - 1) ? "%s\n\n" : "%s, ", *(s + i));
    }
}

void print_groups(struct tnode *tree, int pattern_length) {
    if (tree != NULL) {
        print_groups(tree->left, pattern_length);
        print_vars(tree->variables, tree->variablesp);
        print_groups(tree->right, pattern_length);
    }
}
