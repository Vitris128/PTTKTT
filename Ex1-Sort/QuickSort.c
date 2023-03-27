#include <stdio.h>
typedef int keyType;
typedef float otherKeyType;
typedef struct recordType
{
    keyType key;
    otherKeyType otherFields;
}recordType;

void swapPosition(recordType* a, recordType* b) {
    recordType temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

int findPivot(recordType record[], int i, int j) {
    keyType firstKey;
    int k = i+1;
    firstKey = record[i].key;
    while(k<=j && record[k].key == firstKey) k++;
    if(k>j) return -1;
    if(record[k].key > firstKey) return k;
    return i; 
}

int partition(recordType record[], int i, int j, keyType pivot) {
    int L = i,R = j;
    while( L<=R) {
        while(record[L].key < pivot) L++;
        while(record[R].key >= pivot) R--;
        if(L<R) swapPosition(&record[L], &record[R]);
    }
    return L;
}
void quickSort(recordType record[], int i, int j) {      
    keyType pivot;
    int pivotIndex = findPivot(record, i,j), k;
    if(pivotIndex != -1) {
        pivot = record[pivotIndex].key;
        k = partition(record, i,j, pivot);
        quickSort(record, i, k-1);
        quickSort(record, k, j);
    }
}
void printData(recordType record[], int n) {
    int i;
    for(i=0;i<n;i++) {
        printf("%3d %5d %8.2f\n",i, record[i].key, record[i].otherFields);
    }
}

int main() {
    printf("--- Selection Sort ---\n");
    FILE* fptr = fopen("data.txt", "r");
    recordType record[20];
    int i,n=0;
    while(!feof(fptr)) {
        fscanf(fptr,"%d%f" , &record[n].key, &record[n].otherFields);
        n++;
    }
    printf("\n---Before sorting---\n");
    printData(record, n);

    quickSort(record, 0, n);

    printf("\n---After sorting---\n");
    printData(record, n);

    fclose(fptr);
    return 0;
}