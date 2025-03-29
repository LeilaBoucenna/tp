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
queue *individual;
}borrower;

*/



typedef struct list{
  borrower *head_b;
  borrower *tail_b;
        }list;


typedef struct list_book
{   book* HEAD;
    book* TAIL;
}list_book;

typedef int arr[4]; //this an array the first case it s for nbr of active loan
                     // second one overdue book
                     //third one total nmr of book
                     //fourth total nbr of borrower




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
    if (k.HEAD == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return k; // Nothing to delete if the list is empty
    }

    book *temp = k.HEAD; // Store the current head node
    k.HEAD = next_book(k.HEAD); // Move head pointer to the next node

    // Ensure the new head is properly linked
    if (k.HEAD != NULL) {
        Ass_add_L(k.HEAD, NULL); // Link the left pointer if necessary
    }

    Ass_add_R(temp, NULL); // Unlink the current head
    free(temp); // Deallocate memory for the removed node
return k;
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
list_book delete_book(list_book k,int n,arr tab) /// WORKING GOOD
{
  book *temp =book_search(k,n);
  if(temp!=NULL) //this book exist in the library
  {if (temp->copy > 1) // If there are multiple copies
    {
        temp->copy--; // Decrement the copy count
    }
    else// If this is the last copy
    {if (temp == k.HEAD) // le livre a supprimer se trouve au debut de la liste
      {
       k=delete_first(k);
      }
      else
        {
        if (temp == k.TAIL) // si le livre se trouve a la fin
        {
         k=delete_last_node(k);
        } else // si le livre se trouve au millieu de la liste
        {
          book *before = temp->prev;
          book *after = temp->next;

         Ass_add_R(before,after);
         Ass_add_L(after,before);

          free(temp);
        }
        }
       }//book deleted succesfully
tab[2]--;
return k;
    }
  else     //the book  doesnt exist in the library
    {
    printf("Book with ID %d not found.\n", n);
    printf("\n Press enter to come back to the menu");
    getch();
return k;
  }

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

list_book addBookman(list_book k,int id, const char *name, const char *author,arr tab) {
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
      printf("\nThis book already exists\n");
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
  tab[2]++;
    return k;
}

list_book auto_add_book(list_book k,arr tab) /// this function fill the book list automaticly
{FILE *fp=fopen("books_data.txt","r");
  // Character buffer that stores the read character
  // till the next iteration
char str[100];
char command[50];
char title[50];
char writer[50];
int id;
   if (NULL == fp) {
        printf("file can't be opened \n");
          return k ;
    }
   while (fgets(str, 100,fp) != NULL) {
        printf("%s" ,str);
   if (sscanf(str, "%s %d \"%[^\"]\" \"%[^\"]\"", command, &id, title, writer) == 4) {
        k=addBookman(k,id,title,writer,tab);

    }
   }
 fclose(fp);
 return k;
}



//////////////////////////
list_book add_book(list_book k,arr tab) { ///on rajoute des livre a la liste et en meme temp en l organise par ordre d id croissant
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
  k=addBookman(k,ID_BOOK(temp),temp->title,temp->author,tab);
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
///UPDATE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
list_book add_book(list_book k,arr tab) { ///on rajoute des livre a la liste et en meme temp en l organise par ordre d id croissant
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
  k=addBookman(k,ID_BOOK(temp),temp->title,temp->author,tab);
  printf("\n THIS BOOK WAS ADDED SUCCESSFULLY\n");
  printf("\n Press enter to come back to the menu");
  getch();
  return k;
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
list addBorrman(list k,int IDs, char *name,int tab[]){  ///to change add name then family name

    borrower* newOne= (borrower*)malloc(sizeof(borrower));///create a new cell
        if (newOne == NULL) {
            printf("Memory allocation failed.\n");
             printf("Press enter to comeback to the menu");

            getch();
            return k; // Return the unchanged list
        }
        if (search_borr(k.head_b,IDs)!=NULL){
            printf("This ID is already taken by someone else !\n");
            printf("Press enter to comeback to the menu");
            getch();
        return k;
        }


       else
       {
           ass_id_borr(newOne,IDs);
           ass_name_borr(newOne,name);
           newOne->prev=NULL;
           newOne->next=NULL;
       }

        if(k.head_b==NULL )//borrowers list is empty
            {
           k.head_b=newOne;
            k.tail_b=newOne;
        }
        else{
        borrower *current = k.head_b;
        while ((borrower_id(current)< IDs) && current->next!=NULL){
            current=next_borrow(current);
        }

        if(current==k.tail_b){
            k.tail_b->next=newOne;
            newOne->prev=k.tail_b;
            k.tail_b=newOne;

        }
        else{
            if(current==k.head_b){
            newOne->next=k.head_b;
            k.head_b->prev=newOne;
            k.head_b=newOne;

            }
         else{
            borrower* previous=current->prev;
            previous->next=newOne;
            newOne->next=current;
            newOne->prev=previous;
            current->prev=newOne;


         }

        }

        }


tab[3]++;
return k;

        }




list add_borr(list k,int tab[]) {
  /// first case if the borrower list is empty we add the first borrower

  borrower *temp = k.head_b;
  borrower *current = NULL;

  // let us create individual node
  temp = (borrower *)malloc(sizeof(borrower));

  if (temp == NULL) {
    printf("Memory allocation failed\n");
    return k;
  }

  printf("\nEnter borrower id: ");
  scanf("%d", &temp->id);
  int id ;
  id = ID_Borr(temp);



  printf("\nEnter borrower Name_LastName: ");
  scanf("%s", &temp->name);
list q =k;
  q=addBorrman(q,ID_Borr(temp),temp->name,tab);

  printf("\n THIS Borrower WAS ADDED SUCCESSFULLY\n");
  printf("\n Press enter to come back to the menu");
  getch();
  return q;
}



/*list auto_add_borr(list k,arr tab)
{k=add_borr(k,47,"leila",tab);
k=add_borr(k,45,"Amina",tab);
k=add_borr(k,741,"ROSE",tab);
k=add_borr(k,125,"Jennie",tab);
k=add_borr(k,412,"HIBA",tab);
 return k;
}*/

void display_borrower(list k)
{
    borrower* current = k.head_b;
     if (current == NULL) {
    printf("THE BORROWER LIST IS EMPTY");
   return;
  }
  else
    {
    printf("<== Borrower List ==>\n\n");
    printf("%-10s %-40s\n", "Borrower id", "Borrower Name");

        while (current != NULL) {
        printf("%-10d  %-40s \n", current->id, current->name);
        current = current->next;
}
}
printf("\nPress ENTER to comeback to the menu.");
getch();
}

list delete_borr_id(list k, int ID,arr tab){
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
      tab[3]--;
      return k;
    }
    temp = temp->next;
  } /// si le borrower n'existe pas je ne fais rien
  printf("Borrower with ID %d not found.\n", ID);
  printf("\n Press enter to come back to the menu");
  getch();
}


list_book issue_book(list_book k,list s,int member,int idbook,int date,arr tab)
{borrower *head=s.head_b;
 borrower* temp=NULL;
 book *p=NULL;
temp=search_borr(head,member);

if (temp!=NULL)//this person is  a menber and
{
 p=book_search(k,idbook);
 if (p!=NULL)
    {
   if (temp->individual==NULL)//no loans for this person or borrower
   {
       temp->individual=createQueue();
   }
   temp->individual=enqueue_list(temp->individual,member,idbook,date,p->title,p->author);
   k=delete_book(k,idbook,tab);
   tab[0]++;

   }
   }

  return k;
}





list_book issue_book_menu(list_book k,list s,queue *q,arr tab){
int due_date;
borrower *head=s.head_b;
borrower* temp=NULL;
book *p=NULL;
printf("In order to issue a book you need to be a member of the library.\n");
printf("Please enter your ID\n");
int n;
int n1;
scanf("%d",&n);

temp=search_borr(head,n);
if (temp==NULL)
{
    printf("You are not a member please register first in this library.");
    printf("\nPress ENTER to comeback to the menu.");
    getch();
    return k;
}
else
{printf("Welcome Back %s \n",temp->name);
 printf("Enter the ID of the book that you want to take :");   ///add also search by title
 scanf("%d",&n1);
 p=book_search(k,n1);
 if (p==NULL)
 {
    printf("This book is not available in this library.");
    printf("\nPress ENTER to comeback to the menu.");
    getch();
    return k;
 }
 else
 {  printf("The book : %s written by %s is available!!",p->title,p->author);
    printf("\n Please choose a date to return the book (write it under this format YYYYMMDD)");
    scanf("%d",&due_date);
    k=issue_book(k,s,n,n1,due_date,tab);
    printf("BOOK ISSUE SUCCESSFULLY");
    printf("\nPress ENTER to comeback to the menu.");
    getch();
    return k;
}
}
}
void display_loans(list s){
printf("1-Display personnal loans .\n");
printf("2-Display all active loans in the library.\n ");
printf("Please choose number 1 or 2 any other number will make you come back to the menu :");
int choice;
scanf("%d",&choice);
 switch (choice) {
case 1:
    { printf("Enter ID member : ");
      scanf("%d",&choice);
        borrower *head=s.head_b;
      borrower* temp=temp=search_borr(head,choice);
      display_personnal_loans(temp->individual,temp->name);
      break;
    }
case 2:
    {borrower *temp=s.head_b;//je dois treverser la liste
     printf("\t\t\t\t<==  TOTAL LOANS ==>\n\n");
     printf("%-10s   %-20s  %-10s  %-40s  %-20s\n",  "Borrower id","Borrower Name","Book id","Book Title","Due date");
    while(temp!=NULL)
     {if (temp->individual!=NULL)//this is member has a loan
     {
         display_all_loans(temp->individual,temp->name);
     }

      temp=next_borrow(temp);
     }
        break;
    }
 }
printf("\nPress ENTER to comeback to the menu.");
getch();
}
list_book manually_delete_book(list_book k,arr tab){
      int nbr;
      printf("Enter the id of the book that you want to delete from the list");
      scanf("%d", &nbr);
      k=delete_book(k,nbr,tab);
      return k;
}
list manually_add_member(list s,arr tab){
      printf("Enter the full name of the new borrower : ");
       char nom[100];
       scanf("%s",&nom);
      printf("Enter ID : ");
      int n;
      scanf("%d",&n);
      s=add_borr(s,n,nom,tab);
      printf("\n New member added successfully\n");
      printf("\nPress ENTER to comeback to the menu.");
      getch();
      return s;

};
list manually_delete_member(list s,arr tab){
printf("Enter the ID of the borrower that you want to delete from the list  :  ");
     int n;
     scanf("%d",&n);
     s=delete_borr_id(s,n,tab);
     return s;
}


list_book return_book_menu(list_book k,list s,arr tab){
borrower *head=s.head_b;
borrower* temp=NULL;
book *p=NULL;
printf("In order to return a book you need to be a member of the library.\n");
printf("Please enter your ID\n");
int n;
scanf("%d",&n);
temp=search_borr(head,n);
if (temp==NULL)
{
printf("You are not a member you cannot return a book\n");

} //i ask him to enter todays date i compare then i know if this book is overduee if yes i incremente
else
{printf("Welcome Back %s \n",temp->name);//we remove the first loan //et je desincrement le active loan
                                       //une case d un tableau
node *q=temp->individual->head;
 if (temp->individual==NULL){
 printf("Dear member you have no loan in this library.\n");
 }
 else{
    printf("Enter Today's date(in this FORMAT YYYYMMDD): ") ;
 int return_date;
 scanf("%d",&return_date);
 if (return_date>q->priority)//this book is over due
 {
   printf("This book is overdue you will have to pay for your delay!!\n  ");
   tab[1]++;  //increment the value of over due book
 }
 printf("The book :%s is returned successfully.\n",q->title_of_book);
 k=addBookman(k,q->id_of_book,q->title_of_book,q->writer,tab);
 tab[0]--;
 temp->individual=dequeue_list(temp->individual);
}
 }

printf("Press ENTER to comeback to the menu.");
getch();
return k;
}
void Textecolor(int ForgC){
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // Mask out all but the background attribute,
        //and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}


void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void welcome()
{
    int k;
    system("cls");
    Textecolor(5);
    printf("\t\t\t\t          R%cpublique Alg%crienne D%cmocratique et Populaire           \n", 130, 130, 130);
    printf("\t\t\t\tMinist%cre de l'Enseignement Sup%crieur et de la Recherche Scientifique\n\n\n", 130, 130);
    printf("\t\t\t\t     _______________________________________________________\n");
    printf("\t\t\t\t    |        _______     _______     _                      |\n");
    printf("\t\t\t\t    |       |  _____|   |  _____|   | |  %ccole nationale    |\n", 130);
    printf("\t\t\t\t    |       | |_____    | |_____    | |                     |\n");
    printf("\t\t\t\t    |       |  _____|   |_____  |   | |  sup%crieure         |\n", 130);
    printf("\t\t\t\t    |       | |_____     _____| |   | |                     |\n");
    printf("\t\t\t\t    |       |_______|   |_______|   |_|  d'informatique     |\n");
    printf("\t\t\t\t    |_______________________________________________________|\n\n\n");
    Textecolor(3);
    printf("\t\t\t\t\tCPI - 1%cre Ann%ce - Ann%ce Universitaire 2024/2025 \n\n\n", 138, 130, 130);
    printf("\t\t\t\t ___________________________________________________________________\n");
    printf("\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t| REALISE PAR : Boucenna Leila   &       Bouarab Hiba               |\n");
    printf("\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t|           SECTION : D          GROUPE: 14                         |\n");
    printf("\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t|           TP: Library Management                                  |\n");
    printf("\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t|___________________________________________________________________|\n\n\n");
    Sleep(200);
    Sleep(200);
    Textecolor(5);
    printf("\n");
    printf("\t\t\t\t                             PLease                                         \n");
    printf("\t\t\t\t                    Press any key to continue..                             ");
    getch();

    }




int main() {
  welcome();
arr stat={0,0,0,0}; //init the values
queue *loans=createQueue();
list lst ={NULL,NULL};
list_book BOOK={NULL,NULL};//both the head and the tail of the borrower list are initialized to NULL

  int menu;
BOOK=auto_add_book(BOOK,stat);
lst=auto_add_borr(lst,stat);
  do {
    system("cls");
    printf("Library management system\n\n");
    printf("1-Display book list.\n");
    printf("2-Add book \n"); /// add and return are not the same,in return i need to askfor the student id and maybe other stuff
    printf("3-Remove a book or Take a book.\n"); /// but in add i need nothing
    printf("4-Display borrower list.\n");
    printf("5-Add a new borrower .\n");  /// search book dont forget it
    printf("6-Delete a member.\n");
    printf("7-Issue a book'\n");
    printf("8-Return a book.\n");
    printf("9-Display Loan list.\n");
    printf("10-Display statistics of the total number of books and borrowers active loans, and overdue books.\n");
    printf("0-EXIT and delete all.\n\n");
    printf("Enter your choice:  ");

    scanf("%d", &menu);

    switch (menu) {
    case 1: {
            display_book(BOOK);
            break;
            }
    case 2: {
            BOOK=add_book(BOOK,stat);
            break;   /// will be changed the same way add borrower
            }
    case 3: {
            BOOK=manually_delete_book(BOOK,stat);
            break;
           }
    case 4:{
            display_borrower(lst);
            break;
           }
   case 5:
           {
            add_borr(lst,stat);
            break;

          }
   case 6 :
          {
           lst=manually_delete_member(lst,stat);
           break;
          }
   case 7 :
          {
           BOOK=issue_book_menu(BOOK,lst,loans,stat);
           break;
          }
   case 8:
         {
          BOOK=return_book_menu(BOOK,lst,stat);
          break;
         }
   case 9 :
         {
         display_loans(lst);
         break;
         }
   case 10:
    { printf("Array contents:\n");
    for (int i = 0; i < 4; i++) {
        printf("arr[%d] = %d\n", i, stat[i]);
    }
    getch();
        break;
    }

    default: {
      printf("Invalid Choice...\n\n");
      printf("\n\t\t\t\t      Press any key to try again: ");
      getch();
    }
    }

  } while (menu != 0);

  return 0;
}
