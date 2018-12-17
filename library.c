#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct book{
    char *title;
    char *author;
    char *subject;
};

struct library{
    struct book collection;
    int num_books;
    struct library *next;
};

//Global variables to be accessed by functions
struct library *headptr;
struct library *tailptr;
int num_book=0;

//typedef for readability of the code
typedef struct book Book;

//Function prototypes in use
void addBook(struct library **head, Book newBook);
void deleteBook(struct library **head,char *delPtr);
void bookSearchtitle(struct library *head, char *searchTitle);
void searchByauthor(struct library *head, char *authName);
void searchBysubject(struct library *head, char *subName);
void copyBook(struct book *dest, struct book *source);
void printList(struct library *node);
int isEmpty(struct library *head);


/* Unused functions
void delBook2(struct library **head, struct library *current,char *delTitle);
void delBook1(struct library **head, struct library *lastbook, char *delTitle);
*/


int main()
{
    //Assignment and initialisation of variables
    char *delPtr = malloc(sizeof(char)*50);
    char surprise[100];
    char *author = malloc(sizeof(char)*50);
    char *subject = malloc(sizeof(char)*50);
    int command_num, book_count = 0,counter = 1,file_firstline; 

    //Initialising pointers 
    headptr = NULL;

    //Creating variable of type Book / struct book
    Book newBook;

    //File declarations
    FILE *lib = fopen("library.txt", "r");
    FILE *out = fopen("output.txt", "a+");
    //Use a condition to check whether output.txt is empty or already has data.

    fscanf(lib, "%d", &file_firstline);
    while(counter <= file_firstline)
    {
        fscanf(lib, "%d", &command_num); //Reads the first number in the line to determine command

        switch(command_num)
        {
            case 1:   
                if(num_book > 100)
                {
                   
                    printf("ERROR: THE LIBRARY IS FULL!\n");
                    break;
                }
                
                else
                {
                    num_book++;
                    //Allocating space to store the data
                    newBook.title = malloc(sizeof(char)*50); 
                    newBook.author = malloc(sizeof(char)*50);
                    newBook.subject = malloc(sizeof(char)*50);

                    fscanf(lib, "%s %s %s", newBook.title, newBook.author, newBook.subject);
                
                    addBook(&headptr,newBook);
    
                    counter++;
                    break;
                }

            case 2:
                fscanf(lib, "%s", delPtr);

                deleteBook(&headptr,delPtr);

                counter++;
                break;
            
            case 3:
                fscanf(lib, "%s", surprise);

                bookSearchtitle(headptr, surprise);
               
                counter++;
                break;

            case 4:
                fscanf(lib, "%s", author);
                
                searchByauthor(headptr, author);
                
                counter++;
                break;

            case 5: 
                fscanf(lib, "%s", subject);
                
                searchBysubject(headptr, subject);

                counter++;
                break;

        }  
        puts("");
    }

  
    fclose(lib);
    fclose(out);

}

void addBook(struct library **head, Book newBook)
{
    FILE *out = fopen("output.txt", "a");
    
    struct library *newPtr; //pointer to new node
    struct library *prev;
    struct library *curr;

    newPtr = malloc(sizeof(struct library));
    if(newPtr != NULL)
    {
        //Using a temp of sorts to store the new book
        newPtr -> collection = newBook; 
        newPtr -> next = NULL;

        prev = NULL; //prev is not pointing to anything at the start
        curr = (*head); //Use this to traverse list


        while(curr != NULL)
        {
            prev = curr; //following one step behind the current pointer
            curr = curr ->next; //advance the pointer
        }

        if(prev == NULL) 
        {
            newPtr -> next = (*head);
            (*head) = newPtr;
        }

        else
        {
            prev->next = newPtr; 
            newPtr->next = curr;
        }
    }

    newPtr ->num_books = ++num_book;
    printf("The book %s has been added to the library.\n", newBook.title);
    fprintf(out, "The book %s has been added to the library.\n", newBook.title);
    fprintf(out, "\n");
    fclose(out);
}


void deleteBook(struct library **head,char *delPtr)
{   
    FILE *out = fopen("output.txt", "a");
    struct library *prev;
    struct library *curr;
    struct library *temp;

    int flag=0;

    if((strcmp((*head)->collection.title, delPtr)) ==0) //If the node to be deleted is the first node
    {
        fprintf(out, "The book %s has been removed from the library.\n", (*head)->collection.title);
        printf("The book %s has been removed from the library.\n", (*head)->collection.title);
        temp = (*head);
        *head = (*head) ->next;
        free(temp);
        flag = 1;
    }

    else
    {
        prev = *head;
        curr = (*head) ->next;   
    
        while(curr != NULL && strcmp(delPtr, curr->collection.title) != 0)
        {
            prev = curr;
            curr = curr->next; //Advance the pointer as the title isn't found
        }    

        if(curr != NULL)
        {
            temp = curr;
            prev ->next = curr->next;
            printf("The book %s has been removed from the library.\n", temp->collection.title);
            fprintf(out, "The book %s has been removed from the library.\n", temp->collection.title);
            fprintf(out, "\n");
            free(temp);
            flag = 1;
        }     
    }

    if(flag != 1)
    {
        printf("The book %s cannot be deleted from the library because it does not exist in the library!\n", delPtr);
        fprintf(out, "The book %s cannot be deleted from library because it does not exist in the library!\n",delPtr);
        fprintf(out, "\n");
    }
    fclose(out);
}

void bookSearchtitle(struct library *head, char *searchTitle)
{
    FILE *out = fopen("output.txt", "a");
    struct library *curr = head;
    int flag;

    while (curr != NULL && curr -> collection.title != searchTitle)
    {
        if(strcmp(curr->collection.title, searchTitle ) == 0)
        {
           flag = 1; 
           break;
        }   
        else
        {
            flag = 0;
        }

        curr = curr -> next; //Advancing to next node
    }

    
    if(flag == 1) //If found
    {
        printf("The book %s is currently in the library.\n", curr ->collection.title);
        fprintf(out,"The book %s is currently in the library.\n", curr ->collection.title);
        fprintf(out, "\n");
    }
    else //Not found
    {
        printf("The book %s is currently NOT in the library.\n", searchTitle);
        fprintf(out,"The book %s is currently NOT in the library.\n", searchTitle);
        fprintf(out, "\n");
    }
    fclose(out);
}

void searchByauthor(struct library *head, char *authName)
{
    FILE *out=fopen("output.txt", "a");

    struct library *curr = head;

    char *list[50], tempauth[50], *templist;
    char *lowerAuth = malloc(sizeof(char)*50);

    int i = 0, flag = 0, x , y;
    int subLen = strlen(authName); //Length of string of subject

    strcpy(lowerAuth, authName); //Putting the original search value into a temp variable to convert it to lowercase

    for(int counter = 0 ; counter < subLen ; counter++)
    {
        lowerAuth[counter] = tolower(lowerAuth[counter]); //Convert author name to be searched to undercase
    }
    
    while (curr != NULL)
    {   
        strcpy(tempauth,curr ->collection.author);

        for(int counter = 0 ; counter < subLen ; counter++)
        {
            tempauth[counter] = tolower(tempauth[counter]); //Convert curr-> collection.author to lowercase
        }

        //If found author, keep the titles in a list
        if(strcmp(lowerAuth, tempauth) ==0)
        {
            flag =1 ;
            list[i] = curr->collection.title;
            i++;
        }
        curr = curr ->next;
    }

    //Sorting the list variable using bubble sort
    for(int x =0 ; x < i ; x++ )
    {
        for(y = x+1  ; y < i ; y++ )
        {
            if(strcmp(list[x], list[y]) > 0 ) //if the first element comes after second element
            {
                templist = list[y];
                list[y] = list[x];
                list[x] = templist;
            }
        }
    }

    if(flag != 1) //Books related to the author are not found
    {
        printf("There are no books related to %s.\n", authName);
        fprintf(out, "There are no books related to %s.\n", authName);
    }

    else //Books found related to the author
    { 
        printf("List of all books by %s \n", authName);
        fprintf(out, "List of all books by %s \n", authName);
        for(int a = 0  ; a < i ; a++)
        {
            printf("%s\n", list[a]);
            fprintf(out, "%s\n", list[a]);
        }
    }
    fprintf(out, "\n");
    fclose(out);
}

void searchBysubject(struct library *head, char *subName)
{
    FILE *out=fopen("output.txt", "a");

    struct library *curr = head;

    char *list[50], tempauth[50];
    char *lowerSub = malloc(sizeof(char)*50);

    int i = 0, flag = 0, x , y;
    int subLen = strlen(subName); //Length of string of subject

    strcpy(lowerSub, subName);

    for(int counter = 0 ; counter < subLen ; counter++)
    {
        lowerSub[counter] = tolower(lowerSub[counter]); //Convert author name to be searched to undercase
    }
    
    while (curr != NULL)
    {   
        strcpy(tempauth,curr ->collection.subject);

        for(int counter = 0 ; counter < subLen ; counter++)
        {
            tempauth[counter] = tolower(tempauth[counter]); //Convert curr-> collection.author to lowercase
        }

        //If found author, keep the titles
        if(strcmp(lowerSub, tempauth) ==0)
        {
            flag =1 ;
            list[i] = curr->collection.title;
            i++;
        }
        else
        {
            flag=  0;
        }
        curr = curr ->next;
    }

    //Sorting the list variable using bubble sort
    for(int x =0 ; x < i ; x++ )
    {
        char *templist;
        for(y = x+1  ; y < i ; y++ )
        {
            if(strcmp(list[x], list[y]) < 0 ) //if the first element is larger/ comes after second element
            {
                templist = list[y];
                list[y] = list[x];
                list[x] = templist;
            }
        }
    }

   if(flag != 1)
    {
        printf("There are no books related to %s.\n",subName);
        fprintf(out, "There are no books related to %s.\n", subName);
    }

    else
    { 
        printf("List of all books by %s \n", subName);
        fprintf(out, "List of all books by %s \n", subName);
        for(int a = 0  ; a < i ; a++)
        {
            printf("%s\n", list[a]);
            fprintf(out, "%s\n", list[a]);
        }
    }
    fprintf(out, "\n");

    fclose(out);
}

void copyBook(struct book *dest, struct book *source)
{
    *dest = *source;
}

int isEmpty(struct library *head)
{
    return head == NULL;
}

void printList(struct library *node)
{

    if(isEmpty(node))
    {
        puts("List is empty");
    }

    else
    {
        puts ("The list is: ");

        while(node != NULL)
        {
            printf("%s->", node->collection);
            node =  node->next;
        }

        puts("NULL\n");
    }
   
}

//Previous implementations
/*
void addBook(struct library **head, struct library **current, Book newBook)
{
    struct library *tempPtr; 
    tempPtr = malloc(sizeof(struct library));

    FILE *out;
    fopen("output.txt", "a");
    tempPtr -> collection = newBook; 
    tempPtr -> next = NULL; //Putting the book details into a temp pointer for use

    if ((*head) == NULL) //If the first node is empty
    {
        (*head) = tempPtr; 
        printf("The book %s has been added to the library.\n", (*head)->collection.title);
        //fprintf(out, "The book %s has been added to the library.\n", newBook.title);

    }
    else //If the first node is occupied
    {
        (*current) -> next = tempPtr;   
        printf("The book %s has been added to the library.\n", (*head)->collection.title);
    }

    *current = tempPtr;
    (*head)->num_books++;
    fclose(out);

    printList(*head);
}
*/

/*
void delBook2(struct library **head, struct library *curr, char *delTitle)
{
    struct library *follow = (*head);
    struct library *prev;
    struct library *temp;
    struct library *last;

    while(curr != NULL)
    {
        if(curr ->next == NULL)
        {
            last = curr; //Last node
        }
        curr = curr ->next;
        }


    while(curr != NULL)
    {
  
        while(strcmp(curr->collection.title, delTitle) != 0)
        {
            if(strcmp(curr->collection.title, delTitle) ==0) //If found the element
            {
                curr = last;
                
            }
            curr = follow ->next;

        }
        
    }
    

    

}

void delBook1(struct library **head, struct library *lastbook, char *delTitle)
{
    struct library *temp1 = (*head);
    struct library *lastNode = (*head);
    struct library *prevNode = (*head);


    while(strcmp(temp1->collection.title, delTitle) != 0)
    {
        temp1 = temp1 ->next; //Advance till find delTitle
        printf("Value of comparison of string compare is: %d\n", strcmp(temp1->collection.title, delTitle));
    } 

    if(strcmp(temp1->collection.title, delTitle) == 0)
    {
        struct library *temp2 = temp1->next;
        temp1 ->next = temp2->next;
    }

    
}
*/