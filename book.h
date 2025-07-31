// ===============================
// File: book.h
// ===============================
#ifndef BOOK_H
#define BOOK_H

#define INITIAL_CAPACITY 10
#define MAX_BOOK_LEN 256

void book_init();
void book_add();
void book_edit();
void book_delete();
void book_search();
void book_list();
void book_free();
int book_find_index(int id);

#endif