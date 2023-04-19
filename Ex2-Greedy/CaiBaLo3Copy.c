#include <stdio.h>
#include <malloc.h>
typedef struct {
    int PA;
    float TL, GT, DG;
    char ten[20];
} DoVat;

void swap(DoVat* A, DoVat* B) {
    DoVat temp = (*A);
    (*A) =(*B);
    (*B) = temp;
}
void BubleSort(DoVat dsdv[], int n) {
    int i, j;
    for (i = 0; i < n - 1;i++)
        for (j = n - 1; j >= i + 1;j--)
            if(dsdv[j].DG > dsdv[j-1].DG)
                swap(&dsdv[j], &dsdv[j - 1]);
}

DoVat* ReadFile(int* n, float* W) {
    FILE *fptr = fopen("CaiBaLo3.txt", "r");
    fscanf(fptr, "%f", W);
    DoVat *dsdv;
    int i = 0;
    dsdv = (DoVat *)malloc(sizeof(DoVat));
    while(!feof(fptr)) {
        fscanf(fptr, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].ten);
        dsdv[i].PA = 0;
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        i++;
        dsdv = realloc(dsdv, sizeof(DoVat) * (i + 1));
    }
    *n = i;
    fclose(fptr);
    return dsdv;
}
void INDSDV(DoVat dsdv[], int n, float W) {
    int i;
    float TongTL = 0, TongGT = 0;
    printf("Giai bai toan cai ba lo 3, phuong phap Greedy: \n");
    printf("Trong luong balo: %-9.2f\n", W);
    printf("|STT|   Ten Do Vat    | T Luong | Gia Tri | Don Gia | Phuong An |\n");
    for (i = 0; i < n;i++) {
        printf("|%2d |%-17s|%6.2f   |%6.2f   |%6.2f   |%6d     |\n",
                i + 1, dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
        TongGT += dsdv[i].GT * dsdv[i].PA;
        TongTL += dsdv[i].TL * dsdv[i].PA;
    }
    printf("Phuong an giai bai toan (theo thu tu DG giam dan): X(");
    for (i = 0; i < n-1;i++)
        printf("%d, ", dsdv[i].PA);
    printf("%d)\n", dsdv[i].PA);
    printf("Tong trong luong cua balo: %-9.2f\n", TongTL);
    printf("Tong gia tri cua balo: %-9.2f\n", TongGT);
}

void Greedy(DoVat* dsdv, int n, int W) {
    int i;
    for (i = 0; i < n;i++) {
        dsdv[i].PA = W / dsdv[i].TL;
        if(dsdv[i].PA > 1)
            dsdv[i].PA = 1;
        W -= dsdv[i].PA * dsdv[i].TL;
    }
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