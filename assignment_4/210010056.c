#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
/*------------Node structure---------*/
struct node
{
    int val;
    struct node *ptr;
}*top,*top1,*temp,*front,*rear,*front1;
 
/*---------------------STACK-----------------------STACK------------------------STACK------------------------*/

int count = 0; // maintaining count for elements of stack

// Initialize a stack
void createStack()
{
    top = NULL;
}
 
/* Push data into stack */
void push(int data, FILE* fptr_2, int d)
{
    if (top == NULL)
    {
        top =(struct node *)malloc(1*sizeof(struct node));
        top->ptr = NULL;
        top->val = data;
        fprintf(fptr_2, "pushed %d\n", data);
    }
    else
    {   
        if (count<=d)
        {
            temp =(struct node *)malloc(1*sizeof(struct node));
            temp->ptr = top;
            temp->val = data;
            top = temp;
            fprintf(fptr_2, "pushed %d\n", data);
        }
        else
        {
            fprintf(fptr_2, "overflow \n");
        }
    }
    count++;
}
 
/* Display stack elements */
void display(FILE* fptr_2)
{
    top1 = top;
 
    if (top1 == NULL)
    {
        fprintf(fptr_2, "\n");
        return;
    }
    while (top1 != NULL)
    {
        fprintf(fptr_2, "%d ", top1->val);
        top1 = top1->ptr;
    }
    fprintf(fptr_2, "\n");
 }
 
/* Pop Operation on stack */
void pop(FILE* fptr_2)
{
    top1 = top;
 
    if (top1 == NULL)
    {
        fprintf(fptr_2, "Error : Trying to pop from empty stack\n");
        return;
    }
    else
        top1 = top1->ptr;
    fprintf(fptr_2, "popped %d \n", top->val);
    free(top);
    top = top1;
    count--;
}
 
/* Search stack elements */
void searchStack(int key, FILE* fptr_2)
{
    top1 = top;
 
    while (top1 != NULL)
    {
        if (top1->val == key)
        {
            fprintf(fptr_2, "found %d\n", key);
            return;
        }
        top1 = top1->ptr;
    }
    
    fprintf(fptr_2, "not found %d\n", key);
}


/*----------Doubly linked list-----------------------------------Doubly linked list-----------------------Doubly linked list----*/

struct node_dll
{
    int val;
    struct node_dll *prev;
    struct node_dll *next;
}*newnode, *trav, *head, *todelete;

/* TO create an empty node */
void createLinkedList()
{
    head = NULL;
}

void insert(int data, FILE* fptr_3){
    newnode = (struct node_dll *)malloc(1*sizeof(struct node_dll));
    newnode->prev = NULL;
    newnode->next = NULL;
    newnode->val = data;
    newnode->next = head;
    if (head != NULL) 
        head->prev = newnode;

    head = newnode;
    fprintf(fptr_3, "inserted %d\n", data);
}
 
void deleteHead(){
    todelete = head;
    head = head->next;
    head->prev = NULL;
 
    free (todelete);
}

bool searchLinkedList2(int data, FILE* fptr_3)
{
    trav = head;
    if (head->val == data)
    {
        return 1;
    }
    
    while (trav->next != NULL)
    {
        if (trav->val == data)
        {
            return 1;
        }
        trav = trav->next;
    }
    return 0;
}

/* To delete an element */
void deleteList(int data, FILE* fptr_3)
{   
    if (searchLinkedList2(data, fptr_3))
    {
        
    if (head->val == data)
    {
        deleteHead();
        fprintf(fptr_3, "deleted %d\n", data);
        return;
    }
    
    trav = head;
    while (trav->next->val != data)
    {
        trav = trav->next;
    }
    
    todelete = trav->next;
    trav->next = todelete->next;
    todelete->next->prev = trav;
    fprintf(fptr_3, "deleted %d \n", todelete->val);
    free(todelete);
    }
    
    else{
        fprintf(fptr_3, "cannot delete %d \n", data);
    }

}

/* To search for an element in the list */
void searchLinkedList(int data, FILE* fptr_3)
{
    trav = head;
    if (head->val == data)
    {
        fprintf(fptr_3, "found %d\n", data);
        return;
    }
    
    while (trav->next != NULL)
    {
        if (trav->val == data)
        {
            fprintf(fptr_3, "found %d\n", data);
            return;
        }
        trav = trav->next;
    }
    fprintf(fptr_3, "not found %d\n", data);
}
 
/* Traverse */
void traverse(FILE* fptr_3)
{
    trav = head;

    while (trav != NULL)
    {
        fprintf(fptr_3, "%d ", trav->val);
        trav = trav->next;
    }
    
    fprintf(fptr_3, "\n");
}

 
/*--------------QUEUE------------QUEUE---------QUEUE----------*/

/* Create an empty queue */
void create()
{
    front = rear = NULL;
}
 
int countq = 0;
/* Enqueing  */
void enq(int data, int d, FILE* fptr_4)
{   
    if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->val = data;
        front = rear;
        rear->ptr = front;
        fprintf(fptr_4, "enqueued %d \n", data);
    }
    else
    {   
        if (countq<=d)
        {
            temp=(struct node *)malloc(1*sizeof(struct node));
            rear->ptr = temp;
            temp->val = data;
            temp->ptr = front;
            rear = temp;
            fprintf(fptr_4, "enqueued %d \n", data);
        }
        
        else
        {
            fprintf(fptr_4, "overflow \n");
        }
    }
    countq++;
}
 
/* Displaying the queue elements */
void display_q(FILE* fptr_4)
{
    front1 = front;
 
    if ((front1 == NULL) && (rear == NULL))
    {
        fprintf(fptr_4, "\n");
        return;
    }
    while (front1 != rear)
    {
        fprintf(fptr_4, "%d ", front1->val);
        front1 = front1->ptr;
    }
    if (front1 == rear)
        fprintf(fptr_4, "%d \n", front1->val);
}
 
/* Dequeing the queue */
void deq(FILE* fptr_4)
{
    front1 = front;
 
    if (front == NULL)
    {
        printf("\n Error: Trying to dequeue elements from empty queue");
        return;
    }
    else
    {
        if (front1->ptr != front)
        {
            front1 = front1->ptr;
            fprintf(fptr_4, "dequeued %d\n", front->val);
            free(front);
            rear->ptr = front1;
            front = front1;
        }
        else
        {
            fprintf(fptr_4, "dequeued %d\n", front->val);
            free(front);
            front = NULL;
            rear = NULL;
        }
        countq--;
    }
}


 /* Searching the queue elements */
void search_q(FILE* fptr_4, int key)
{
    front1 = front;
 
    if ((front1 == NULL) && (rear == NULL))
    {
        fprintf(fptr_4, "Queue is empty");
        return;
    }
    while (front1 != rear)
    {   
        if (front1->val == key)
        {
            fprintf(fptr_4, "found %d\n", key);
            return;
        }
        front1 = front1->ptr;
    }

    fprintf(fptr_4, "not found %d\n", key);
}


/*---------Driver code--------------*/


int main(int argc, char* argv[])
{   
    FILE *fptr, *fptr_2, *fptr_3, *fptr_4;
    printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);
    printf("Value of argv[2]= %s\n",argv[2]);

    fptr = fopen(argv[1], "r");
    fptr_2 = fopen("stack.txt","w");
    fptr_3 = fopen("dll.txt","w");
    fptr_4 = fopen("queue.txt","w");

    int d = atoi(argv[2]); // second command-line argument for size of stack

    // Exception handling for input.txt
    if (fptr == NULL) 
        {
        	printf("Error! File not found");
        	return 0;
        }


    int n;
    char rt;

    while (!feof(fptr))
    {
        if(fscanf(fptr,"%c",&rt) == 1){
            if (rt == '+')
            {
                fscanf(fptr,"%d",&n);
                push(n, fptr_2, d);
                insert(n, fptr_3);
                enq(n, d, fptr_4);
            }
            else if (rt == '-')
            {
                fscanf(fptr,"%d",&n);
                pop(fptr_2);
                deleteList(n, fptr_3);
                deq(fptr_4);
            }
            else if (rt == '?')
            {
                fscanf(fptr,"%d",&n);
                searchStack(n, fptr_2);
                searchLinkedList(n, fptr_3);
                search_q(fptr_4, n);
            }
            else if (rt == '!')
            {
                display(fptr_2);
                traverse(fptr_3);
                display_q(fptr_4);
            }
        }
    }

    return 0;
}