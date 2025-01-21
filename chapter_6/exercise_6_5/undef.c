#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *s);

char *str_dup(char *s);

int main() {
    install("anthony", "24");
    install("carson", "24");
    install("avery", "4");
    install("avery", "5");

    printf("value of anthony: %s\n", lookup("anthony")->defn);
    printf("value of carson: %s\n", lookup("carson")->defn);
    printf("value of avery: %s\n", lookup("avery")->defn);

    undef("anthony");
    printf("\n");

    printf("Is anthony still in table? %s\n", (lookup("anthony") == NULL) ? "No" : "Yes");
    printf("Is carson still in table? %s\n", (lookup("carson") == NULL) ? "No" : "Yes");
    printf("Is avery still in table? %s\n", (lookup("avery") == NULL) ? "No" : "Yes");

    return 0;
}

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; ++s) {
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0)
            return np;
    }

    return NULL;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = str_dup(name)) == NULL)
            return NULL;
        
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }

    if ((np->defn = str_dup(defn)) == NULL)
        return NULL;
    
    return np;
}

void undef(char *s) {
    struct nlist *prev;
    struct nlist *curr;
    unsigned hashval;

    hashval = hash(s);

    if (hashtab[hashval] == NULL)
        return;
    
    if (strcmp(hashtab[hashval]->name, s) == 0) {
        free(hashtab[hashval]->name);
        free(hashtab[hashval]->defn);
        hashtab[hashval] = hashtab[hashval]->next;
        free(hashtab[hashval]);
        return;
    }
    
    prev = hashtab[hashval];
    curr = prev->next;

    while (strcmp(curr->name, s) != 0) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;

    free(curr->name);
    free(curr->defn);
    free(curr);
}

char *str_dup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);

    return p;
}
