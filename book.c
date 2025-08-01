// ===============================
// File: book.c
// ===============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "book.h"

Book *pbook = NULL;
static int *pbook_del = NULL;
int book_count = 0;
static int book_count_del = 0;
static int book_capacity = 0;
static int book_capacity_del = 0;

void book_init() {
    book_capacity_del = book_capacity = INITIAL_CAPACITY;
    pbook = (Book *)malloc(book_capacity * sizeof(Book));
    pbook_del = (int *)malloc(book_capacity_del * sizeof(int));
}

static void resize_books() {
    book_capacity *= 2;
    pbook = (Book *)realloc(pbook, book_capacity * sizeof(Book));
}

static void resize_books_del() {
    book_capacity_del *= 2;
    pbook_del = (int *)realloc(pbook_del, book_capacity_del * sizeof(int));
}

void book_add() {
    if (book_count == book_capacity) resize_books();

    Book *b = &pbook[book_count++];
    if (book_count_del != 0)
        b->id = pbook_del[--book_count_del];
    else
        b->id = book_count;

    b->is_borrowed = false;

    char buffer[MAX_BOOK_LEN];
    printf("Enter book title: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    b->title = strdup(buffer);

    printf("Enter author: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    b->author = strdup(buffer);

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

    char buffer[MAX_BOOK_LEN];
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
    pbook_del[book_count_del++] = id;
    free(pbook[idx].title);
    free(pbook[idx].author);
    pbook[idx] = pbook[--book_count];
    printf("Book deleted.\n");
}

void book_search() {
    char keyword[MAX_BOOK_LEN];
    printf("Enter keyword to search (title or author): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    bool found = false;
    for (int i = 0; i < book_count; ++i) {
        if (strstr(pbook[i].title, keyword) || strstr(pbook[i].author, keyword)) {
            found = true;
            printf("ID: %d, Title: %s, Author: %s, %s\n",
                   pbook[i].id, pbook[i].title, pbook[i].author,
                   pbook[i].is_borrowed ? "Borrowed" : "Available");
            break;
        }
    }

    if (!found) {
        printf("No books found matching the keyword.\n");
    }
}

void book_list() {
    if (book_count == 0) {
        printf("No books available.\n");
        return;
    }
    for (int i = 0; i < book_count; ++i) {
        printf("ID: %d, Title: %s, Author: %s, %s\n",
               pbook[i].id, pbook[i].title, pbook[i].author,
               pbook[i].is_borrowed ? "Borrowed" : "Available");
    }
}

void book_free() {
    for (int i = 0; i < book_count; ++i) {
        pbook[i].id = 0;
        free(pbook[i].title);
        free(pbook[i].author);
        pbook[i].is_borrowed = false;
    }
    book_count = 0;
    free(pbook);
}

int book_find_index(int id) {
    for (int i = 0; i < book_count; ++i) {
        if (pbook[i].id == id) return i;
    }
    return -1;
}