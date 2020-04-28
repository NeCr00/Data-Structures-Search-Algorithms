#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int linearSearch (int array[], int l, int r, int key) {

    int found = 0, i = l;

    while (!found && i < r) {

        if (array[i] == key) return i;

        ++i;
    }
    return -1;
}

void Binary_Search(int array[], int size, int key)
{
    int bottom = 0, top = size - 1;
    while (bottom <= top)
    {
        int mid = (top + bottom) / 2;
        if (array[mid] == key)
        {
            //printf("To stoixeio %d vrethike sthn thesi %d \n", key, mid);
            return;
        }
        else if (array[mid] > key)
        {
            top = mid - 1;
        }
        else
        {
            bottom = mid + 1;
        }
    }
    //printf("O xarakthras %d den vrethike", key);
}

void Interpolation_Search(int array[], int size, int key)
{
    int low = 0, high = size - 1;
    while (array[high] >= key && key > array[low])
    {
        int next = low + ((key - array[low]) / (array[high] - array[low])) * (high - low);
        if (key > array[next])
        {
            low = next + 1;
        }
        else if (key < array[next])
        {
            high = next - 1;
        }
        else
        {
            low = next;
        }

        if (key == array[low])
        {
            //printf("To stoixeio %d vrethke sthn thesi %d", key, low);
            return;
        }
    }
    //printf("To stoixeio den vrethike !");
}


//========================== BIS ===================================
void search(int array[], int size, int key, int next)
{
    int i;
    printf("%d \n", next);

    for (i = 1; i <= 3; i++)
    {
        if (array[next + i] == key && next >= -3)
        {
            //printf("To stoixeio %d vrethike sthn thesi %d", key, next + i);
            return;
        }
    }

    //printf("To stoixeio den vrethike !");
}

 int bisSearch2 (int arr[], int l, int r, int key)  {
    int left    = l;
    int right   = r;
    int size = right - left;
    int next = (int) (size * ((key - arr[left])/(arr[right] - arr[left]))) + 1;
    int index = 0, n = r;

    while (key != arr[next]) {
        int i = 1;
        size = right - left;

        if (size <= 3){
            return linearSearch (arr, l, r, key);

        }



        if (key >= arr[next]) {

            while (key > arr[next + i*((int) sqrt(size)) - 1]) {
                i= i*2;
            }

            right = next + (int) (i*sqrt(size));

            left  = next + (int) ((i-1)*sqrt(size));

        }

        else if (key < arr[next]) {

            while (key < arr[next -i* ((int) sqrt(size)) + 1]) {

                i=i*2;

            }

            right = next - (int) ((i-1)*sqrt(size));

            left  = next - (int) (i*sqrt(size));

        }

        next = (int) (left + ((right - left +1)*(key - arr[left])/(arr[right] - arr[left]))) - 1;

        index++;

        if(index >n)
            break;

    }

    if (key = arr[next])

            return next;

        else return -1;

}



  int bisSearch1 (int arr[], int l, int r, int key)  {
    int left    = l;
    int right   = r;
    int size = right - left;
    int next = (int) (size * ((key - arr[left])/(arr[right] - arr[left]))) + 1;

    while (key != arr[next]) {
        int i = 0;
        size = right - left;

        if (size <= 3){
            return linearSearch (arr, l, r, key);

        }



        if (key >= arr[next]) {

            while (key > arr[next + i*((int) sqrt(size)) - 1]) {
                ++i;
            }

            right = next + (int) (i*sqrt(size));

            left  = next + (int) ((i-1)*sqrt(size));

        }

        else if (key < arr[next]) {

            while (key < arr[next -i* ((int) sqrt(size)) + 1]) {

                ++i;

            }

            right = next - (int) ((i-1)*sqrt(size));

            left  = next - (int) (i*sqrt(size));

        }

        next = (int) (left + ((right - left +1)*(key - arr[left])/(arr[right] - arr[left]))) - 1;



    }

    if (key = arr[next])

            return next;

        else return -1;

}

void Insertion_Sort(int array[], int size)
{
    int i, j;

    for (i = 1; i < size; i++)
    {
        int x = array[i];
        int j = i - 1;
        while (j >= 0 && x < array[j])
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = x;
    }
}
//===================================================================================================
int main()
{
    //=============================================
    // dhmiourgia pinaka kai tou antigrafou
     int size = 50000, array[size], index=0;
    int srchsize = 100000;

    int i,srch[srchsize];
    for (i = 0; i < size; i++)
    {
        array[i] = rand() % 5000 + 1;

    }

    for (i = 0; i < srchsize-1; i++)
    {
        srch[i] = rand() % 100 + 1;

    }


    //=============================================
    double time;
    clock_t start, end;


     start = clock();

    for(i=0; i<srchsize; i++)
    linearSearch(array,0,size,srch[i]);
    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Linear Search execution is %lf\n", time);
  //=======================================================

    Insertion_Sort(array,size);
      start = clock();


     for(i=0; i<srchsize-1; i++)
        bisSearch1(array,1,size,srch[i]);

    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of BIS1 execution is %lf\n", time);
//==========================================================
    Insertion_Sort(array,size);
    start = clock();


    for(i=0; i<srchsize-1; i++)
        bisSearch2(array,1,size,srch[i]);

    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of BIS2 execution is %lf\n", time);

//===========================================================

    Insertion_Sort(array,size);
    start = clock();

    for(i=0; i<srchsize; i++)
    Binary_Search(array, size, srch[i]);

    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Binary Search execution is %lf\n", time);
//===========================================================  
	Insertion_Sort(array,size);
    start = clock();

    for(i=0; i<srchsize; i++)
   	 Interpolation_Search(array,size ,srch[i]);

    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Interpolation Search execution is %lf\n", time);



    return 0;
}
