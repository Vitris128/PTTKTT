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
