#include <stdio.h>
#include <stdlib.h>

#define MAXWORDLEN 100
#define MAXWORDSPERLINE 100
#define MAXWORDS 10000

struct word_tnode {
    char *word;
    int count;
    struct word_tnode *left;
    struct word_tnode *right;
};

struct word_tnode *words[MAXWORDS];
int word_count = 0;

char getword(char *w);
char valid_first_char(char c);
char valid_char(char c);
char strcmp(char *s, char *t);
struct word_tnode *add_word_node(struct word_tnode *node, char *word);
struct word_tnode *word_talloc(void);
int strlen(char *s);
char *strdup(char *s);
void strcpy(char *s, char *t);
void print_tree(struct word_tnode *node);
void qsort_(struct word_tnode *v[], int left, int right);
void swap(struct word_tnode *v[], int i, int j);
void print_freq_sorted_words_desc(void);

int main() {
    char word[MAXWORDLEN];
    char c;
    struct word_tnode *root = NULL;

    while (1) {
        c = getword(word);
        if (c == EOF) {
            if (strlen(word) > 0)
                root = add_word_node(root, word);
            break;
        } else {
            root = add_word_node(root, word);
        }
    }

    qsort_(words, 0, word_count - 1);
    print_freq_sorted_words_desc();
    return 0;
}

char getword(char *w) {
    while (!valid_first_char(*w = getchar()) && *w != EOF)
        ;
    
    while (valid_char(*w))
        *++w = getchar();
    
    if (*w == EOF) {
        *w = '\0';
        return EOF;
    }

    *w = '\0';
    return 1;
}

char valid_first_char(char c) {
    return (48 <= c && c <= 57) || (65 <= c && c <= 90) || (97 <= c && c <= 122);
}

char valid_char(char c) {
    return (48 <= c && c <= 57) || (65 <= c && c <= 90) || (97 <= c && c <= 122) || (c == '_') || (c == '\'');
}

char strcmp(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0')
            return 0;
        ++s;
        ++t;
    }

    if (*s < *t)
        return -1;
    return 1;
}

struct word_tnode *add_word_node(struct word_tnode *node, char *word) {
    char cond;

    if (node == NULL) {
        node = word_talloc();
        node->word = strdup(word);
        node->count = 1;
        node->left = node->right = NULL;
        words[word_count++] = node;
    } else if ((cond = strcmp(word, node->word)) < 0) {
        node->left = add_word_node(node->left, word);
    } else if (cond > 0) {
        node->right = add_word_node(node->right, word);
    } else {
        node->count++;
    }

    return node;
}

struct word_tnode *word_talloc(void) {
    return (struct word_tnode *) malloc(sizeof(struct word_tnode));
}

int strlen(char *s) {
    char *start = s;
    while (*s != '\0')
        ++s;
    
    return s - start;
}

char *strdup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void strcpy(char *s, char *t) {
    while (*s++ = *t++)
        ;
}

void print_tree(struct word_tnode *node) {
    if (node != NULL) {
        print_tree(node->left);
        printf("%s - %d\n", node->word, node->count);
        print_tree(node->right);
    }
}

void qsort_(struct word_tnode *v[], int left, int right) {
    int last;
    
    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);

    last = left;

    for (int i = left + 1; i <= right; ++i) {
        if (v[i]->count > v[left]->count)
            swap(v, i, ++last);
    }

    swap(v, left, last);
    qsort_(v, left, last - 1);
    qsort_(v, last + 1, right);
}

void swap(struct word_tnode *v[], int i, int j) {
    struct word_tnode *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void print_freq_sorted_words_desc(void) {
    for (int i = 0; i < word_count; ++i) {
        printf("%s - %d\n", words[i]->word, words[i]->count);
    }
}
