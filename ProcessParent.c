#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int n, stat;
    printf("n = ");
    scanf("%d", &n); // biến n để in ra bảng cửu chương n
    pid = vfork(); // tạo tiến trình con
    int childrenPID=0; // biến lưu PID của tiến trình con 
    if(pid<0) {  //pid <0 thì không thể tạo tiến trình con
        printf("\n Unable to create child process!\n");
        exit(EXIT_FAILURE); //kết thúc tiến trình cha khi không thể tạo tiến trình con
    }
    else if(pid ==0) {  //pid=0 thì đã tạo tiến trình con thành công
        childrenPID=getpid(); //lấy số tiến trình của tiến trình con
        printf("PID's P2: %d\n", childrenPID); //in PID của tiến trình con
        int i;
        printf("--- Multiplicationtable ---\n"); //In bảng cửu chương n
        for(i=1;i<=10;i++) {                    
            printf("%d x %d = %d\n",n,i, n*i);
        }
        exit(EXIT_SUCCESS); //Kết thúc tiến trình con
    }
    else {
        printf("PID's P2 - Child of P1: %d\n", pid); // in PID của tiến trình con từ tiến trình cha
        printf("Exit status: %d\n", WEXITSTATUS(waitpid(pid, &stat, 0))); //WEXITSTATUS trả về trạng thái kết thúc của tiến trình con, hàm waitpid đợi tiến trình pid( tiến trình con) kết thúc
    }
    return EXIT_SUCCESS; //kết thúc tiến trình cha

}
