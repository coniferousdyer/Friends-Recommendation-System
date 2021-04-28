#include "heap.h"

void MinHeapify(int A[], int heapSize, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    if (l < heapSize && A[l] < A[i])
        smallest = l;
    if (r < heapSize && A[r] < A[smallest])
        smallest = r;

    if (smallest != i)
    {
        int temp = A[i];
        A[i] = A[smallest];
        A[smallest] = temp;
        MinHeapify(A, heapSize, smallest);
    }
}

void Delete(int A[], int *heapSize)
{
    --(*heapSize);

    int temp = A[*heapSize];
    A[*heapSize] = A[0];
    A[0] = temp;

    MinHeapify(A, *heapSize, 0);
}

void Insert(int A[], int *heapSize, int elem)
{
    ++(*heapSize);
    A[*heapSize - 1] = elem;

    for (int i = *heapSize - 1; i >= 0 && A[i] < A[(i - 1) / 2]; i = (i - 1) / 2)
    {
        int temp = A[i];
        A[i] = A[(i - 1) / 2];
        A[(i - 1) / 2] = temp;
    }
}