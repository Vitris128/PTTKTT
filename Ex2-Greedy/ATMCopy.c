#include <stdio.h>
typedef struct Tien{
    int MG, PA;
    char Ten[20];
} Tien;
void swap(Tien* A, Tien* B) {
    Tien temp = (*A);
    (*A) = (*B);
    (*B) = temp;
}
void bubleSort(Tien A[], int n) {
    int i, j;
    for (i = 0; i< n - 1;i++)
        for (j = n - 1; j >= i + 1;j--)
            if(A[j].MG > A[j-1].MG)
                swap(&A[j], &A[j - 1]);
}

void Greedy(Tien A[], int n, int soTienCanRut) {
    int i=0;
    bubleSort(A, n);
    while (i < n && soTienCanRut >0) {
        A[i].PA = soTienCanRut / A[i].MG;
        soTienCanRut -= A[i].PA * A[i].MG;
        i++;
    }
}


int main() {
    FILE *fptr = fopen("ATM.txt", "r");
    Tien A[10];
    int i, n = 0;
    while(!feof(fptr)) {
        fscanf(fptr, "%d%[^\n]", &A[n].MG, &A[n].Ten);
        A[n].PA = 0;
        n++;
    }
    printf("Danh sach cac loai tien: \n");
    for (i = 0; i < n;i++)
        printf("%d: %s\n", A[i].MG, A[i].Ten);
    int sum = 0;
    int soTienCanRut = 0;
    printf("Nhap so tien can rut: \n");
    scanf("%d", &soTienCanRut);
    Greedy(A, n, soTienCanRut);
    for (i = 0; i < n;i++)
        if(A[i].PA>0) {
            printf("%d: %s. Phuong an: %d\n", A[i].MG, A[i].Ten, A[i].PA);
            sum += A[i].PA;
        }
    printf("Tong so to tien phai chi tra: %d\n", sum);
    fclose(fptr);
    return 0;
}