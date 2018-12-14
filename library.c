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

//typedef for readability of the code
typedef struct book Book;


void addBook(struct library **head, struct library **current, Book newBook);
void delBook2(struct library **head, struct library **tailptr,char *delTitle);
void delBook1(struct library **head, struct library *lastbook, char *delTitle);
void delBook(struct library **head, struct library *headPtr, struct  library **current, char *delTitle);
void bookSearch(struct library **head, char *searchTitle);
void copybook(struct book* dest, struct book* source);
void printList(struct library *node);
void deleteBook(struct library **head,struct library *lastbook,char *title);


int main()
{
    headptr = NULL;
    tailptr = NULL;
    char *delPtr = malloc(sizeof(char)*50);
    Book newBook;

    int command_num, book_count = 0,counter; 
    char surprise[100];
    FILE *lib = fopen("library.txt", "r");
    FILE *out = fopen("output.txt", "a+");
    //Use a condition to check whether output.txt is empty or already has data.

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
                fprintf(out, "The book %s has been added to the library.\n", newBook.title);
                addBook(&headptr,&tailptr, newBook);

                break;

            
            case 2:
                printf("Entered the second case\n");
                fscanf(lib, "%s", delPtr);
                printf("Title to be deleted is: %s\n", delPtr);
                delBook2(&headptr, &tailptr,delPtr);
                printf("FUnction executed\n");
               
                break;
            
            case 3:
            fscanf(lib, "%s", surprise);
            bookSearch(&headptr, surprise);
            printf("Case 3");
            break;
        }
        printf("From head: %s\n", headptr->collection.title );
        printf("At tail: %s\n", tailptr ->collection);
        puts("");
    }

  
    fclose(lib);
    fclose(out);

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
    (*head)->num_books++;
}


//Add a if condition in the case that the last node is a null
void delBook2(struct library **head, struct library **tail, char *delTitle)
{
    struct library *prev=(*head);
    struct library *curr =NULL;
    struct library *temp =NULL;

    if(strcmp((*head)->collection.title,delTitle) ==0)
    {
        temp = (*head);
        (*head) = (*head) -> next;
        free(temp);
        return;
    }

    else
    {
        prev = (*head);
        curr = (*head) -> next;

        while(curr != NULL && (strcmp(curr ->collection.title, delTitle) != 0))
        {
            prev = curr;
            curr = curr->next;
            
        }

        if(curr->next != NULL && strcmp(curr-> collection.title, delTitle) == 0 )
        {
            temp->collection = curr->collection;
            prev->collection = temp -> next->collection;
            free(temp);

        }
 
    }

}
/*
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

void delBook(struct library **head, struct library *headPtr, struct  library **current, char *delTitle)
{
    struct library *searchDel; //To traverse the list
    struct library *prev; //used to point to last element in linked list
    struct library *lastNode;
    

    searchDel = (*head); //Assigning it to first node (head)
    prev = (*head); //Used to keep track of the prev node

    //Find the last element of the linked list and assign it to another pointer
    while(searchDel->next != NULL)
    {
        if(searchDel -> next == NULL)
        {
            (*current) = searchDel->next;
        }
        prev = searchDel; //This acts as the prev node from searchDel(current node)
        searchDel = searchDel -> next;
    }

    if(searchDel == headPtr)
        {
            headPtr = NULL;
        }
        else
        {
            // Disconnects the link of second last node with last node 
            prev->next = NULL;
        }
        

    struct book *lastLibraryBook = &(prev -> collection);
    printf("The last book is %s\n",(*lastLibraryBook).title);


    //Searching for the element to delete
    //Use strcmp
    while(strcmp(searchDel->collection.title, delTitle) != 0) //while not a match, continue executing the condition in the loop
    {   
        if(strcmp((*current) ->collection.title, delTitle) == 0) //If matches, override the info
        {
            (*current)->collection = prev->collection;
        }
        
    }  (*current) = (*current)-> next; //Keep going to the next element until it is found


}


void bookSearch(struct library **head, char *searchTitle)
{
    // 
}


void copybook(struct book* dest, struct book* source)
{
    *dest = *source;
}
