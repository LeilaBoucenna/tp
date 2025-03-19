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


/// var globale///!!! a re checker

/////////////////////////
borrower *BORROW = NULL;
book *HEAD = NULL;
book *TAIL = NULL;

/// this one working and used model abstract
book *book_search(int n) /// search for the book by his id if founded returns it
                         /// @ else return 0(doesnt exist)
{
  if (HEAD == NULL)
    return NULL; // si la liste est vide donc il n existe pas
                 /// si oui liste n est pas vide

  book *temp = HEAD;
  while (temp != NULL) {
    if (ID_BOOK(temp) == n) {
      return temp;
    }

    temp = next_book(temp);
    ; /// si marche supprime
  }
  return NULL;
}

void delete_first() /// WORKING GOOD
{
  book *temp = HEAD;
  HEAD = next_book(HEAD);
  Ass_add_R(temp, NULL);
  Ass_add_L(HEAD, NULL);
  free(temp);
}

//////////////////
void delete_last_node() /// WORKING GOOD
{                       // TAIL->prev
  if (HEAD == NULL || TAIL == NULL) {
    printf("\n The list is empty\n");
    return;
  }

  if (HEAD == TAIL) // If there's only one node
  {
    free(HEAD);
    HEAD = NULL;
    TAIL = NULL; /// now the list is empty
  } else         /// the list is not empty and contains more than one book
  {
    book *temp = prev_book(TAIL);
    if (temp != NULL) {
      free(TAIL);
      TAIL = temp;
      TAIL->next = NULL;
    } else {
      // Handle potential error if temp is unexpectedly NULL
      fprintf(stderr, "Error: Unable to delete the last node.\n");
    }
  }
}
///!!!!!!!!!!!!do i delete it completely or deincrment the nmb of copy availble
///until =0 at this moment i delete completly
void delete_book(int n) /// WORKING GOOD
{
  bool found = false;
  book *temp = HEAD;
  ///book *p = NULL;
  if (temp == NULL) {
    // List is empty
    printf("The list is empty.\n");
    return;
  }
  /// est ce que je fais le cas quand la liste est vide
  while (temp != NULL && found == false) {
    if (temp->id == n) // je le supprime et je fais un lien entr prev et next si
                       // il est au milleiu sinon cas fin et cas debut
    {
      found = true;
      if (temp == HEAD) /// le livre a supprimer se trouve au debut de la liste
      {
        delete_first();
      } else {
        if (temp == TAIL) /// si le livre se trouve a la fin
        {
          delete_last_node();
        } else /// si le livre se trouve au millieu de la liste
        {
          book *before = temp->prev;
          book *after = temp->next;
          before->next = after;
          after->prev = before;
          free(temp);
        }
      }
      printf("Book with ID %d deleted.\n", n);
      printf("\n Press enter to come back to the menu");
      getch();
      return;
    }
    temp = temp->next;
  } /// si le livre n'existe pas je ne fais rien
  printf("Book with ID %d not found.\n", n);
  printf("\n Press enter to come back to the menu");
  getch();
}
/////////////////////////////

void affiche_book() {
  book *temp = HEAD;
  if (temp == NULL) {
    printf("THE BOOK LIST IS EMPTY");

  } else {
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-40s %-50s\n", "Book id", "Book Name", "Book author",
           "Number of copies available");

    while (temp != NULL) {
      printf("%-10d %-30s %-40s %-50d \n", temp->id, temp->title, temp->author,
             temp->copy);
      temp = temp->next;
    }
  }
}

/////////////////////////////
void addBookman(int id, const char *name, const char *author) {
  book *temp = (book *)malloc(sizeof(book));

  if (temp == NULL) {
    // Handle memory allocation failure
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  temp->id = id;
  temp->copy = 1;
  strncpy(temp->title, name,
          sizeof(temp->title) - 1); // Ensure buffer is not overflowed
  temp->title[sizeof(temp->title) - 1] = '\0'; // Null-terminate
  strncpy(temp->author, author, sizeof(temp->author) - 1);
  temp->author[sizeof(temp->author) - 1] = '\0'; // Null-terminate

  if (HEAD == NULL && TAIL == NULL) /// LIST EMPTY
  {
    HEAD = temp;
    TAIL = temp;
    TAIL->prev = NULL;
    HEAD->prev = NULL;
    HEAD->next = NULL;

  } else {
    temp->prev = TAIL;
    TAIL->next = temp;
    TAIL = temp;
    TAIL->next = NULL;
  }
}

void auto_add_book() /// this function fill the book list automaticly
{
  addBookman(1, "Internet of Things", "Eric Freeman");
  addBookman(2, "Parallel Programming", "Peter Pacheco");
  addBookman(3, "Web Development Fundamentals", "Jiawei Han");
  addBookman(4, "Data Mining", "David A. Patterson");
  addBookman(5, "Computer Graphics", "Nielsen Chuang");
  addBookman(6, "Quantum Computing", "Andrew S. Tanenbaum");
  addBookman(7, "Game Development", "Jake VanderPlas");
  addBookman(8, "Computer Architecture", "Jacob Eisenstein");
  addBookman(9, "Functional Programming", "Nielsen Chuang");
  addBookman(10, "Cybersecurity Principles", "Jacob Eisenstein");
  addBookman(11, "Game Development", "Jacob Eisenstein");
  addBookman(12, "Parallel Programming", "Kazem Sohraby");
  addBookman(13, "Wireless Sensor Networks", "Thomas Cormen");
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
  addBookman(50, "Blockchain Technology", "William Stallings");

  book *temp = HEAD;
  while (temp != NULL) {
    temp->copy = 1;
    temp = temp->next;
  }
}

//////////////////////////
void add_book() {
  /// first case if the book list is empty we add the first book

  book *temp = HEAD;
  book *p = NULL;

  // let us create individual node
  temp = (book *)malloc(sizeof(book));

  if (temp == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  printf("\nEnter book id: ");
  scanf("%d", &temp->id);
  int id = ID_BOOK(temp);

  printf("\nEnter book title: ");
  scanf("%s", &temp->title);

  printf("\nEnter book author: ");
  scanf("%s", &temp->author);

  temp->prev = NULL;
  temp->next = NULL;
  temp->copy = 1;
  /// c bon we created a cell
  if (HEAD == NULL ||
      TAIL ==
          NULL) /// first case if the book list is empty we add the first book
  {
    HEAD = temp; /// head ET TAIL  pointeront a la nouvelle cellule creer
    TAIL = temp;

  } else /// seconde case if the list is not empty
  {
    p = book_search(id);
    if (p != NULL) /// ie ce livre existe deja
    {              /// faux
      p->copy = p->copy + 1;
      temp = p;

    } else /// il nexister pas avant je cree une nouvelle cellule avec nbr copy
           /// =1
    { /// mais sa doit etre une sorted linked list por le moment elle ne sera
      /// pas organiser

      TAIL->next = temp;
      TAIL = temp;
      TAIL->prev = temp->prev;
    }
  }
  printf("\n THIS BOOK WAS ADDED SUCCESSFULLY");
  printf("\n Press enter to come back to the menu");
  getch();
  return;
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

book *trie_bubble_croissant(book *head) {
  
  if (head == NULL) {
    printf("the list is empty");
  } else {
    int i = length_list(head) - 1;

    for (int k = 0; k <= i; k++)

    {
      book *prev = head;
      book *temp = head->next;
      while (temp != NULL) {
        if ((prev->id) > (temp->id)) {
          int sauv;
          sauv = prev->id;
          prev->id = temp->id;
          temp->id = sauv;
        }
        prev = prev->next;
        temp = temp->next;
      }
    }
  }
  return head;
}

void book_list() {
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
  case 1: {
    HEAD = trie_bubble_croissant(HEAD);
    break;
  }
  /* case 2:
       {
      sort by title
       break;
       }*/
  }

  affiche_book();
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

list add_borr(list k,int IDs, const char* name){
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


int main() {
list lst ={NULL,NULL};
///both the head and the tail of the borrower list are initialized to NULL
  int menu;
  auto_add_book();
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
    printf("7-Loan list.\n");
    printf("7-Display statistics of the total number of books and borrowers, "
           "active loans, and overdue books.\n");
   printf("0-EXIT and delete all.\n\n");
    printf("Enter your choice:  ");

    scanf("%d", &menu);

    switch (menu) {
    case 1: {
      book_list();
      break;
    }
    case 2: {
      add_book(); /// we will add a book head and tail will get updated
      break;   /// will be changed the same way add borrower
    }
    case 3: {
      int nbr;
      printf("Enter the id of the book that you want to delete from the list");
      scanf("%d", &nbr);
      delete_book(nbr);
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
