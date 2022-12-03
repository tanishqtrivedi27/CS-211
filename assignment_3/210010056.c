#include<stdio.h>
#include <stdlib.h>
#include "math.h"

int power(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y%2 == 0)
        return power(x, y/2)*power(x, y/2);
    else
        return x*power(x, y/2)*power(x, y/2);
}

//Count Sort
//n is the size of array arr[]
//dg gives digit for which count sort is to be applied
int countSorter(int arr[], int n, int dg){
    int ds[n]; //array to store digits of number

    for (int i = 0; i < n; i++)
        ds[i] = ((arr[i]%(power(10,dg))) - (arr[i]%(power(10,dg-1))))/(power(10, dg-1));

    int freq[10] = { 0 };//array to store frequeny of digits

    for (int i = 0; i < n; i++)
        freq[ds[i]]++;

    for (int i = 1; i < 10; i++)
        freq[i] += freq[i-1];
    
    int output[n];

    for (int i = n-1; i >= 0; i--)
        output[--freq[ds[i]]] = arr[i];
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
}

//Radix Sort
void radixSorter(int arr[], int n, int d){

    for (int i = 1; i <= d; i++)    
        countSorter(arr, n, i);

}

int main(int argc, char* argv[]){

    FILE *fptr, *fptr_2;
    
	printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);
    printf("Value of argv[2]= %s\n",argv[2]);
    
    int d = atoi(argv[2]); // second command-line argument for number of digits
    //opening the 2 files
    fptr = fopen(argv[1],"r");
    fptr_2 = fopen("radix.txt","w");

    //exception handling if file doesn't open
    if (fptr == NULL) 
        {
        	printf("Error! File not found");
        	return 0;
        }
    

    int n;
    int arr[40000];
    int c = 0;

    for (int i = 0; i < 40000; i++) //making array with numbers given in file
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


    radixSorter(arr, c, d);
    
    for (int i = 0; i < c; i++)
        fprintf(fptr_2, "%d\n", arr[i]);


    fclose(fptr);
    fclose(fptr_2);

    return 0;
}