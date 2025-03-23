#include <conio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*typedef struct book{
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

*/



typedef struct list{
  borrower *head_b;
  borrower *tail_b;
        }list;


typedef struct list_book
{
    book* HEAD;
    book* TAIL;
}list_book;

/// var globale///!!! a re checker

/////////////////////////
/*borrower *BORROW = NULL;
book *HEAD = NULL;
book *TAIL = NULL;*/

/// this one working and used model abstract
book *book_search(list_book k,int n) /// search for the book by his id if founded returns it
                         /// @ else return 0(doesnt exist)
{
  if (k.HEAD == NULL)
    return NULL; // si la liste est vide donc il n existe pas
                 /// si oui liste n est pas vide

  book *temp = k.HEAD;
  while (temp != NULL) {
    if (ID_BOOK(temp) == n) {
      return temp;
    }

    temp = next_book(temp);
    ; /// si marche supprime
  }
  return NULL;
}

list_book delete_first(list_book k) /// WORKING GOOD
{
  book *temp = k.HEAD;
  k.HEAD = next_book(k.HEAD);
  Ass_add_R(temp, NULL);
  Ass_add_L(k.HEAD, NULL);
  free(temp);
}

//////////////////
list_book delete_last_node(list_book k) /// WORKING GOOD
{                       // TAIL->prev
  if (k.HEAD == NULL || k.TAIL == NULL) {
    printf("\n The list is empty\n");
    return k;
  }

  if (k.HEAD == k.TAIL) // If there's only one node
  {
    free(k.HEAD);
    k.HEAD=NULL;
    k.TAIL=NULL; /// now the list is empty
  } else         /// the list is not empty and contains more than one book
  {
    book *temp = prev_book(k.TAIL);
    if (temp != NULL) {
      free(k.TAIL);
      k.TAIL=temp;
      Ass_add_R(k.TAIL,NULL);
    } else {
      // Handle potential error if temp is unexpectedly NULL
      fprintf(stderr, "Error: Unable to delete the last node.\n");
    }
  }
  return k;
}
///!!!!!!!!!!!!do i delete it completely or deincrment the nmb of copy availble
///until =0 at this moment i delete completly
list_book delete_book(list_book k,int n) /// WORKING GOOD
{
  bool found = false;
  book *temp = k.HEAD;

  if (temp == NULL) {
    // List is empty
    printf("The list is empty.\n");
    return k;
  }
  /// est ce que je fais le cas quand la liste est vide
  while (temp != NULL && found == false) {
    if (book_id(temp) == n) // je le supprime et je fais un lien entr prev et next si
                       // il est au milleiu sinon cas fin et cas debut
    {
      found = true;
      if (temp == k.HEAD) /// le livre a supprimer se trouve au debut de la liste
      {
       k=delete_first(k);
      } else {
        if (temp == k.TAIL) /// si le livre se trouve a la fin
        {
         k=delete_last_node(k);
        } else /// si le livre se trouve au millieu de la liste
        {
          book *before = temp->prev;
          book *after = temp->next;

         Ass_add_R(before,after);
         Ass_add_L(after,before);

          free(temp);
        }
      }
      printf("Book with ID %d deleted.\n", n);
      printf("\n Press enter to come back to the menu");
      getch();
      return k;
    }
   temp=next_book(temp);
  } /// si le livre n'existe pas je ne fais rien
  printf("Book with ID %d not found.\n", n);
  printf("\n Press enter to come back to the menu");
  getch();
  return k;
}
/////////////////////////////

void affiche_book(list_book k) {
  book *temp = k.HEAD;///il me dit que k.head est NULL
  if (temp == NULL) {
    printf("THE BOOK LIST IS EMPTY");

  } else {
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-40s %-50s\n", "Book id", "Book Name", "Book author",
           "Number of copies available");

    while (temp != NULL)
    {
      printf("%-10d %-30s %-40s %-50d \n",book_id(temp),temp->title,temp->author,book_copy(temp));
      temp=next_book(temp);
    }
  }
}

list_book addBookman(list_book k,int id, const char *name, const char *author) {
  book *temp = (book *)malloc(sizeof(book));

  if (temp == NULL) {
    // Handle memory allocation failure
    fprintf(stderr, "Memory allocation failed\n");
    return k;
  }
  Ass_id_book(temp,id);
  ass_copy_book(temp,1);
  strncpy(temp->title, name,sizeof(temp->title) - 1); // Ensure buffer is not overflowed
  temp->title[sizeof(temp->title) - 1] = '\0'; // Null-terminate
  strncpy(temp->author, author, sizeof(temp->author) - 1);
  temp->author[sizeof(temp->author) - 1] = '\0'; // Null-terminate

  if (k.HEAD == NULL && k.TAIL == NULL) /// LIST EMPTY
  {
    k.HEAD=temp;
    k.TAIL=temp;
    Ass_add_L(k.TAIL,NULL);
    Ass_add_L(k.HEAD,NULL);
    Ass_add_R(k.HEAD,NULL);

  } else {
    Ass_add_L(temp,k.TAIL);
    Ass_add_R(k.TAIL,temp);
    k.TAIL=temp;
    Ass_add_R(k.TAIL,NULL);  }
    return k;
}

list_book auto_add_book(list_book k) /// this function fill the book list automaticly
{ k=addBookman(k,9, "Functional Programming", "Nielsen Chuang");
 k=addBookman(k,10, "Cybersecurity Principles", "Jacob Eisenstein");
 k=addBookman(k,11, "Game Development", "Jacob Eisenstein");
 k=addBookman(k,12, "Parallel Programming", "Kazem Sohraby");
 k=addBookman(k,1, "Internet of Things", "Eric Freeman");
 k=addBookman(k,2, "Parallel Programming", "Peter Pacheco");
 k=addBookman(k,3, "Web Development Fundamentals", "Jiawei Han");
 k=addBookman(k,4, "Data Mining", "David A. Patterson");
 k=addBookman(k,5, "Computer Graphics", "Nielsen Chuang");
 k=addBookman(k,6, "Quantum Computing", "Andrew S. Tanenbaum");
 k=addBookman(k,7, "Game Development", "Jake VanderPlas");
 k=addBookman(k,8, "Computer Architecture", "Jacob Eisenstein");

 /* addBookman(13, "Wireless Sensor Networks", "Thomas Cormen");
  addBookman(14, "Deep Learning", "Peter Pacheco");
  addBookman(15, "Database Management Systems", "Richard Szeliski");
  addBookman(16, "Programming with Java", "Ben Fry");
  addBookman(17, "Introduction to Algorithms", "Dennis Ritchie");
  addBookman(18, "Operating System Concepts", "Tony Parisi");
  addBookman(19, "The C Programming Language", "Jiawei Han");
  addBookman(20, "Computer Graphics", "Eric Freeman");
  addBookman(21, "Object-Oriented Programming", "Sutton & Barto");
  addBookman(22, "Data Visualization", "Andrew S. Tanenbaum");
  addBookman(23, "Cyber-Physical Systems", "Ian Goodfellow");
  addBookman(24, "Data Mining", "Mahadev Satyanarayanan");
  addBookman(25, "Theory of Computation", "Jake VanderPlas");
  addBookman(26, "Database Management Systems", "Jon Duckett");
  addBookman(27, "Embedded Systems", "John F. Hughes");
  addBookman(28, "Internet of Things", "Alan V. Oppenheim");
  addBookman(29, "Quantum Computing", "Johnathan Harbour");
  addBookman(30, "Computer Graphics", "Richard Szeliski");
  addBookman(31, "Web Development Fundamentals", "Peter Pacheco");
  addBookman(32, "Cybersecurity Principles", "Alan Dix");
  addBookman(33, "Data Structures in C", "Raghu Ramakrishnan");
  addBookman(34, "Software Project Management", "Steve Aukstakalnis");
  addBookman(35, "Neural Networks", "Jacob Eisenstein");
  addBookman(36, "Human-Computer Interaction", "Rajkumar Buyya");
  addBookman(37, "Functional Programming", "Simon Haykin");
  addBookman(38, "Python for Data Science", "Steve Aukstakalnis");
  addBookman(39, "Python for Data Science", "Andrew S. Tanenbaum");
  addBookman(40, "Software Testing", "Richard Szeliski");
  addBookman(41, "The C Programming Language", "Herbert Schildt");
  addBookman(42, "Database Management Systems", "Alan Dix");
  addBookman(43, "Bioinformatics", "Sutton & Barto");
  addBookman(44, "Data Structures in C", "Christopher Bishop");
  addBookman(45, "Software Testing", "Arvind Narayanan");
  addBookman(46, "Computer Vision", "Adrian McEwen");
  addBookman(47, "Wireless Sensor Networks", "Rajkumar Buyya");
  addBookman(48, "Embedded Systems", "Nielsen Chuang");
  addBookman(49, "Cloud Computing", "Rajkumar Buyya");
  addBookman(50, "Blockchain Technology", "William Stallings");*/

  book *temp = k.HEAD;
  while (temp != NULL) {
   ass_copy_book(temp,1);
   temp=next_book(temp);
  }
 return k;
}

//////////////////////////
list_book add_book(list_book k) { ///on rajoute des livre a la liste et en meme temp en l organise par ordre d id croissant
  /// first case if the book list is empty we add the first book

  book *temp = k.HEAD;
  book *current = NULL;

  // let us create individual node
  temp = (book *)malloc(sizeof(book));

  if (temp == NULL) {
    printf("Memory allocation failed\n");
    return k;
  }

  printf("\nEnter book id: ");
  scanf("%d", &temp->id);
  int id =ID_BOOK(temp);

  printf("\nEnter book title: ");
  scanf("%s", &temp->title);

  printf("\nEnter book author: ");
  scanf("%s", &temp->author);
  temp->prev=NULL;
  temp->next=NULL;
  temp->copy = 1;
  /// c bon we created a cell
  if (k.HEAD == NULL /*|| k.TAIL ==NULL*/) /// first case if the book list is empty we add the first book
  {
    k.HEAD=temp; /// head ET TAIL  pointeront a la nouvelle cellule creer
    k.TAIL=temp;

  }
   else /// seconde case if the list is not empty
  {
book *current = book_search(k,id);
    if (current != NULL) /// ie ce livre existe deja
    {
      current->copy = current->copy + 1;
      free(temp);
    }
     else ///je traverse la liste pour rajouter le livre au bon endroit
    {book *current=k.HEAD;
    while ((ID_BOOK(current)<id) && current->next!=NULL )
    {
      current=next_book(current) ;///je traverse la liste
    }
///change

    if (current==k.TAIL)///l ID rajouter est le plus grand donc il sera forcement ajouter a la fin
    {
    k.TAIL->next=temp;///this part not working proprely
    temp->prev=k.TAIL;
    k.TAIL=temp;
    }
    else
    {
        if(current==k.HEAD) ///si l ID est le plus petit il sera ajouter au debut
    {
     temp->next=k.HEAD;     ///cette partie marche
     k.HEAD->prev=temp;
     k.HEAD=temp;

    }
    else/// si l id sera rajoutr au millieu
    {
    book *previous=current->prev;

     previous->next=temp;
     temp->next=current;
     temp->prev=previous;
     current->prev=temp;
    }
    }

    }
  }
  printf("\n THIS BOOK WAS ADDED SUCCESSFULLY\n");
  printf("\n Press enter to come back to the menu");
  getch();
  return k;
}

int length_list(book *head) {
      int cpt = 0;
  book *temp = head;
  while (temp != NULL) {
    cpt = cpt + 1;
    temp = temp->next;
  }
  return cpt;
}

void display_book(list_book h) {///cette fonction devient useless
  printf("if you want the list of book to be sorted by :\n");
  printf("*ID    (Press 1)\n");
  printf("*Title     (Press 2)\n");
  int order;
  scanf("%d", &order);
  while (order != 1 && order != 2) {
    printf("Invalid Choice...\n\n");
    printf("Press 1 for ID or 2 for Title: ");
    scanf("%d", &order);
  }
  switch (order) {
  case 1: {affiche_book(h);
  break;
  }
  /* case 2:
       {
      sort by title
       break;
       }*/
  }


  printf("\n Press enter to come back to the menu");
  getch();
}

borrower* search_borr(borrower* head,int ID){

    borrower* current= head;
    while(current !=NULL){
        if (current->id == ID){
            return current;
            }
        current= current->next;

    }
    return NULL;

    }

list add_borr(list k,int IDs, char name[50]){  ///to change add name then family name
        if (search_borr(k.head_b,IDs)!=NULL){
            printf("l'etudiant existe deja !\n");
            printf("Press enter to comeback to the menu");
            getch();
        return k;
        }


        borrower* newOne= (borrower*)malloc(sizeof(borrower));///create a new cell
        if (newOne == NULL) {
            printf("Memory allocation failed.\n");
             printf("Press enter to comeback to the menu");
            getch();
            return k; // Return the unchanged list
        }
       else
       {
        newOne->id=IDs;
        strcpy(newOne->name,name);
        newOne->next=NULL;///initialize prev and next to NULL
        newOne->prev=NULL;

        if(k.head_b==NULL ){
           k.head_b=newOne;
            k.tail_b=newOne;
        }
        else{
            newOne->prev=k.tail_b;

            (k.tail_b)->next=newOne;
            (k.tail_b)=newOne;
            k.tail_b->next=NULL;
        }
       }
       return k;
        }

list auto_add_borr(list k)
{k=add_borr(k,47,"leila");
k=add_borr(k,45,"Amina");
k=add_borr(k,741,"ROSE");
k=add_borr(k,125,"Jennie");
k=add_borr(k,412,"HIBA");
 return k;
}

void display_borrower(list k)
{
    borrower* current = k.head_b;
     if (current == NULL) {
    printf("THE BOOK LIST IS EMPTY");
   return;
  }
  else
    {
    printf("<== Borrower List ==>\n\n");
    printf("%-10s %-40s\n", "Book id", "Book Name");

        while (current != NULL) {
        printf("%-10d  %-40s \n", current->id, current->name);
        current = current->next;
}
}
printf("\nPress ENTER to comeback to the menu.");
getch();
}
///leila

list delete_borr_id(list k, int ID){
    bool found=false;
if (k.head_b==NULL){
  printf("The list is empty.\n");
    return k;
}

borrower* temp= k.head_b;
while (temp != NULL && found == false) {
if (temp->id == ID) // je le supprime et je fais un lien entr prev et next si
                       // il est au milleiu sinon cas fin et cas debut
    {
      found = true;
      if (temp == k.head_b) /// le livre a supprimer se trouve au debut de la liste
      {
        /// WORKING GOOD

      borrower *temp = k.head_b;
      k.head_b = k.head_b->next;
      temp->next= NULL;
      k.head_b->prev=NULL;
      free(temp);

      } else {
        if (temp == k.tail_b) ///si le borrower se trouve a la fin
        {
  if (k.head_b == k.tail_b) // If there's only one node
  {free(k.head_b);
   k.head_b= NULL;
   k.tail_b= NULL; /// now the list is empty
  }
  else         /// the list is not empty and contains more than one  borrower
  {
    borrower *temp = k.tail_b->prev;
    if (temp != NULL) {
      free(k.tail_b);
      k.tail_b = temp;
      k.tail_b->next = NULL;
    } else {
      // Handle potential error if temp is unexpectedly NULL
      fprintf(stderr, "Error: Unable to delete the last node.\n");
    }
    }
        } else /// si le  borrower se trouve au millieu de la liste
        {
          borrower *before = temp->prev;
          borrower *after = temp->next;
          before->next = after;
          after->prev = before;
          free(temp);
        }
      }
      printf("Borrower with ID %d deleted.\n", ID);
      printf("\n Press enter to come back to the menu");
      getch();
      return k;
    }
    temp = temp->next;
  } /// si le borrower n'existe pas je ne fais rien
  printf("Borrower with ID %d not found.\n", ID);
  printf("\n Press enter to come back to the menu");
  getch();
}




int main() {
list lst ={NULL,NULL};
list_book BOOK={NULL,NULL};
///both the head and the tail of the borrower list are initialized to NULL
  int menu;
//BOOK=auto_add_book(BOOK);
lst=auto_add_borr(lst);
  do {
    system("cls");
    printf("Library management system\n\n");
    printf("1-Display book list.\n");
    printf("2-Add book or Return a book.\n"); /// add and return are not the
                                              /// same,in return i need to ask
                                              /// for the student id and maybe
                                              /// other stuff
    printf("3-Remove a book or Take a book.\n"); /// but in add i need nothing

    printf("4-Display borrower list.\n");
    printf("5-Add a borrower.\n");
    /// search book dont forget it
    printf("6-Delete a borrower.\n");
    printf("9-Loan list.\n");
    printf("8-Display statistics of the total number of books and borrowers, "
           "active loans, and overdue books.\n");
   printf("0-EXIT and delete all.\n\n");
    printf("Enter your choice:  ");

    scanf("%d", &menu);

    switch (menu) {
    case 1: {
     display_book(BOOK);
      break;
    }
    case 2: {
     BOOK=add_book(BOOK); /// we will add a book head and tail will get updated
      break;   /// will be changed the same way add borrower
    }
    case 3: {
      int nbr;
      printf("Enter the id of the book that you want to delete from the list");
      scanf("%d", &nbr);
      BOOK=delete_book(BOOK,nbr);
      break;
    }
    case 4:{
            display_borrower(lst);
            break;
           }
   case 5:
        {
       printf("Enter the full name of the new borrower : ");
       char nom[100];
       scanf("%s",&nom);
      printf("\nEnter ID : ");
      int n;
      scanf("%d",&n);
      lst=add_borr(lst,n,nom);
        break;
        }
   case 6 :
    {printf("Enter the ID of the borrower that you want to delete from the list  :  ");
     int n;
     scanf("%d",&n);
     lst=delete_borr_id(lst,n);
     break;
    }

    case 0: {
      exit(0);///Happy ending
    }

    default: {
      printf("Invalid Choice...\n\n");
      printf("\n\t\t\t\t      Press any key to try again: ");
      getch();
    }
    }

  } while (menu != 10);
  return 0;
}
