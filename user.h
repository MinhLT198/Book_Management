// ===============================
// File: user.h
// ===============================
#ifndef USER_H
#define USER_H

#define INITIAL_CAPACITY 10
#define MAX_NAME_LEN 100

typedef struct 
{
    int id;
    char *name;
    int *borrowed_books; // Store book IDs
    int borrowed_count;
}User;

void user_init();
void user_add();
void user_edit();
void user_delete();
void user_list();
void user_free();
int user_find_index(int id);

#endif