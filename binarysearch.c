#include "binarysearch.h"

int SearchValue(int A[], int n, int value)
{
    int beg = 0, end = n - 1, mid;

    while (beg <= end)
    {
        mid = beg + (end - beg) / 2;

        if (A[mid] == value)
            return mid;
        else if (A[mid] > value)
            end = mid - 1;
        else if (A[mid] < value)
            beg = mid + 1;
    }

    return -1;
}

int SearchPosition(int A[], int n, int value)
{
    int beg = 0, end = n - 1, mid;

    while (beg <= end)
    {
        mid = beg + (end - beg) / 2;

        if (mid > 0 && A[mid] > value && A[mid - 1] < value)
            return mid;
        else if (beg == 0 && end == 0)
            return 0;
        else if (beg == n - 1 && end == n - 1)
            return n;
        else if (A[mid] < value)
            beg = mid + 1;
        else if (A[mid] > value)
            end = mid - 1;
    }
}

int BinarySearch(int fList[], int idB, int first, int last)
{
    int middle = (first + last) / 2;
    while (first <= last)
    {
        if (fList[middle] < idB)
            first = middle + 1;
        else if (fList[middle] == idB)
        {
            return 1;
        }
        else
            last = middle - 1;

        middle = (first + last) / 2;
    }
    return 0;
}
