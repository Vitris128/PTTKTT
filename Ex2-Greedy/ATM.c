#include <stdio.h>
typedef int keyType;
typedef struct Tien
{
    int MG, PA;
    char TenTien[25];
}Tien;

void swapPosition(Tien* a, Tien* b) {
    Tien temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

void insertionSort(Tien A[], int n) {
    int i,j;
    for(i=1;i<n;i++) {
        j=i;
        while(j>0 && A[j].MG > A[j-1].MG)  {
            swapPosition(&A[j], &A[j-1]);
            j--;
        }
    }
}

void  readFile(Tien A[], int *n) {
    FILE* fptr = fopen("ATM.txt", "r");
    *n=0;
    int i=0;
    if(fptr==NULL) {
        printf("Loi mo file!");
        return;
    }
    while(!feof(fptr)) {
        fscanf(fptr,"%d %[^\n]" , &A[i].MG, A[i].TenTien);
        A[i++].PA = 0;
    }
    *n=i;
    fclose(fptr);
}
void Greedy(Tien A[],int n,  int sotien) {
    int i = 0;
    insertionSort(A, n);
    while(i<n && sotien>0) {
        A[i].PA = sotien/A[i].MG;
        sotien = sotien-A[i].PA*A[i].MG;
        i++;
    } 
}

int main() {
    Tien A[10];
    int i, n;
    readFile(A, &n);
    int sotien = 0;
    printf("--- Nhap so tien can rut: \n");
    scanf("%d", &sotien);
    
    Greedy(A, n, sotien);
    int sum = 0;
    for(i=0;i<n;i++) {
        if(A[i].PA!=0) sum+=A[i].PA;
    }
    printf("--- Tong so to tien: %d\n", sum);
    printf("--- Danh sach tien va so to phai chi tra: \n");
    for(i=0;i<n;i++) {
        if(A[i].PA!=0)
            printf("%d: %s. So luong: %d\n", A[i].MG, A[i].TenTien, A[i].PA);
    }
    return 0;
}