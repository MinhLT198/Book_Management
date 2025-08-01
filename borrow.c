// ===============================
// File: borrow.c
// ===============================
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "book.h"
#include "user.h"
#include "borrow.h"

void book_borrow() {
    int book_id, user_id;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &book_id);
    printf("Enter User ID: ");
    scanf("%d", &user_id);

    int b_index = book_find_index(book_id);
    int u_index = user_find_index(user_id);

    if (b_index == -1 || u_index == -1) {
        printf("Book or User not found.\n");
        return;
    }

    if (pbook[b_index].is_borrowed == true) {
        printf("Book has been borrowed. Cannot be borrowed.\n");
        return;
    }

    User *u = &user[u_index];
    u->borrowed_books = realloc(u->borrowed_books, (u->borrowed_count+1) * sizeof(int));
    u->borrowed_books[u->borrowed_count++] = book_id;
    pbook[b_index].is_borrowed = true;

    printf("Book borrowed successfully.\n");
}

void book_return() {
    int book_id, user_id;
    printf("Enter Book ID to return: ");
    scanf("%d", &book_id);
    printf("Enter User ID: ");
    scanf("%d", &user_id);

    int b_index = book_find_index(book_id);
    int u_index = user_find_index(user_id);

    if (b_index == -1 || u_index == -1) {
        printf("Book or User not found.\n");
        return;
    }

    if (pbook[b_index].is_borrowed == false) {
        printf("User did not borrow this book.\n");
        return;
    }

    User *u = &user[u_index];
    int found = 0;
    for (int i = 0; i < u->borrowed_count; i++) {
        if (u->borrowed_books[i] == book_id) {
            found = 1;
            for (int j = i; j < u->borrowed_count - 1; j++) {
                u->borrowed_books[j] = u->borrowed_books[j + 1];
            }
            u->borrowed_count--;
            //u->borrowed_books = realloc(u->borrowed_books, (u->borrowed_count + 1) * sizeof(int)); // cấp phát lại sẽ không cần thiết tuy giải phóng vùng nhớ nhưng sẽ tiêu tốn hiệu năng nếu gọi nhiều
            pbook[b_index].is_borrowed = false;
            printf("Book returned successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("User did not borrow this book.\n");
    }
}