#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void print(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d  ", array[i]);
    printf("\n");
}

void Bubble_Sort(int array[], int size)
{
    int i, j;

    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
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

void Selection_Sort(int array[], int size)
{
    int i, j, min;

    for (i = 0; i < size - 1; i++)
    {
        min = i;
        for (j = i + 1; j < size; j++)
        {
            if (array[min] > array[j])
            {
                min = j;
            }
        }
        int temp = array[min];
        array[min] = array[i];
        array[i] = temp;
    }
}

void merging(int array[], int low1, int high1, int low2, int high2)
{
	int temp[10000];
	int i, j, k;
	i = low1;
	j = low2;
	k = 0;

	while (i <= high1 && j <= high2)
	{
		if (array[i] < array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];
	}

	while (i <= high1)
		temp[k++] = array[i++];

	while (j <= high2)
		temp[k++] = array[j++];

	for (i = low1, j = 0; i <= high2; i++, j++)
		array[i] = temp[j];
}

void mergesort(int array[], int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		mergesort(array, low, mid);
		mergesort(array, mid + 1, high);
		merging(array, low, mid, mid + 1, high);
	}
	else
	{
		return;
	}
}

void QuickSort(int array[], int left, int right)
{
	int pivot, leftArrow, rightArrow;
	leftArrow = left;
	rightArrow = right;
	pivot = array[(left + right) / 2];
	do
	{
		while (array[rightArrow] > pivot)
			--rightArrow;
		while (array[leftArrow] < pivot)
			++leftArrow;
		if (leftArrow <= rightArrow)
		{
			int temp = array[leftArrow];
			array[leftArrow] = array[rightArrow];
			array[rightArrow] = temp;

			++leftArrow;
			--rightArrow;
		}
	} while (rightArrow >= leftArrow);
	if (left < rightArrow)
		QuickSort(array, left, rightArrow);
	if (leftArrow < right)
		QuickSort(array, leftArrow, right);
}

void heapsort(int array[], int size)
{
    int l = size / 2;

    if (size % 2 == 0)
    {
        l = size / 2 - 1;
    }

    int r = size - 1;
    int j, k;

    while (r >= 1)
    {
        if (l > 0)
        {
            l--;
            j = l;
        }
        else
        {
            swap(&array[0], &array[r]);
            r--;
            j = 0;
        }
        int s = array[j];

        while (2 * j <= r)
        {
            k = 2 * j;
            if (k < r && array[k] < array[k + 1])
            {

                k++;
            }
            if (s < array[k])
            {
                swap(&array[j], &array[k]);
                j = k;
            }
            else
            {

                break;
            }
        }
    }
}

int main()
{
    //=============================================
    // dhmiourgia pinaka kai tou antigrafou
    int size = 10000, array[size];
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = rand() % 1000 + 1;
    }
    int temp[size];
    memcpy(temp, array, sizeof(array));
    //=============================================
    double time;
    clock_t start, end;

    //=============Bubble Sort=========================
    start = clock();
    Bubble_Sort(temp, size);
    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Bubble Sort execution is %lf\n", time);

    memcpy(temp, array, sizeof(array));

    //=============Insertion Sort======================
    start = clock();
    Insertion_Sort(temp, size);
    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Insertion Sort execution is %lf\n", time);

    memcpy(temp, array, sizeof(array));

    //=============Selection Sort======================
    start = clock();
    Selection_Sort(temp, size);
    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Insertion Sort execution is %lf\n", time);



    memcpy(temp, array, sizeof(array));

    //==================Merge Sort===========================

    start = clock();
    mergesort(temp, 0, size - 1);
    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Merge Sort execution is %lf\n", time);
    //========================================================

    memcpy(temp, array, sizeof(array));

    //===================Quick Sort===========================
    start = clock();
    QuickSort(temp, 0, size - 1);
    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of Quick Sort execution is %lf\n", time);
    //=========================================================

    memcpy(temp, array, sizeof(array));

    //============== HeapSort ===========================
    start = clock();
    heapsort(temp, size);
    end = clock();
    time = ((double)(end - start)) / CLK_TCK;
    printf("Total time of HeapSort execution is %lf\n", time);

    return 0;
}
