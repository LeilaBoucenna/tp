#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include<conio.h>
#include <string.h>

typedef struct book{
int id;
int copy;
char title[100];
char author[100];
struct book *next;
struct book *prev;
}book;

typedef struct borrower{
int id;
char name[256];
struct borrower *next;
struct borrower *prev;
}borrower;

//assign Address
void Ass_add_R(book *p, book *Add);
void Ass_add_L(book *p, book *Add);
void Ass_id_book(book *book,int id );

int  book_id(book *p);
int  book_copy(book *p);
void ass_copy_book(book *p,int n);
void Ass_title_book(book *book, char *title );

//NEXT BOOK
book* next_book(book* book);
//PREVIOUS BOOK
book* prev_book(book* book);
//ASSIGN ID BORROWER
void ass_id_borr(borrower* borrow , int ID);
//ASSIGN NAME BORROWER
void ass_name_borr(borrower* borrow , char *nom);
//NEXT BORROWER
borrower* next_borrow(borrower* borrow);
//PREVIOUS BORROWER
borrower* prev_borrow(borrower* borrow);
int ID_BOOK(book *p);


