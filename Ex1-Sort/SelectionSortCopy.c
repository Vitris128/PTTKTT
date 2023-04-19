#include <stdio.h>

typedef struct record{
    int key;
    float otherkey;
} record;

void swap(record* A, record* B) {
    record temp = (*A);
    (*A) = (*B);
    (*B) = temp;
}

void SelectionSort(record A[], int n) {
    int i, j;
    for (i = 0; i < n;i++)
        for (j = 0; j < n-1 ;j++)
            if(A[j].key > A[i].key)
                swap(&A[j], &A[i]);
}

void printData(record A[], int n) {
    int i;
    for (i = 0; i < n;i++)
        printf("%3d %5d %8.2f\n", i, A[i].key, A[i].otherkey);
}


int main() {
    printf("Selection Sort\n");
    record A[20];
    int n = 0;
    FILE *fptr = fopen("data.txt", "r");
    while(!feof(fptr)) {
        fscanf(fptr, "%d%f", &A[n].key, &A[n].otherkey);
        n++;
    }
    printf("Before Sort\n");
    printData(A, n);
    SelectionSort(A, n);
    printf("After Sort\n");
    printData(A, n);
    fclose(fptr);
}