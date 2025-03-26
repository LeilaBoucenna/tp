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
//ASS NBR OF COPY
void ass_copy_book(book *p,int n)
{if (p == NULL){
    printf("Erreur  c''est vide \n");
    return ;
}
   p->copy=n;
    return ;
}

//NEXT BOOK
book* next_book(book* book){
return book->next;
}

//PREVIOUS BOOK
book* prev_book(book* book){
return book->prev ;
}
 //ID BOOK
int  book_id(book *p)

{
    return p->id;
}

int  book_copy(book *p)

{
    return p->copy;
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

//QUEUE RELATED FUNCTIONS
// Function to create a new node
node* createNode(int n1,int n2,int prio,char titre[100]) {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL) {
        return NULL; // Memory allocation failed
    }
    newnode->id_of_borrower = n1;
    newnode->id_of_book = n2;

  strncpy(newnode->title_of_book,titre,sizeof(newnode->title_of_book) - 1); // Ensure buffer is not overflowed
  newnode->title_of_book[sizeof(newnode->title_of_book) -1] = '\0'; // Null-terminate

    newnode->priority = prio;
    newnode->next = NULL;
    return newnode;
}

// Function to create a new queue
queue* createQueue() {
    queue *q = (queue *)malloc(sizeof(queue));
       if (q == NULL) {
        return NULL; // Memory allocation failed
    }
    q->head = NULL; // Initialize head to NULL
    return q;
}


queue * enqueue_list(queue *q ,int id1,int id2,int prio,char title[100])///WORKING GOOD
{//create a new node
  node *newnode = createNode(id1,id2,prio,title);//new node is a pointer to the new node
   if (newnode==NULL) return q ; //no memory space left ALLOCATION PROBLEM

// If the queue is empty or the new node has higher priority than the head
 if (q->head==NULL || q->head->priority> prio)
 {newnode->next=q->head;
  q->head=newnode;
 }
else
{// Find the correct position to insert the new node
 node *current =q->head;
while (current->next != NULL && current->next->priority <= prio) {
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
    }return q;
}


int dequeue_list(queue *q )///WORKING GOOD
{//check to see if the queue is empty
    if (q->head==NULL) return 0;

    //save the head of the queue
    node * temp=q->head;

    //save the result we re going to return
    int result =temp->id_of_borrower;
    q->head=q->head->next;
    if (q->head==NULL)
    {q->tail=NULL;
    }
    free(temp);
    return(result);
}

// Function to free the queue
void freeQueue(queue *q) {
    node *current = q->head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
}

///lets display the queue
void display_personnal_loans(queue *q ,char name[100])
{if (q==NULL)
{printf("This member has NO active loan in this library.\n");

}
else
{node *temp=q->head;
printf("\t\t\t\t<== PERSONAL LOANS ==>\n\n");
printf("%-10s   %-20s  %-10s  %-40s  %-20s\n",  "Borrower id","Borrower Name","Book id","Book Title","Due date");

    while (temp != NULL)
    {
     printf("%-10d    %-20s  %-10d  %-40s  %-20d\n",temp->id_of_borrower,name,temp->id_of_book,temp->title_of_book,temp->priority);
      temp=temp->next;
    }


}
return;
}


void display_all_loans(queue *q ,char name[100])
{
node *temp=q->head;
    while (temp != NULL)
    {
     printf("%-10d    %-20s  %-10d  %-40s  %-20d\n",temp->id_of_borrower,name,temp->id_of_book,temp->title_of_book,temp->priority);
      temp=temp->next;
    }
return;
}
