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
node* createNode(int n1,int n2,int prio) {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL) {
        return NULL; // Memory allocation failed
    }
    newnode->id_of_borrower = n1;
    newnode->id_of_book = n2;

    newnode->priority = prio;
    newnode->next = NULL;
    return newnode;
}

// Function to create a new queue
queue* createQueue() {
    queue *q = (queue *)malloc(sizeof(queue));
    q->head = NULL; // Initialize head to NULL
    return q;
}


queue * enqueue_list(queue *q ,int id1,int id2,int prio)///WORKING GOOD
{//create a new node
  node *newnode = createNode(id1,id2, prio);//new node is a pointer to the new node
   if (newnode==NULL) return q ; //no memory space left ALLOCATION PROBLEM

 ///if the priority is the lowest i will enqueu at the end normally
 ///else im gonna search for the right position to insert it (before the pririty bigger)

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
void display_queue_list(queue *q)
{node *temp=q->head;
while (temp !=NULL)
{   printf("%d -->\t",temp->priority);
    temp=temp->next;
}
printf("NULL\n");
}
