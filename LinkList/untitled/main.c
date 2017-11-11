#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
struct python{
    int value;
    struct python *nextPtr;
} ;
typedef struct python node;
enum _status{
    NORMAL,DISPLAY,INSERT,DEL,EXIT
};
void insert(node* *ptr,char data);
void display(node* currentPtr);
void deleteLastOne(node* *ptr);
int main(void)
{
    node* startPtr = NULL;
    enum _status status = NORMAL;
    uint8_t user_input = 1;
    while (status != EXIT){
        if (status == NORMAL){
            printf("Please Select Mode: (1:Display,2:Insert,3:Delete,4:Exit)");
            scanf("%c",&user_input);
            getchar();
            switch (user_input){
            case '1':
                printf("\nDisplay:");
                printf("startPtr = 0x%p \n",startPtr);
                display(startPtr);
                printf("\n");
                break;
            case '2':
                printf("startPtr = 0x%p \n",startPtr);
                printf("\nInsert(int 0~100):");
                __mingw_scanf("%hhu",&user_input);
                getchar();
                insert(&startPtr, user_input);
                printf("\n");
                break;
            case '3':
                printf("\nDeleteing...");
                deleteLastOne(&startPtr);
                printf("\n");
                break;
            case '4':
                printf("\nExit!\n");
                status = EXIT;
                break;
            default:
                printf("\nError!");
            }
        }
    }
}
void insert(node* *ptr,char data)
{
    node* newPtr  = NULL;
    node* previousPtr  = NULL;
    node* currentPtr = NULL;

    newPtr = (node*)malloc(sizeof(node));

    printf("startPtr = %p \t",*ptr);
    printf("newPtr = %p \n",newPtr);

    newPtr->value = data;
    newPtr->nextPtr = NULL;

    previousPtr = NULL;
    currentPtr = *ptr;

    while(currentPtr != NULL){
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }
    if(previousPtr == NULL){
        *ptr = newPtr;
    }
    else{
        previousPtr->nextPtr = newPtr;
    }
}

void display(node* currentPtr){
    if ( currentPtr == NULL){
        puts("\n List is empty \n");
    }
    else{
        puts("List is:");
        while (currentPtr != NULL){
            printf("%d --> ", currentPtr->value);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}

void deleteLastOne(node* *ptr){
    node* previousPtr  = NULL;
    node* currentPtr = NULL;

    previousPtr = NULL;
    currentPtr = *ptr;

    if(currentPtr != NULL){
        while(currentPtr->nextPtr != NULL){
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }
        if(previousPtr != NULL){
            free(currentPtr);
            previousPtr->nextPtr = NULL;
        }
        else{
            free(currentPtr);
            *ptr = NULL;
            puts("\n List is empty now \n");
        }
    }
    else{
        puts("\n List is empty \n");
    }
}
