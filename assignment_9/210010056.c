#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Edge{
	int source;
	int destination;
	int weight;
};

int findPar(int v, int *parent){
	if(parent[v] == v)
		return v;

	return findPar(parent[v], parent);
}

int max(int u, int v){
	if (u >= v)
		return u;

	return v;
}

void swap(struct Edge *xp, struct Edge *yp)
{
    struct Edge temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(struct Edge* arr, int E){
    for (int i = 0; i < E-1; i++)
    {
        int minNo = i;
        for (int j = i+1; j < E; j++)
        {
            if (arr[j].weight<arr[minNo].weight)
            {
                minNo = j;
            }
        }
        swap(&arr[i], &arr[minNo]);
    }
}

void kruskal(struct Edge *input, int n, int E, FILE* fptr){
	//Sorting the input array in ascending order
	sort (input, E);

	struct Edge *output = (struct Edge*) malloc((n-1)*sizeof(struct Edge));

	int *parent = (int*) malloc(1000000*sizeof(int)); //Parent array defined

	for(int i = 0; i < 1000000; i++){
		parent[i] = i;
	}

	int count = 0;
	int i = 0;
	while(count != n-1){
		struct Edge current = input[i];
		
		int source_p = findPar(current.source, parent);
		int destination_p = findPar(current.destination, parent);
	
		if(source_p != destination_p){ //Checking if current can be added to MST or not
			output[count] = current;
			count++;
			parent[source_p] = destination_p;
		}
		i++;
	}
	
	int r = 0; 
	while(r<n-1){
		fprintf(fptr, "%d %d %d\n", output[r].source, output[r].destination, output[r].weight);
		r++;
	}
}

int main(int argc, char* argv[]){
    FILE *fptr, *fptr_2, *fptr_3;
    printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);

    fptr = fopen(argv[1], "r"); //input.graph
	fptr_3 = fopen(argv[1], "r"); //input.graph
    fptr_2 = fopen("mst.txt", "w"); //output file: mst.txt

	if (fptr == NULL) 
        {
        	printf("Error! File not found");
            return 0;
        }

	int E = -1, n1, n2, n3; //no. of edges

	int n = INT_MIN;

	bool flag = 0;

    while(!feof(fptr))
    {
        if(fscanf(fptr,"%d", &n1) && fscanf(fptr,"%d", &n2) && fscanf(fptr,"%d", &n3))
        {
			E++;
			n = max(n, n1);
			n = max(n, n2);
			if (n1 == 0 || n2 == 0)
			{
				flag = 1;
			}
        }
    }

	if (flag)
	{
		n++;
	}
	

	fclose(fptr);
	fptr = fopen(argv[1], "r");

	struct Edge* input = (struct Edge*) malloc(E*sizeof(struct Edge));

	for (int i = 0; i < E; i++)
	{
		int s, d, w;
		fscanf(fptr,"%d", &s);
		fscanf(fptr,"%d", &d);
		fscanf(fptr,"%d", &w);

		input[i].source = s; //Storing source
		input[i].destination = d; //Storing destination
		input[i].weight = w; //Storing weight
	}

	// printf("%d %d", E, n);

	kruskal(input, n, E, fptr_2); 
	
	
    fclose(fptr_2);
	fclose(fptr);
    return 0;
}