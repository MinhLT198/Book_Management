// ===============================
// File: borrow.h
// ===============================
#ifndef BORROW_H
#define BORROW_H

extern Book *pbook;
extern User *user;
extern int book_count;
extern int user_count;

void book_borrow();
void book_return();

#endif