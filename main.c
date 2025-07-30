// ===============================
// File: main.c
// ===============================
#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "user.h"
#include "borrow.h"

int main() {
    int choice;
    book_init();
    //init_users();

    while (1) {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n2. Edit Book\n3. Delete Book\n4. Add User\n5. Edit User\n6. Delete User\n");
        printf("7. Borrow Book\n8. Return Book\n9. Search Books\n10. Display Books\n11. Display Users\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1: book_add(); break;
            case 2: book_edit(); break;
            case 3: book_delete(); break;
            //case 4: add_user(); break;
            //case 5: edit_user(); break;
            //case 6: delete_user(); break;
            //case 7: borrow_book(); break;
            //case 8: return_book(); break;
            case 9: book_search(); break;
            case 10: book_list(); break;
            //case 11: display_users(); break;
            case 0:
                book_free();
                //free_users();
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}