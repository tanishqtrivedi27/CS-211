#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
 
/*------------Node structure---------*/
struct node
{
    int data;
    struct node* left;
    struct node* right;
}*pre, *suc;
 
/*----------BST------------------BST--------------------------BST-----------------------*/

struct node* insert_BST(struct node* root, int val, FILE* fptr_2){
    if(root == NULL){
        struct node* temp = (struct node*)malloc(1*sizeof(struct node));
        temp->data=val;
        temp->right=NULL;
        temp->left=NULL;
        fprintf(fptr_2, "%d inserted\n", val);
        return temp;
    }
    if (val < root->data)
        root->left = insert_BST(root->left, val, fptr_2);

    else
        root->right = insert_BST(root->right, val, fptr_2);   
    
}

void preOrder(struct node* root, FILE* fptr_2){

    if (root == NULL)
    {   
        return;
    }
    
    fprintf(fptr_2, "%d ",root->data);
    preOrder(root->left, fptr_2);
    preOrder(root->right, fptr_2);
}

void inOrder(struct node* root, FILE* fptr_2){
    if (root == NULL)
    {
        return;
    }

    inOrder(root->left, fptr_2);
    fprintf(fptr_2, "%d ",root->data);
    inOrder(root->right, fptr_2);
}

void postOrder(struct node* root, FILE* fptr_2){
    if (root == NULL)
    {
        return;
    }

    postOrder(root->left, fptr_2);
    postOrder(root->right, fptr_2);
    fprintf(fptr_2, "%d ",root->data);
}

struct node* search_BST(struct node* root, int key, FILE* fptr_2){
    if (root == NULL)
    {
        fprintf(fptr_2, "%d not found\n", key);
        return NULL;
    }
    
    if (root->data == key)
    {
        fprintf(fptr_2, "%d found\n", key);
        return root;
    }

    if (root->data < key)
    {
        return search_BST(root->right, key, fptr_2);
    }

    return search_BST(root->left, key, fptr_2);
}

bool search(struct node* root, int key, FILE* fptr_2){
    if (root == NULL)
    {
        return 0;
    }
    
    if (root->data == key)
    {
        return 1;
    }

    if (root->data < key)
    {
        return search(root->right, key, fptr_2);
    }

    return search(root->left, key, fptr_2);
}

void max_BST(struct node* root, FILE* fptr_2){
    struct node* curr = root;
    if (curr == NULL)
    {   
        fprintf(fptr_2, "\n");
        return;
    }
    
    while (curr->right != NULL)
        curr = curr->right;
    
    fprintf(fptr_2, "%d\n", curr->data);
    return;
}

void min_BST(struct node* root, FILE* fptr_2){
    struct node* curr = root;
    if (curr == NULL)
    {   
        fprintf(fptr_2, "\n");
        return;
    }
    
    while (curr->left != NULL)
        curr = curr->left;
    
    fprintf(fptr_2, "%d\n", curr->data);
    return;
}

void pre_BST(struct node* root, int key, FILE* fptr_2){

        if (root->data == key)
        {
            if (root->left != NULL)
            {
                struct node* temp = root->left;
                while (temp->right)
                    temp = temp->right;

                pre = temp;
            }
        }

        else if (root->data > key)
        {
            pre_BST(root->left, key, fptr_2);
        }
        else
        {
            pre = root;
            pre_BST(root->right, key, fptr_2);
        }

        return;
}

void suc_BST(struct node* root, int key, FILE* fptr_2){
    
        if (root->data == key)
        {
            if (root->right != NULL)
            {
                struct node* temp = root->right;
                while (temp->left)
                    temp = temp->left;

                suc = temp;
            }
        }

        else if (root->data > key)
        {
            suc = root;
            suc_BST(root->left, key, fptr_2);
        }
        else
        {
            suc_BST(root->right, key, fptr_2);
        }

        return;
}


/*---------Driver code--------------*/


int main(int argc, char* argv[])
{   
    FILE *fptr, *fptr_2;
    printf("Value of argv[0]= %s\n",argv[0]);
    printf("Value of argv[1]= %s\n",argv[1]);

    fptr = fopen(argv[1], "r");
    fptr_2 = fopen("bst.txt","w");

    // Exception handling for input.txt
    if (fptr == NULL) 
        {
        	printf("Error! File not found");
        	return 0;
        }


    struct node* root = NULL;
    
    int n;
    char buff[12];

    while (!feof(fptr))
    {
        if(fscanf(fptr,"%s", buff) == 1){
            if (!strcmp(buff, "insert"))
            {
                fscanf(fptr,"%d",&n);
                if (root == NULL)
                    root = insert_BST(root, n, fptr_2);

                else
                    insert_BST(root, n, fptr_2);
            }
            else if (!strcmp(buff, "postorder"))
            {
                postOrder(root, fptr_2);
                fprintf(fptr_2, "\n");
            }
            else if (!strcmp(buff, "preorder"))
            {
                preOrder(root, fptr_2);
                fprintf(fptr_2, "\n");
            }
            else if (!strcmp(buff, "inorder"))
            {
                inOrder(root, fptr_2);
                fprintf(fptr_2, "\n");
            }
            else if (!strcmp(buff, "search"))
            {
                fscanf(fptr,"%d",&n);
                search_BST(root, n, fptr_2);
            }
            else if (!strcmp(buff, "maximum"))
            {   
                max_BST(root, fptr_2); 
            }
            else if (!strcmp(buff, "minimum"))
            {
                min_BST(root, fptr_2);
            }
            else if (!strcmp(buff, "predecessor"))
            {
                fscanf(fptr,"%d",&n);
                if(search(root, n, fptr_2))
                {   
                    pre_BST(root, n, fptr_2);
                    if (pre == NULL)
                        fprintf(fptr_2, "predecessor of %d does not exist\n", n);
                    else
                        fprintf(fptr_2, "%d\n", pre->data);
                }  
                else
                {
                    fprintf(fptr_2, "%d does not exist\n", n);
                }
            }
            else if (!strcmp(buff, "successor"))
            {
                fscanf(fptr,"%d",&n);
                if(search(root, n, fptr_2))
                {   
                    suc_BST(root, n, fptr_2);
                    if (suc == NULL)
                        fprintf(fptr_2, "successor of %d does not exist\n", n);
                    else
                        fprintf(fptr_2, "%d\n", suc->data);
                }  
                else
                {
                    fprintf(fptr_2, "%d does not exist\n", n);
                }
            }
        }
    }

    return 0;
}