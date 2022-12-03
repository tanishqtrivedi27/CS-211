#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 10000

int visited[MAX]; //visited array
int arr[MAX][MAX]; //Adjcency matrix 
int ans[MAX]; // array to store final distances

int main(int argc, char** argv){

    FILE *fptr, *fptr_2;
    printf("Value of argv[0]= %s\n",argv[0]);
    // printf("Value of argv[1]= %s\n",argv[1]);
    // printf("Value of argv[2]= %s\n",argv[2]);

    fptr = fopen("input.graph", "r"); //input.graph
    // int source = atoi(argv[2]); //Source taken input from command line argument
    fptr_2 = fopen("dijkstra.txt", "w"); //output file: dijkstra.txt

    int count = 0;
    int w, x, y;
    for (int i = 0; i < MAX; i++)
    {
        ans[i] = -1;
    }
    
    while(!feof(fptr)){
        fscanf(fptr,"%d", &w);
        fscanf(fptr,"%d", &x);
        fscanf(fptr,"%d", &y);

        // printf("%d\n", w);
        bool check = 0;
        for (int i = 0; i <= count; i++)
        {   
            if (ans[i] == w)
            {  
                check = 1;
                break;
            }
        }
        if (check == 0 )
        {
            ans[count++] = w;
        }
        
        check = 0;
        for (int i = 0; i <= count; i++)
        {   
            if (ans[i] == x)
            {  
                check = 1;
                break;
            }
        }
        if (check == 0 )
        {
            ans[count++] = x;
        }
    }

    printf("%d\n", count);

    for (int i = 0; i < count; i++)
    {
        printf("%d\n", ans[i]);
    }
    

    fclose(fptr);
    fclose(fptr_2);
    return 0;
}
