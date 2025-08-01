//=======================================================================
// File: devlinux/BT1/user.c
//=======================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

User *user = NULL;
int user_count = 0;
static int user_capacity = 0;
static int *user_del = NULL;
static int user_count_del = 0;
static int user_capacity_del = 0;

void user_init(){
    user_capacity_del = user_capacity = INITIAL_CAPACITY;
    user_del = (int *)malloc(user_capacity_del * sizeof(int));
    user = (User *)malloc(user_capacity * sizeof(User));
    if (!user) {
        fprintf(stderr, "Memory allocation failed for users.\n");
        exit(EXIT_FAILURE);
    }
}

static void resize_users() {
    user_capacity *= 2;
    user = (User *)realloc(user, user_capacity * sizeof(User));
}
static void resize_users_del() {
    user_capacity_del *= 2;
    user_del = (int *)realloc(user_del, user_capacity_del * sizeof(int));
}

void user_add() {
    if (user_count == user_capacity) resize_users();

    User *u = &user[user_count++];
    if (user_count_del != 0)
        u->id = user_del[--user_count_del];
    else
        u->id = user_count; // Simple ID assignment
    u->borrowed_count = 0;
    u->borrowed_books = NULL;
    char buffer[MAX_NAME_LEN];
    printf("Enter user name: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    u->name = strdup(buffer);

    printf("User added with ID: %d\n", u->id);
}
void user_edit() {
    int id;
    printf("Enter user ID to edit: ");
    scanf("%d", &id);
    getchar();

    int idx = user_find_index(id);
    if (idx == -1) {
        printf("User not found.\n");
        return;
    }

    char buffer[MAX_NAME_LEN];
    printf("Enter new name: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    free(user[idx].name);
    user[idx].name = strdup(buffer);

    printf("User updated.\n");
}
void user_delete() {
    int id;
    printf("Enter user ID to delete: ");
    scanf("%d", &id);
    getchar();

    int idx = user_find_index(id);
    if (idx == -1) {
        printf("User not found.\n");
        return;
    }

    if (user_count_del == user_capacity_del) resize_users_del();
    user_del[user_count_del++] = id;
    free(user[idx].name);
    user[idx] = user[--user_count]; // Replace with last user
    printf("User deleted.\n");
}
void user_list() {
    if (user_count == 0) {
        printf("No users available.\n");
        return;
    }
    for (int i = 0; i < user_count; ++i) {
        printf("ID: %d, Name: %s, Borrowed Count: %d\n", user[i].id, user[i].name, user[i].borrowed_count);
    }
}
void user_free(){
    for (int i = 0; i < user_count; ++i) {
        user[i].id = 0;
        free(user[i].name);
        free(user[i].borrowed_books);
        user[i].borrowed_count = 0;
    }
    user_count = 0;
    free(user);
}
int user_find_index(int id){
    for (int i = 0; i < user_count; ++i) {
        if (user[i].id == id) {
            return i;
        }
    }
    return -1;
}
