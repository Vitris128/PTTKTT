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

int partition(recordType record[], int i, int j) {
    int pivot = record[i].key;
    int L = i+1, R = j;
    while(L<=R) {
        while(L<=R && record[L].key <= pivot) L++;
        while(L<=R && record[R].key >= pivot) R--;
        if(L<R) swapPosition(&record[L], &record[R]);
    }
    swapPosition(&record[R], &record[i]);
    return R;
}
void otherQuickSort(recordType record[], int i, int j) {      
    if(i<j) {
        int p = partition(record, i, j);
        otherQuickSort(record, i, p-1);
        otherQuickSort(record, p+1, j);
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
    for(i=0;i<n;i++) {
        printf("%4d %.2f\n", record[i].key, record[i].otherFields);
    }

    otherQuickSort(record, 0, n);

    printf("\n---After sorting---\n");
    for(i=0;i<n;i++) {
        printf("%4d %.2f\n", record[i].key, record[i].otherFields);
    }


    fclose(fptr);
    return 0;
}