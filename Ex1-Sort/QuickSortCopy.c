#include <stdio.h>

typedef struct {
    int key;
    float otherkey;
} Record;

void swap(Record* A, Record* B) {
    Record temp = (*A);
    (*A) = (*B);
    (*B) = temp;
}

int findPivot(Record A[], int i, int j) {
    int keytype = A[i].key;
    int k = i + 1;
    while(k<=j && A[k].key == keytype)
        k++;
    if(k>j)
        return -1;
    if(A[k].key > keytype)
        return k;
    return i;
}

int Partition(Record A[], int i, int j, int Pivot) {
    int L = i, R = j;
    while(L<=R) {
        while(A[L].key < Pivot)
            L++;
        while(A[R].key >= Pivot)
            R--;
        if(L < R)
            swap(&A[L], &A[R]);
    }
    return L;
}

void QuickSort(Record A[], int i, int j) {
    int PivotIndex = findPivot(A, i, j);
    if(PivotIndex != -1) {
        int Pivot = A[PivotIndex].key;
        int k = Partition(A, i, j, Pivot);
        QuickSort(A, i, k - 1);
        QuickSort(A, k, j);
    }
}
void printData(Record A[], int n) {
    int i;
    for (i = 0; i < n;i++)
        printf("%3d %5d %8.2f\n", i, A[i].key, A[i].otherkey);
}

int main() {
    FILE *fptr = fopen("data.txt", "r");
    int n=0;
    Record A[20];
    while(!feof(fptr)) {
        fscanf(fptr, "%d%f", &A[n].key, &A[n].otherkey);
        n++;
    }
    printf("Quick Sort\n");
    printf("Before Sort\n");
    printData(A, n);
    QuickSort(A, 0, n);
    printf("After Sort\n");
    printData(A, n);
    fclose(fptr);
    return 0;
}