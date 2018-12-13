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

//typedef for readability of the code
typedef struct book Book;


void addBook(struct library **head, struct library **current, Book newBook);
void delBook(struct library **head,struct library **current, char *delTitle);
void copybook(struct book* dest, struct book* source);
void printList(struct library *node);


int main()
{
    struct library *headptr = NULL;
    struct library *tailptr = NULL;
    char *delPtr = malloc(sizeof(char)*50);
    Book newBook;

    int command_num, book_count = 0,counter; 
    char surprise[100];
    FILE *lib = fopen("library.txt", "r");


    fscanf(lib, "%d", &counter);
    for(int x =0 ; x < counter ; x++)
    {
        fscanf(lib, "%d", &command_num); //Reads the first number in the line to determine command

        switch(command_num)
        {
            case 1:   
                book_count++;
                //Allocating space to store the data
                newBook.title = malloc(sizeof(char)*50); 
                newBook.author = malloc(sizeof(char)*50);
                newBook.subject = malloc(sizeof(char)*50);

                fscanf(lib, "%s %s %s", newBook.title, newBook.author, newBook.subject);
                addBook(&headptr, &tailptr, newBook);

                break;

            
            case 2:
                printf("Entered the second case\n");
                fscanf(lib, "%s", delPtr);

                delBook(&headptr, &tailptr, delPtr);
                printf("From head: %s\n", headptr->collection.title );
                printf("From tail: %s\n", tailptr ->collection.title);
               
                break;
            
            case 3:
            fscanf(lib, "%s", surprise);

            break;
        }
        //printf("From head: %s\n", headptr->collection.title );
        //printf("From tail: %s\n", tailptr ->collection.title);
    }

  
    fclose(lib);

}

void addBook(struct library **head, struct library **current, Book newBook)
{
    struct library *tempPtr; 

    tempPtr = malloc(sizeof(struct library));

    tempPtr -> collection = newBook; 
    tempPtr -> next = NULL;//Putting the book details into a temp pointer for use

    if ((*head) == NULL) //If the first node is empty
    {
        (*head) = tempPtr; 
       

    }
    else //If the first node is occupied
    {
        (*current) -> next = tempPtr;   
    }

    *current = tempPtr;
    puts("");
}


/*
void delBook(struct library **head, struct library **current, char *delTitle)
{
    struct library *temp = *head,*prev;
    
    if(temp != NULL && temp-> collection.title == delTitle)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && temp->collection.title != delTitle)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;

    free(temp);

}
*/




void delBook(struct library **head,struct library **current, char *delTitle)
{
    struct library *search = *head;

    struct library *last = NULL; //used to point to last element in linked list
    last = malloc(sizeof(struct library));


    /*
    //Find the last element of the linked list and assign it to another pointer
    while(search != NULL)
    {
        if(search->next == NULL)
        {
            last = search;
        }
    } search = search -> next;
    */

    //Searching for the element to delete
    //Use strcmp
    while(strcmp((*current) ->collection.title, delTitle) != 0) //while not a match, continue executing the condition in the loop
    {   
        if(strcmp((*current) ->collection.title, delTitle) == 0) //If matches, override the info
        {
            (*current) = last;
        }
        
    }  (*current) = (*current)-> next; //Keep going to the next element until it is found

}


void copybook(struct book* dest, struct book* source)
{
    
}