//Binary search Tree
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

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s \n", root->key.am);
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
struct node *insert(struct node *node, struct student array[], int i)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(array, i);

    /* Otherwise, recur down the tree */
    if (strcmp(array[i].am, node->key.am) < 0)
        node->left = insert(node->left, array, i);
    else if (strcmp(array[i].am, node->key.am) > 0)
        node->right = insert(node->right, array, i);

    /* return the (unchanged) node pointer */
    return node;
}
struct node *search(struct node *root, char *x)
{
    if (root == NULL || strcmp(root->key.am, x) == 0)
        return root;
    else if ((strcmp(x, root->key.am) > 0))
        return search(root->right, x);
    else
        return search(root->left, x);
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

struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL)
        return find_minimum(root->left);
    return root;
}

struct node* deleteNode(struct node *root, char x[])
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (strcmp(x,root->key.am)>0)
        root->right = deleteNode(root->right, x);
    else if(strcmp(x,root->key.am)<0)
        root->left = deleteNode(root->left, x);
    else
    {
        //No Children
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left==NULL || root->right==NULL)
        {
            struct node *temp;
            if(root->left==NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            struct node *temp = find_minimum(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key.am);
        }
    }
    return root;
}
// Driver Program to test above functions
int main()
{
    int i;
    struct student array[50];
    readFile(array);
    struct node *root = NULL;
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
    struct node *st = NULL;

    while (check == 1)
    {
        printf("\n");
        printf("1.Inorder Traversal\n");
        printf("2.Search\n");
        printf("3.Search and edit\n");
        printf("4.Delete\n");
        printf("5.Exit\n");
        printf("\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            inorder(root);
            break;
        case 2:
            printf("Search by AM : ");
            scanf("%s", &word);
            print(search(root, word));
            break;
        case 3:
            printf("Search by AM : ");
            scanf("%s", &word);
            printf("\n");
            printf("Press 1 for FullName edit or 2 for Mark\n");
            printf("\n");
            scanf("%d", &n);
            struct node *per = search(root, word);
            if (per == NULL)
                n == 0;
            switch (n)
            {
            case 1:
                printf("Type the new Surname : ");
                scanf("%s", &word);
                strcpy(per->key.sname, word);
                printf("Type the new Name : ");
                scanf("%s", &word);
                strcpy(per->key.name, word);
                break;
            case 2:
                printf("Type the new Mark : ");
                scanf("%f", &mark);
                per->key.bathmos = mark;
                break;
            default:
                printf("Error ! Student Does not Exists. Try again .");
            }
            break;
        case 4:
            printf("Delete by AM : ");
            scanf("%s", &word);
            deleteNode(root,word);
            break;
        case 5:
            check = 0;
            break;
        default:
            printf("Wrong choice\n");
        } /*End of switch */
    }     /*End of while */

    return 0;
}
