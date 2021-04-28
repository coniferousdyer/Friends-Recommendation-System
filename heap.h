#ifndef HEAP_H
#define HEAP_H

void MinHeapify(int A[], int heapSize, int i);
void Insert(int A[], int *heapSize, int elem);
void Delete(int A[], int *heapSize);

#endif