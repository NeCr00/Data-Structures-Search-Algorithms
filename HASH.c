#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bufSize 1024
#define MAX 20

struct Student
{
    char am[20];
    char name[20];
    char sname[20];
    float bathmos;
};

struct Record
{
    struct Student data;
    struct Record *link;
};

void readFile(struct Student array[]);

void insert(struct Student person, struct Record *hash_array[]);
int search_element(char key [], struct Record *hash_array[]);
void remove_record(char key [], struct Record *hash_array[]);
void show(struct Record *hash_array[]);
int hash_function(char key []);

int main()
{
    struct Record *hash_array[20];
    struct Student array[20];
    int count, option;
    char key[20];

    for(count = 0; count <= MAX - 1; count++)
      {
            hash_array[count] = NULL;
      }

    readFile(array);

    for(count = 0; count <17; count++)
      {
            insert(array[count],hash_array);
      }


    while (1)
    {
        printf("1. Search for a Record\n");
        printf("2. Delete a Record\n");
        printf("3. Show Hash Table\n");
        printf("4. Quit\n");
        printf("Enter your option\n");
        scanf("%d", &option);
        switch (option)
        {

        case 1:
            printf("Enter the element to search:\t");
            scanf("%s", &key);
            count = search_element(key, hash_array);
            if (count == -1)
            {
                printf("Element Not Found\n");
            }
            else
            {
                printf("Element Found in Chain:\t%d\n", count);
            }
            break;
        case 2:
            printf("Enter the element to delete:\t");
            scanf("%s", &key);
            remove_record(key, hash_array);
            break;
        case 3:
            show(hash_array);
            break;
        case 4:
            exit(1);
        }
    }
    return 0;
}
void readFile(struct Student array[])
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

void insert(struct Student person, struct Record *hash_array[])
{
    int h;
    char key[256];
    struct Record *temp;
    strcpy(key, person.am);
    if (search_element(key, hash_array) != -1)
    {
        printf("Duplicate Key\n");
        return;
    }
    h = hash_function(key);
    temp = malloc(sizeof(struct Record));
    temp->data = person;
    temp->link = hash_array[h];
    hash_array[h] = temp;
}

void show(struct Record *hash_array[])
{
    int count;
    struct Record *ptr;
    for (count = 0; count < MAX; count++)
    {
        printf("\n[%3d]", count);
        if (hash_array[count] != NULL)
        {
            ptr = hash_array[count];
            while (ptr != NULL)
            {
                printf("%s %s %f\t", ptr->data.am, ptr->data.name, ptr->data.bathmos);
                ptr = ptr->link;
            }
        }
    }
    printf("\n");
}

int search_element(char key[], struct Record *hash_array[])
{
    int h;
    struct Record *ptr;
    h = hash_function(key);
    ptr = hash_array[h];
    while (ptr != NULL)
    {
        if (strcmp(ptr->data.am , key)==0)
        {
            return h;
        }
        ptr = ptr->link;
    }
    return -1;
}

void remove_record(char key [], struct Record *hash_array[])
{
    int h;
    struct Record *temp, *ptr;
    h = hash_function(key);
    if (hash_array[h] == NULL)
    {
        printf("Key %s Not Found\n", key);
        return;
    }
    if (strcmp(hash_array[h]->data.am,key)==0)
    {
        temp = hash_array[h];
        hash_array[h] = hash_array[h]->link;
        free(temp);
        return;
    }
    ptr = hash_array[h];
    while (ptr->link != NULL)
    {
        if (strcmp(ptr->link->data.am , key)==0)
        {
            temp = ptr->link;
            ptr->link = temp->link;
            free(temp);
            return;
        }
        ptr = ptr->link;
    }
    printf("Key %d Not Found\n", key);
}

int hash_function(char key[])
{
    int i,num=0;
    for(i=0; i<8; i++){
        num = num + (int)key[i];
    }
    return num%11;
}
