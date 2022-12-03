#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max 10000

struct node
{
    int val;
    struct node* next;
}*temp, *temp2;

void addEdge(struct node* adjList[], int n1, int n2)
{
    temp = (struct node*)malloc(1*sizeof(struct node));
    temp->val = n2;

    temp->next = adjList[n1];
    adjList[n1] = temp;
}

int count = 0;

void dfs(int node, bool visited[], struct node* adjList[], int ans[]){
    visited[node] = 1;

    struct node* temp3 = adjList[node];

    while (temp3)
    {   
        if (!visited[temp3->val])
            dfs(temp3->val, visited, adjList, ans);
        
        temp3 = temp3->next;
    }

    ans[count++] = node;
    return;
}

int main(int argc, char* argv[])
{   
    FILE *fptr, *fptr_2;
    printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);

    fptr = fopen(argv[1], "r"); //input.graph
    fptr_2 = fopen("ts.txt","w"); //output file: ts.txt

    // Exception handling for input.txt
    if (fptr == NULL) 
        {
        	printf("Error! File not found");
            return 0;
        }
    
    int n, m, n1, n2;
    
    fscanf(fptr, "%d", &n); // no. of nodes
    fscanf(fptr, "%d", &m); // no. of edges

    struct node* adjList[max]; //array to store the heads of linked list

    for (int i = 0; i < max; i++)
        adjList[i] = NULL;
    

    for (int i = 0; i < m; i++)
    {
        if(fscanf(fptr,"%d", &n1) && fscanf(fptr,"%d", &n2))
        {
            addEdge(adjList, n1, n2);
        }
    }
    
    bool visited[max];
    int ans[max];
    for (int i = 0; i < max; i++)
    {
        visited[i] = 0;
        ans[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {   
        if (!visited[i])
        {
            dfs(i, visited, adjList, ans);
        }
    }

    for (int i = n-1; i >=0; i--)
    {
        fprintf(fptr_2, "%d\n", ans[i]);
    } 

    fclose(fptr);
    fclose(fptr_2);
    return 0;
}