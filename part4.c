#include<stdio.h>
#define MAX_N 100

typedef struct{
    int id;
    int arv_time;
    int CPU_time;
    int CPU_time_less;
    int Turn_Arr_time, Res_time, Wait_time;
}Process;
typedef Process ElementType;
typedef struct{
    int front, rear;
    ElementType A[MAX_N];
}Queue;
void makenullQueue(Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}
void enQueue(Queue *pQ, ElementType x){
    pQ->A[++pQ->rear] = x;
}
void deQueue(Queue *pQ){
    pQ->front++;
}
ElementType front(Queue Q){
    return Q.A[Q.front];
}
int empty(Queue Q){
    return Q.front > Q.rear;
}
void set_process(Process P[], int n){
    for(int i = 0; i < n ; i++){
        P[i].CPU_time_less = P[i].CPU_time;
        P[i].Turn_Arr_time = 0;
        P[i].Res_time = -1;
        P[i].Wait_time = 0;
    }
}
int total_time(Process P[], int n){
    int sum = 0;
    if(P[0].arv_time > 0)
        sum += P[0].arv_time;
    for(int i = 0; i < n - 1 ; i++){
        int tmp = sum + P[i].CPU_time;
        if(tmp < P[i+1].arv_time)
        sum += (P[i+1].arv_time - tmp);
        sum += P[i].CPU_time;
    }
    return sum + P[n-1].CPU_time;
}
void sort_process(Process P[], int n){
    for(int i = 0; i < n-1; i++)
        for(int j = i + 1; j < n; j++)
            if(P[i].arv_time > P[j].arv_time ){
                Process tmp = P[i];
                P[i] = P[j];
                P[j] = tmp;
            }
}
void print_all_proc(int Gantt[], Process P[], int n, int time_in_total){
    int avrw = 0, avrt = 0, avrr = 0;
    for(int i = 0; i < n; i++)
        P[i].CPU_time_less = P[i].CPU_time;
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < time_in_total; j++){
            if(P[i].id != Gantt[j]){
                if(P[i].arv_time > j ){
                    printf("-");
                }
                else{
                    if(P[i].CPU_time_less > 0)
                    printf("W");
                    else
                    printf("-");
                }
            }
            else{
                printf("R");
                P[i].CPU_time_less--;
            }
        }
        printf("\n");
        avrw += P[i].Wait_time;
        avrt += P[i].Turn_Arr_time;
        avrr += P[i].Res_time;
    }
    printf("AVGW = %.2f", (1.0*avrw)/n);
    printf("\tAVGR = %.2f", (1.0*avrr)/n);
    printf("\tAVRT = %.2f", (1.0*avrt)/n);
printf("\n");
}
void WRA_time_counting(int Gantt[], Process P[], int time_in_total, int n){
    set_process(P, n);
    for(int i = 0; i < time_in_total; i++){
        for(int j = 0; j < n; j++){
        if(P[j].id != Gantt[i]){
            if(P[j].arv_time > i )
                continue;
            else if(P[j].CPU_time_less > 0){
                P[j].Wait_time++;
                P[j].Turn_Arr_time++;
            }
        }
        else{
                if(P[j].Res_time == -1 && i > P[j].Res_time)
                P[j].Res_time = i - P[j].arv_time;
                P[j].Turn_Arr_time++;
                P[j].CPU_time_less--;
            }
        }
    }
}
void FCFS(int Gantt[], Process P[], int fst_in, int time_in_total, int n){
    for(int i = 0; i < fst_in; i++)
        Gantt[i] = 0;
    set_process(P, n);
    int idx = 0;
    for(int i = fst_in; i < time_in_total; i++){
        if(P[idx].arv_time > i)
            Gantt[i] = 0;
        else{
            Gantt[i] = P[idx].id;
            P[idx].CPU_time_less --;
            if(P[idx].CPU_time_less == 0)
            idx++;
        }
    }
    WRA_time_counting(Gantt, P, time_in_total, n);
}
void SJF_preemtive(int Gantt[], Process P[], int fst_in, int time_in_total, int n){
    for(int i = 0; i < fst_in; i++)
        Gantt[i] = 0;
    set_process(P, n);
    int time = fst_in;
    while(time < time_in_total){
        Process tmp;
        for(int i = 0; i < n; i++)
            if(P[i].CPU_time_less != 0){
                tmp = P[i];
                break;
            }
        while(tmp.arv_time > time){
            Gantt[time++] = 0;
        }
        for(int i = 0; i < n; i++){
            if(P[i].arv_time > time || P[i].CPU_time_less == 0)
                continue;
            else{
                if(tmp.CPU_time_less > P[i].CPU_time_less)
                tmp = P[i];
            }
        }
        for(int i = 0; i < n; i++)
            if(P[i].id == tmp.id){
                Gantt[time++] = P[i].id;
        P[i].CPU_time_less--;
        }
    }
    WRA_time_counting(Gantt, P, time_in_total, n);
}
void Round_Robin(int Gantt[], Process P[], int fst_in, int time_in_total, int n, int q){
    for(int i = 0; i < fst_in; i++)
        Gantt[i] = 0;
    set_process(P, n);
    int time = fst_in;
    Queue Q;
    makenullQueue(&Q);
    for(int i = 0; i < n; i++)
        enQueue(&Q, P[i]);
    while(!empty(Q)){
        Process tmp = front(Q);
        deQueue(&Q);
        while(tmp.arv_time > time){
            Gantt[time++] = 0;
        }
        if(tmp.CPU_time_less <= q){
            for(int i = 0; i < tmp.CPU_time_less; i++)
            Gantt[time++] = tmp.id;
            tmp.CPU_time_less = 0;
        }
        else{
            for(int i = 0; i < q; i++)
            Gantt[time++] = tmp.id;
            tmp.CPU_time_less -= q;
            enQueue(&Q, tmp);
        }
    }
    WRA_time_counting(Gantt, P, time_in_total, n);
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    Process P[n];
    for(int i = 0; i < n ; i++){
    int arv_t, CPU_t;
    scanf("%d%d", &arv_t, &CPU_t);
    P[i].id = i + 1;
    P[i].arv_time = arv_t;
    P[i].CPU_time = CPU_t;
    }

    int min_arv = P[0].arv_time;
    sort_process(P, n);
    int time_in_total = total_time(P,n);
    int Gantt[time_in_total];
    printf("***********************************\n");
    FCFS(Gantt, P, min_arv, time_in_total, n);
    printf("Dinh thoi FCFS\n");
    print_all_proc(Gantt, P, n, time_in_total);
    printf("***********************************\n");
    printf("Dinh thoi SJF preemtive\n");
    SJF_preemtive(Gantt, P, min_arv, time_in_total, n);
    print_all_proc(Gantt, P, n, time_in_total);
    printf("***********************************\n");
    Round_Robin(Gantt, P, min_arv, time_in_total, n, q);
    printf("Dinh thoi Round Robin\n");
    print_all_proc(Gantt, P, n, time_in_total);
    return 0;
}
