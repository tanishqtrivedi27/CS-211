#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 10000

int visited[MAX]; //visited array
int arr[MAX][MAX]; //Adjcency matrix 
int ans[MAX]; // array to store final distances
int set_vertex[MAX];

struct completed{
    int dist;
    int node;
    struct completed* next;
}*temp, *temp2, *todelete;

struct completed* head = NULL;

void insert(int val, int val2){
    temp = (struct completed*) malloc(1*sizeof(struct completed));
    temp->next = NULL;
    temp->dist = val;
    temp->node = val2;

    if (head == NULL) 
    {
        head = temp;
        return;
    }

    temp2 = head;
    while (temp2->next!=NULL)
    {
        temp2 = temp2->next;
    }
    temp2->next=temp;
}

void deleteAtHead(void){
    todelete=head;
    head = head->next;

    free(todelete);
}


void djikstra(int arr[MAX][MAX], int source){

    insert(0, source); //distance from source itself is 0
    ans[source] = 0;

    while(head != NULL){
        int weight = head->dist;
        int u = head->node;
        deleteAtHead();

        if (visited[u])
            continue;
        visited[u] = 1;

        for (int i = 0; i < MAX; i++)
        {
            if (i == u)
            {
                for (int j = 0; j < MAX; j++)
                {
                    if (arr[u][j] != -1)
                    {
                        if(arr[u][j] + ans[u] < ans[j]){
							ans[j] = arr[u][j] + ans[u]; 
							insert(ans[j],j);
						}
                    }                    
                }                
            }            
        }
    }


}

int main(int argc, char** argv){

    FILE *fptr, *fptr_2;
    printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);
    printf("Value of argv[2]= %s\n",argv[2]);

    fptr = fopen(argv[1], "r"); //input.graph
    int source = atoi(argv[2]); //Source taken input from command line argument
    fptr_2 = fopen("dijkstra.txt", "w"); //output file: dijkstra.txt

	if (fptr == NULL) 
        {
        	printf("Error! File not found");
            return 0;
        }

    
    for(int i=0;i<MAX;i++) //Intialising the whole visited array to 0
		visited[i] = 0;

    

	for(int i = 0;i < MAX;i++){ //Initialising all to -1
		for(int j=0;j<MAX;j++){
			arr[i][j] = -1;
		}
	}

    for(int i=0;i<MAX;i++) //Initialising all the distances to infinity
		ans[i] = INT_MAX;

    int x,y,w;
    int count = 0;

    for (int i = 0; i < MAX; i++)
    {
        set_vertex[i] = -1;
    }

    while(!feof(fptr)){
        fscanf(fptr,"%d", &x);
        fscanf(fptr,"%d", &y);
        fscanf(fptr,"%d", &w);

        arr[x][y] = w;

        bool check = 0;
        for (int i = 0; i <= count; i++)
        {   
            if (set_vertex[i] == x)
            {  
                check = 1;
                break;
            }
        }
        if (check == 0 )
        {
            set_vertex[count++] = x;
        }
        
        check = 0;
        for (int i = 0; i <= count; i++)
        {   
            if (set_vertex[i] == y)
            {  
                check = 1;
                break;
            }
        }
        if (check == 0 )
        {
            set_vertex[count++] = y;
        }
    }

    djikstra(arr, source);


    for (int i = 0; i < count; i++)
    {   
        if (ans[set_vertex[i]] == INT_MAX)
            fprintf(fptr_2, "%d -1\n", set_vertex[i]);
        else
            fprintf(fptr_2, "%d %d\n", set_vertex[i], ans[set_vertex[i]]);
        
    }

    return 0;
}
