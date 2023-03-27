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

void pushDown(recordType record[], int first, int last) {
    int r = first;
    while(r<= (last-1)/2)
        if(last==2*r+1) {
            if(record[r].key < record[last].key)
                swapPosition(&record[r], &record[last]);
                r = last;
        } else if(record[r].key < record[2*r+1].key && record[2*r+1].key >= record[2*r+2].key) {
                    swapPosition(&record[r], &record[2*r+1]);
                    r = 2*r+1;
                } else if(record[r].key < record[2*r+2].key) {
                    swapPosition(&record[r], &record[2*r+2]);
                    r =2*r+2;
                    } else
                        r=last; 

}

void heapSort(recordType record[], int n) {
    int i;
    for(i= (n-2)/2;i >=0; i--)
        pushDown(record, i, n-1);
    for(i=n-1;i>=2;i--) {
        swapPosition(&record[0], &record[i]);
        pushDown(record, 0, i-1);
    }
    swapPosition(&record[0], &record[1]);
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

    heapSort(record, n);

    printf("\n---After sorting---\n");
    for(i=0;i<n;i++) {
        printf("%4d %.2f\n", record[i].key, record[i].otherFields);
    }


    fclose(fptr);
    return 0;
}