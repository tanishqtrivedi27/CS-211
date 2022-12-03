#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node
{
    char word[25];
    struct node* next;
};

struct node *temp, *temp2;

int hashFunction(char word[25], int m){
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum = sum + (int)word[i];
    }

    return sum%m;
}

void insertAtHead(char wordIn[25], struct node* arr[], int m){
    temp = (struct node*)malloc(1*sizeof(struct node));
    
    strcpy(temp->word, wordIn);
    int idx = hashFunction(wordIn, m);

    temp->next = arr[idx];
    arr[idx] = temp;
}

bool sort(char str[], char str2[]){
    int m = strlen(str);
    int n = strlen(str2);
    int i, j;
    char temp;
    char str3[m];
    strcpy(str3, str);
    char str4[n];
    strcpy(str4, str2);

    for (i = 0; i < m-1; i++) {
        for (j = i+1; j < m; j++) {
            if (str3[i] > str3[j]) {
                temp = str3[i];
                str3[i] = str3[j];
                str3[j] = temp;
            }
        }
    }

    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (str4[i] > str4[j]) {
                temp = str4[i];
                str4[i] = str4[j];
                str4[j] = temp;
            }
        }
    }

    if(strcmp(str3, str4) == 0)
        return 1;
    else
        return 0;
}


void display(struct node* head, FILE* fptr, char str[])
{   
    temp = head;
    while (temp!=NULL)
    {   
        if (sort(temp->word, str))     
            fprintf(fptr, "%s ", temp->word);

        else
            fprintf(fptr, "");

        temp = temp->next;
    }
    fprintf(fptr, "\n");
    return;
}


int main(int argc, char* argv[])
{   
    FILE *fptr, *fptr_2, *fptr_3;
    printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);
    printf("Value of argv[2]= %s\n",argv[2]);
    printf("Value of argv[3]= %s\n",argv[3]);

    fptr = fopen(argv[1], "r"); //words.txt
    int m = (int)argv[2];
    fptr_2 = fopen(argv[3],"r"); //input file: query.txt
    fptr_3 = fopen("anagram.txt","w"); //output file: anagram.txt

    // Exception handling for input.txt
    if (fptr == NULL || fptr_2 ==  NULL) 
        {
        	printf("Error! File not found");
        	return 0;
        }

    char buff[25] = "";
    struct node* hashArray[27000] = {NULL}; //array to store the heads of linked list
    

    while (!feof(fptr))
    {
        if(fscanf(fptr,"%s", buff) == 1)
        {
            insertAtHead(buff, hashArray, m);
        }
    }

    while (!feof(fptr_2))
    {
        if(fscanf(fptr_2,"%s", buff) == 1)
        {
            int id = hashFunction(buff, m);
            display(hashArray[id], fptr_3, buff);
        }
    }



    fclose(fptr);
    fclose(fptr_2);
    fclose(fptr_3);
    return 0;
}