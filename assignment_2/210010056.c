#include<stdio.h>
#include <stdlib.h>
// MERGE SORT

void Merger(int arr[], int left, int mid, int right){

    int n1=mid-left+1;
    int n2=right-mid;

    //these are temporary arrays
    int a[n1];
    int b[n2];

    //value is being assigned to arrays
    for (int i = 0; i < n1; i++)
        a[i] = arr[left+i];


    for (int i = 0; i < n2; i++)
        b[i] = arr[mid+1+i];

    
    int i = 0;
    int j = 0;
    int k = left;
    
    //sorting is done here
    //merge sort works for positive numbers
    while (i<n1 && j<n2)
    {
        if (a[i]<b[j])
        {
            arr[k] = a[i];
            k++; 
            i++;
        }
        else if (a[i]>b[j])
        {
            arr[k] = b[j];
            k++; 
            j++;
        }
        else if (a[i] == b[j])
        {
            arr[k] = a[i];
            arr[k+1] = b[j];
            k = k + 2;
            i++; j++;
        }
    }

    while(j<n2)
    {
        arr[k] = b[j]; 
        k++; j++;
    }


    while(i<n1)
    {
        arr[k] = a[i]; 
        k++; i++;
    }

}


void mergeSort(int arr[], int left, int right){

    if (right>left)
    {
        int mid = (left+right)/2;

        mergeSort(arr, left, mid);//splitting array into 2 parts
        mergeSort(arr, mid+1, right);

        Merger(arr, left, mid, right);//merging 2 arrays
    }
}

int main(int argc, char* argv[]){

	FILE *fptr, *fptr_2;
    
	printf("Value at argv[0]= %s\n",argv[0]);
    printf("Value at argv[1]= %s\n",argv[1]);
    
    //opening the 2 files
    fptr = fopen(argv[1],"r");
    fptr_2 = fopen("mergesort.txt","w");

    //exception handling if file doesn't open
    if (fptr == NULL) 
        {
        	printf("Error! File not found");
        	return 0;
        }

    int n;
    int arr[40000];
    int c = 0;

    for (int i = 0; i < 40000; i++)
    {
        if (fscanf(fptr,"%d",&n) == 1)
            arr[i] = n;
        else
        {
            arr[i] = -1;
            c = i;
            break;
        }
    }


    mergeSort(arr, 0, c-1);

    for (int i = 0; i < c; i++)
    {
        fprintf(fptr_2, "%d\n", arr[i]);
    }

    fclose(fptr);
    fclose(fptr_2);
    return 0;
}