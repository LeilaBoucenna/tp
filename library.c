#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include<conio.h>
#include <string.h>
#include "library.h"
///MAchine abstraite
//assign Address right
void Ass_add_R(book *p, book *Add){
if (p == NULL){
    printf("Erreur  c''est vide \n");
    return ;
}
p->next=Add;
return;
}

//assign address left
void Ass_add_L(book *p, book *Add){
if (p == NULL){
    printf("Erreur  c''est vide \n");
    return ;
}
p->prev=Add;
return;
}


//assign ID
void Ass_id_book(book *book,int id ){
if (book == NULL){
    printf("Erreur  c''est vide \n");
    return ;
}
book->id=id;

}

//Ass TITLE


void Ass_title_book(book *book, char *title ){
if (book == NULL){
    printf("Erreur  c''est vide \n");
    return ;
}
strcpy(book->title , title);

}

//NEXT BOOK
book* next_book(book* book){
return book->next;
}

//PREVIOUS BOOK
book* prev_book(book* book){
return book->prev ;
}






//ASSIGN ID BORROWER
void ass_id_borr(borrower* borrow , int ID){

borrow->id=ID;
}

//ASSIGN NAME BORROWER

void ass_name_borr(borrower* borrow , char *nom){

strcpy(borrow->name, nom);
}
//NEXT BORROWER
borrower* next_borrow(borrower* borrow){
return borrow->next;
}

//PREVIOUS BORROWER
borrower* prev_borrow(borrower* borrow){
return borrow->prev ;
}
int ID_BOOK(book *p)
{int k=p->id;
   return k;
}
