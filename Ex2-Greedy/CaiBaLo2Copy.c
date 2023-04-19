#include <stdio.h>
#include <malloc.h>

typedef struct DoVat{
    float DG,TL,GT;
    int PA,SL;
    char ten[20];
}DoVat;

void swap(DoVat *A, DoVat* B) {
    DoVat temp = (*A);
    (*A) = (*B);
    (*B) = temp;
}

void BubleSort(DoVat dsdv[], int n) {
    int i,j;
    for (i = 0; i < n - 1;i++)
        for (j = n - 1; j >= i + 1;j--)
            if(dsdv[j].DG > dsdv[j-1].DG)
                swap(&dsdv[j], &dsdv[j - 1]);
}

DoVat* ReadFile(int* n, float *W) {
    FILE *fptr = fopen("CaiBaLo2.txt", "r");
    fscanf(fptr, "%f", W);
    DoVat *dsdv;
    dsdv = (DoVat *)malloc(sizeof(DoVat));
    int i = 0;
    while(!feof(fptr)) {
        fscanf(fptr, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].ten);
        dsdv[i].PA = 0;
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        i++;
        dsdv = (DoVat *)realloc(dsdv, sizeof(DoVat) * (i + 1));
    }
    *n = i;
    fclose(fptr);
    return dsdv;
}

Greedy(DoVat dsdv[], int n, float W) {
    int i;
    for (i = 0; i < n;i++) {
        dsdv[i].PA = W / dsdv[i].TL;
        if(dsdv[i].PA > dsdv[i].SL)
            dsdv[i].PA = dsdv[i].SL;
        W -= dsdv[i].PA * dsdv[i].TL;
    }
}
void INDSDV(DoVat *dsdv, int n, float W) {
    float TongTL = 0, TongGT = 0;
    int i;
    printf("\nGiai bai toan cai ba lo 2 su dung Greedy:\n");
    printf("\nTrong luong balo: %-9.2f\n", W);
    printf("|STT|  Ten Do Vat    |T Luong|Gia Tri|So Luong|Don Gia| Phuong an |\n");
    for (i = 0; i < n;i++) {
        printf("|%2d |%-18s|%7.2f|%7.2f|%8d|%7.2f|%6d     |\n",
        i+1,dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].DG, dsdv[i].PA);
        TongGT += dsdv[i].PA * dsdv[i].GT;
        TongTL += dsdv[i].PA * dsdv[i].TL;
    }
    printf("Phuong an cua bai toan: X(");
    for (i = 0; i < n-1;i++) {
        printf("%d, ", dsdv[i].PA);
    }
    printf("%d)\n", dsdv[i].PA);

    printf("Tong trong luong cua balo: %-9.2f\n", TongTL);
    printf("Tong gia tri cua balo: %-9.2f\n", TongGT);
}

int main() {
    DoVat *dsdv;
    int n;
    float W;
    dsdv = ReadFile(&n, &W);
    BubleSort(dsdv, n);
    Greedy(dsdv, n, W);
    INDSDV(dsdv, n, W);
    free(dsdv);
    return 0;
}