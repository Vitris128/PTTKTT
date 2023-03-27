#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int n, stat;
    printf("n = ");
    scanf("%d", &n);
    pid = vfork();
    int childrenPID=0;
    if(pid<0) {
        printf("\n Unable to create child process!\n");
        exit(EXIT_FAILURE);
    }
    else if(pid ==0) {
        childrenPID=getpid();
        printf("PID's P2: %d\n", childrenPID);
        int i;
        printf("--- Multiplicationtable ---\n");
        for(i=1;i<=10;i++) {
            printf("%d x %d = %d\n",n,i, n*i);
        }
        exit(EXIT_SUCCESS);
    }
    else {
        printf("PID's P2 - Child of P1: %d\n", pid);
        printf("Exit status: %d\n", WEXITSTATUS(waitpid(pid, &stat, 0)));
    }
    return EXIT_SUCCESS;

}
