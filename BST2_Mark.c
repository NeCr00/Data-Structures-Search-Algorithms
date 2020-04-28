//Binary search tree vol2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bufSize 1024
struct student
{
    char name[50];
    char sname[50];
    char am[20];
    float bathmos;
};

struct node
{
    struct student key;
    struct node *left, *right;
};

void readFile(struct student array[])
{

    FILE *fp;
    char buf[bufSize];

    if ((fp = fopen("test.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    char buff[256];
    int i = 0;

    for (i = 0; fgets(buff, sizeof(buff), fp) != NULL; i++)
    {
        char *pch;
        pch = strtok(buff, " ,-");
        int j = 0;
        while (pch != NULL)
        {
            if (j == 0)
            {
                memcpy(array[i].am, pch, sizeof(pch) * 8);
                //printf(" %d,%d: %s\n", i, j, array[i].am);
            }
            else if (j == 1)
            {
                memcpy(array[i].name, pch, sizeof(pch) * 8);
                //printf(" %d,%d: %s\n", i, j, array[i].name);
            }
            else if (j == 2)
            {

                memcpy(array[i].sname, pch, sizeof(pch) * 8);
                // printf(" %d,%d: %s\n", i, j, array[i].sname);
            }
            else if (j == 3)
            {
                array[i].bathmos = atof(pch);
                //printf(" %d,%d: %.02lf\n", i, j, array[i].bathmos);

                j = 0;
            }
            j++;
            pch = strtok(NULL, " ,-");
        }
    }

    fclose(fp);
}

// A utility function to create a new BST node
struct node *newNode(struct student array[], int i)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = array[i];
    temp->left = temp->right = NULL;
    return temp;
}

struct node  *MinMax(struct node *root,float mark)
{
    if(root!= NULL && root->key.bathmos == mark)
        print(root);

    if (root != NULL)
    {
        MinMax(root->left,mark);
        MinMax(root->right,mark);
    }
}

/* A utility function to insert a new node with given key in BST */
struct node *insert(struct node *node, struct student array[], int i)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(array, i);

    /* Otherwise, recur down the tree */
    if (array[i].bathmos < node->key.bathmos)
        node->left = insert(node->left, array, i);
    else if (array[i].bathmos >= node->key.bathmos)
        node->right = insert(node->right, array, i);

    /* return the (unchanged) node pointer */
    return node;
}


struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL)
        return find_minimum(root->left);
    return root;
}
struct node* find_maximun(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->right != NULL)
        return find_maximun(root->right);
    return root;
}




void print(struct node *person)
{
    printf("\n");
    printf("=============Student Information===========\n");
    printf(" AM :%s \n", person->key.am);
    printf(" FullName :%s %s\n", person->key.sname, person->key.name);
    printf(" Mark : %.2f\n", person->key.bathmos);
    printf("=========================================== \n");
    printf("\n");
}

// Driver Program to test above functions
int main()
{
    int i;
    struct student array[50];
    readFile(array);
    struct node *root = NULL;
    char temp [256];
    char word[256];

    root = insert(root, array, 9);
    for (i = 0; i < 19; i++)
    {
        if (i == 9)
            i++;
        insert(root, array, i);
    }

    int choice, check = 1;
    int n;
    float mark;

    while (check == 1)
    {
        printf("\n");
        printf("1.Search Students with the minimum mark \n");
        printf("2.Search Students with the maximum mark\n");
        printf("3.Exit\n");
        printf("\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:

            MinMax(root,find_minimum(root)->key.bathmos);
            break;
        case 2:
            MinMax(root,find_maximun(root)->key.bathmos);

            break;

        case 3:
            check = 0;
            break;
        default:
            printf("Wrong choice\n");
        } /*End of switch */
    }     /*End of while */

    return 0;
}
