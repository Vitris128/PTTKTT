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

void insertionSort(recordType record[], int n) {
    int i,j;
    for(i=1;i<n;i++) {
        j=i;
        while(j>0 && record[j].key < record[j-1].key)  {
            swapPosition(&record[j], &record[j-1]);
            j--;
        }
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

    insertionSort(record, n);

    printf("\n---After sorting---\n");
    for(i=0;i<n;i++) {
        printf("%4d %.2f\n", record[i].key, record[i].otherFields);
    }


    fclose(fptr);
    return 0;
}