// Online C compiler to run C program online
#include <stdio.h>
void Display_Sorted_Array(int arr[], int len);
void Reverse_Array(int arr[], int len);
void BubbleSort(int arr[], int len);
void InsertionSort (int arr[], int len);
void SelectionSort(int arr[], int len);
void QuickSort(int arr[], int len);
void swap(int arr[], int i, int j);
void QuickSort_Recursion(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void MergeSort(int arr[], int len);
void Merge(int arr[], int low, int mid, int high);
void MergeSort_Recursion(int arr[], int low, int high);

int main() {
    // Write C code here
    int array[] = {5,2,7,8,3,1,6,4};
    BubbleSort(array, 8);
    InsertionSort(array, 8);
    QuickSort(array, 8);
    MergeSort(array, 8);
    SelectionSort(array, 8);
    return 0;
}

void Display_Sorted_Array(int arr[], int len)
{
    for(int i = 0; i < len; i++)
    {
        printf(" %d  ",arr[i]);
    }
}

void Reverse_Array(int arr[], int len)
{
    printf("\n\tReversing the array\n");
    for(int i = len -1; i >= 0; i--)
    {
        printf(" %d  ",arr[i]);
    }
}

void BubbleSort(int arr[], int len)
{
    for(int i =0; i< len; i++)
    {
        for(int j =0; j < (len -1); j++)
        {
            if(arr[j] > arr[j +1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("\t\t  Bubble Sort \n");
    Display_Sorted_Array(arr, len);

}

void InsertionSort (int arr[], int len)
{
    for(int i = 1; i < len; i++)
    {
        int key = arr[i];
        int j = i - 1;
        
        while(i >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j +1]  =  key;
    }
    printf("\n\t\tInsertion Sort \n");
    Display_Sorted_Array(arr, len);
}
void swaping(int a[], int b[], int i, int j)
{
    int temp = a[i];
    a[i] = b[j];
    b[j] = temp;
}

void SelectionSort (int arr[], int len)
{
    for(int i = 0;i < len - 1; i++)
    {
        int min_pos = i;
        for(int j = i+1; j < len; j++)
        {
            if(arr[j] < arr[min_pos])
            {
                min_pos = j;
            }
        }
        swaping(arr, arr, i, min_pos);
    }
    printf("\n\t\tSelection Sort \n");
    Display_Sorted_Array(arr, len);
}

void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void QuickSort(int arr[], int len)
{
    printf("\n\t\t  Quick Sort \n");
    QuickSort_Recursion(arr, 0, len -1);
    Display_Sorted_Array(arr, len);
    
}
void QuickSort_Recursion(int arr[], int low, int high)
{
    if(low < high)
    {
        int pivot_index = partition(arr, low, high);
        QuickSort_Recursion(arr, low, pivot_index -1);
        QuickSort_Recursion(arr, pivot_index+1, high);
    }
}
int partition(int arr[], int low, int high)
{
    int pivot_value = arr[high];
    int i = low -1;
    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot_value)
        {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i+1, high);
    return i+1;
}

void Merge(int arr[], int low, int mid, int high)
{
    int n1 = mid - low +1;
    int n2 = high - mid;
    int temp1[n1];
    int temp2[n2];
    // printf("\n\nOR here");
    for(int i = 0; i <n1; i++)
    {
        temp1[i] = arr[low + i];
    }
    for(int i = 0; i <n2; i++)
    {
        temp2[i] = arr[mid + 1 +i];
    }
    int i = 0, j = 0, k = low;
    while(i <n1 && j <n2)
    {
        if(temp1[i] < temp2[j])
        {
            arr[k] = temp1[i];
            i++;
        }
        else
        {
            arr[k] = temp2[j];
            j++;
        }
        k++;
    }
    while(i <n1)
    {
        arr[k] = temp1[i];
        k++; i++;
    }
    while(j <n2)
    {
        arr[k] = temp2[j];
        j++; k++;
    }
}
void MergeSort_Recursion(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = (low+high)/2;
        MergeSort_Recursion(arr, low, mid);
        MergeSort_Recursion(arr, mid+1, high);
        Merge(arr, low, mid, high);
    }
}

void MergeSort(int arr[], int len)
{
    printf("\n\t\t  Merge Sort \n");
    MergeSort_Recursion(arr, 0, len -1);
    Display_Sorted_Array(arr, len);
}
