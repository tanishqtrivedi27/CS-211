#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max 2000

/* the adjacency list will have an array of node* 
where index of array will denote vertex and value in array will 
be head of of linked list, the linked list will contain all neighbours
of that vertex
*/
struct node
{
    int val;
    struct node* next;
};

struct node *temp, *temp2, *front, *rear;

/*  QUEUE DATA STRUCTURE */

void push(int data)
{   
    temp=(struct node *)malloc(1*sizeof(struct node));
    temp->val = data;
    temp->next = NULL;

    if (!front)
    {
        rear = temp;
        front = temp;
        return;
    }
    
    rear->next = temp;
    rear = temp;
}

int pop(){
    if (!front)
    {
        return -1;
    }
    
    temp2 = front;
    int re = front->val;
    front = front->next;
    free(temp2);
    return re;
}

bool empty(){
    if (front == NULL)
        return 1;
    
    return 0;
}

/*  QUEUE DATA STRUCTURE  ENDS*/

void addEdge(struct node* adjList[], int n1, int n2)
{
    temp = (struct node*)malloc(1*sizeof(struct node));
    temp->val = n2;

    temp->next = adjList[n1];
    adjList[n1] = temp;
}


void bfs(struct node* adjList[], int n, FILE* fptr){
    int arrDist[n]; // array to store distance to vertex, vertex is in index
    for (int i = 0; i < n; i++)
    {
        arrDist[i] = 1000;
    }
    

    arrDist[0] = 0;
    push(0);

    while (!empty())
    {  
        int num = pop();

        temp2 = adjList[num];
        while(temp2)
        {
            if (arrDist[num] + 1 < arrDist[temp2->val])
            {
                arrDist[temp2->val] = arrDist[num] + 1;
                push(temp2->val);
            }
            
            temp2 = temp2->next;
        }
    }

    for (int i = 0; i < n; i++)
    {   
        if (arrDist[i] == 1000)
        {
            arrDist[i] = -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "%d\n", arrDist[i]);
    }
    
}

int main(int argc, char* argv[])
{   
    FILE *fptr, *fptr_2;
    printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);

    fptr = fopen(argv[1], "r"); //input.graph
    fptr_2 = fopen("sd.txt","w"); //output file: sd.txt

    // Exception handling for input.txt
    if (fptr == NULL) 
        {
        	printf("Error! File not found");
            return 0;
        }

    int n, m, n1, n2; //no. of nodes, no. of edges
    struct node* adjList[max] = {NULL}; //array to store the heads of linked list
    
    fscanf(fptr, "%d", &n);
    fscanf(fptr, "%d", &m);
    
    while(!feof(fptr))
    {
        if(fscanf(fptr,"%d", &n1) && fscanf(fptr,"%d", &n2))
        {
            addEdge(adjList, n1, n2);
            addEdge(adjList, n2, n1);
        }
    }

    bfs(adjList, n, fptr_2);

    fclose(fptr);
    fclose(fptr_2);
    return 0;
}