// ===============================
// File: book.c
// ===============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "book.h"

#define INITIAL_CAPACITY 10

typedef struct {
    int id;
    char *title;
    char *author;
    bool is_borrowed;
} Book;

static Book *pbook = NULL;
static Book *pbook_del = NULL;
static int book_count = 0;
static int book_count_del = 0;
static int book_capacity = 0;
static int book_capacity_del = 0;

void book_init() {
    book_capacity_del = book_capacity = INITIAL_CAPACITY;
    pbook = (Book *)malloc(book_capacity * sizeof(Book));
    pbook_del = (Book *)malloc(book_capacity_del * sizeof(Book));
}

static void resize_books() {
    book_capacity *= 2;
    pbook = (Book *)realloc(pbook, book_capacity * sizeof(Book));
}

static void resize_books_del() {
    book_capacity_del *= 2;
    pbook_del = (Book *)realloc(pbook_del, book_capacity_del * sizeof(Book));
}

void book_add() {
    if (book_count == book_capacity) resize_books();

    Book *b = &pbook[book_count];
    b->id = book_count + 1;
    b->is_borrowed = false;

    char buffer[256];
    printf("Enter book title: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    b->title = strdup(buffer);

    printf("Enter author: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    b->author = strdup(buffer);

    book_count++;
    printf("Book added successfully.\n");
}

void book_edit() {
    int id;
    printf("Enter book ID to edit: ");
    scanf("%d", &id);
    getchar();

    int idx = book_find_index(id);
    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    char buffer[256];
    printf("Enter new title: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    free(pbook[idx].title);
    pbook[idx].title = strdup(buffer);

    printf("Enter new author: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    free(pbook[idx].author);
    pbook[idx].author = strdup(buffer);

    printf("Book updated.\n");
}

void book_delete() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);
    getchar();

    int idx = book_find_index(id);
    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    if (book_count_del == book_capacity_del) resize_books_del();
    Book *del = &pbook_del[book_count_del];
    //free(pbook[idx].title);
    //free(pbook[idx].author);
    printf("book_count %d\n",book_count);
    pbook[idx] = pbook[--book_count];
    printf("Book deleted.\n");
}

void book_search() {
    char keyword[256];
    printf("Enter keyword to search (title or author): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    for (int i = 0; i < book_count; ++i) {
        if (strstr(pbook[i].title, keyword) || strstr(pbook[i].author, keyword)) {
            printf("ID: %d, Title: %s, Author: %s, %s\n",
                   pbook[i].id, pbook[i].title, pbook[i].author,
                   pbook[i].is_borrowed ? "Borrowed" : "Available");
        }
    }
}

void book_list() {
    for (int i = 0; i < book_count; ++i) {
        printf("ID: %d, Title: %s, Author: %s, %s\n",
               pbook[i].id, pbook[i].title, pbook[i].author,
               pbook[i].is_borrowed ? "Borrowed" : "Available");
    }
}

void book_free() {
    for (int i = 0; i < book_count; ++i) {
        free(pbook[i].title);
        free(pbook[i].author);
    }
    free(pbook);
}

int book_find_index(int id) {
    for (int i = 0; i < book_count; ++i) {
        if (pbook[i].id == id) return i;
    }
    return -1;
}