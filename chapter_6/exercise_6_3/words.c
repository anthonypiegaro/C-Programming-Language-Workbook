#include <stdio.h>
#include <stdlib.h>

#define MAXWORDLEN 100
#define MAXWORDSPERLINE 100

char *noise_words[] = {
    "a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "aren't", 
    "aren't", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", 
    "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", 
    "during", "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't", 
    "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers", "herself", "he's", "how", "how's", 
    "howsoever", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", "is", "isn't", "it", "it'd", "it'll", 
    "it's", "it's", "its", "itself", "let's", "me", "meant", "more", "most", "mustn't", "my", "myself", "myself", 
    "must", "mustn't", "need", "needn't", "nor", "not", "of", "off", "on", "once", "only", "onto", "or", "other", 
    "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over", "own", "same", "should", "shouldn't", 
    "so", "so's", "some", "such", "than", "that", "that's", "that'd", "that'll", "that've", "that's", "the", "the's", 
    "their", "theirs", "themselves", "there", "there's", "these", "they", "they'd", "they'll", "they're", "they've", 
    "this", "this'd", "this'll", "this's", "those", "though", "through", "to", "too", "under", "until", "up", "very", 
    "was", "wasn't", "we", "we'd", "we'll", "we're", "we've", "we'll", "weren't", "what", "what's", "whatsoever", 
    "when", "when's", "where", "where's", "whereas", "wherever", "whether", "which", "which's", "while", "why", 
    "why's", "whysoever", "with", "withal", "within", "without", "won't", "would", "wouldn't"
};

int noise_words_length = sizeof(noise_words) / sizeof(noise_words[0]);
int line_count = 1;

struct word_tnode {
    char *word;
    int line_numbers[MAXWORDSPERLINE];
    int line_number_len;
    struct word_tnode *left;
    struct word_tnode *right;
};

char getword(char *w);
char valid_first_char(char c);
char valid_char(char c);
int binary_search(char *s);
char strcmp(char *s, char *t);
char getch(void);
struct word_tnode *add_word_node(struct word_tnode *node, char *word);
struct word_tnode *word_talloc(void);
int strlen(char *s);
char *strdup(char *s);
void strcpy(char *s, char *t);
void print_tree(struct word_tnode *node);

int main() {
    char word[MAXWORDLEN];
    char c;
    struct word_tnode *root = NULL;

    do {
        c = getword(word);
        if (binary_search(word) == -1)
            root = add_word_node(root, word);
    } while (c != EOF);

    print_tree(root);
    return 0;
}

char getword(char *w) {
    while (!valid_first_char(*w = getch()) && *w != EOF)
        ;
    
    while (valid_char(*w))
        *++w = getch();
    
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

int binary_search(char *s) {
    int left, mid, right;
    char cond;

    left = 0;
    right = noise_words_length - 1;
    while (left <= right) {
        mid = (right + left) / 2;

        if ((cond = strcmp(s, noise_words[mid])) < 0) {
            right = mid - 1;
        } else if (cond > 0) {
            left = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
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

char getch(void) {
    char c = getchar();

    if (c == '\n')
        ++line_count;
    
    return c;
}

struct word_tnode *add_word_node(struct word_tnode *node, char *word) {
    char cond;

    if (node == NULL) {
        node = word_talloc();
        node->word = strdup(word);
        node->line_numbers[0] = line_count;
        node->line_number_len = 1;
        node->left = node->right = NULL;
    } else if ((cond = strcmp(word, node->word)) < 0) {
        node->left = add_word_node(node->left, word);
    } else if (cond > 0) {
        node->right = add_word_node(node->right, word);
    } else {
        if (node->line_numbers[node->line_number_len - 1] != line_count) {
            if (node->line_number_len == MAXWORDSPERLINE) {
                printf("error: word appeared too many times in document\n");
            } else {
                node->line_numbers[node->line_number_len++] = line_count;
            }
        }
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
        printf("%s: ", node->word);
        for (int i = 0; i < node->line_number_len; ++i) {
            printf((i < node->line_number_len - 1) ? "%d, " : "%d\n", node->line_numbers[i]);
        }
        print_tree(node->right);
    }
}
