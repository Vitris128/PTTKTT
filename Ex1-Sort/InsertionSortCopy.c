#include <stdio.h>

typedef struct Record
{
    int key;
    float otherkey;
}Record;


void swap(Record* A, Record* B) {
    Record temp = (*A);
    (*A) = (*B);
    (*B) = temp;
}

void InsertionSort(Record A[], int n) {
    int i,j;
    for (i = 0; i < n;i++) {
        j = i;
        while(j>0 && A[j].key < A[j-1].key ) {
            swap(&A[j], &A[j - 1]);
            j--;
        }
            
    }
}


void printData(Record A[], int n) {
    int i;
    for (i = 0; i < n;i++)
        printf("%3d %5d %8.2f\n", i, A[i].key, A[i].otherkey);
}

int main() {
    int n = 0;
    Record A[20];
    FILE *fptr = fopen("data.txt", "r");
    while(!feof(fptr)) {
        fscanf(fptr, "%d%f", &A[n].key, &A[n].otherkey);
        n++;
    }
    printf("Insertion Sort\n");
    printf("Before Sort\n");
    printData(A, n);
    InsertionSort(A, n);
    printf("After Sort\n");
    printData(A, n);

}