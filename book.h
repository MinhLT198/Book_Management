// ===============================
// File: book.h
// ===============================
#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

#define INITIAL_CAPACITY 10
#define MAX_BOOK_LEN 256

typedef struct {
    int id;
    char *title;
    char *author;
    bool is_borrowed;
} Book;

void book_init();
void book_add();
void book_edit();
void book_delete();
void book_search();
void book_list();
void book_free();
int book_find_index(int id);

#endif