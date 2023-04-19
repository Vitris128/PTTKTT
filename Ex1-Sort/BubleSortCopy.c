#include <stdio.h>

typedef struct record
{
    int key;
    float data;
}record;


void swap(record* A, record* B) {
    record temp = (*A);
    (*A) = (*B);
    (*B) = temp;
}

void BubleSort(record A[], int n) {
    int i, j;
    for (i = 0; i < n - 1;i++)
        for (j = n - 1; j >= i + 1;j--)
            if(A[j].key < A[j-1].key)
                swap(&A[j], &A[j - 1]);
}

void printData(record a[], int n) {
    int i;
    for (i = 0; i < n;i++)
        printf("%3d %5d %8.2f\n", i, a[i].key, a[i].data);
}

int main() {
    printf("\n--- Buble Sort ---\n");
    FILE *fptr = fopen("data.txt", "r");
    record A[20];
    int n = 0;
    while(!feof(fptr)) {
        fscanf(fptr, "%d%f", &A[n].key, &A[n].data);
        n++;
    }
    printf("\nBefore Sort\n");
    printData(A, n);
    BubleSort(A, n);
    printf("\nAfter Sort\n");
    printData(A, n);
    fclose(fptr);
    return 0;
}