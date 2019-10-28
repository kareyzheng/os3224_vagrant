#include "types.h"
#include "user.h"


int main(){
    int proc[20];
    int i, j, schedWait;
    int wtime, rtime, iotime, status;
    int wSum, rSum, tSum;

    wSum = rSum = tSum = 0;

    for(i=0; i<20; ++i) {
        proc[i] = fork();
        if(proc[i] > 0) continue;
        if(proc[i] == -1){
            printf(1, "Uh Oh...Failed to fork!");
            exit();
        }
        for(j = 0; j < 99999999; j++){}   // Some delay
        exit();
    }

    while((schedWait = wait_stat(&wtime, &rtime, &iotime, &status)) != -1){
        for(i = 0; i < 20; ++i){
            if(status == proc[i]){
                printf(1, "Child Process %d (pid: %d):\t", i, proc[i]);
                printf(1, "Wait Time: %d,\tRuntime: %d,\tTurnaround Time: %d\n", wtime, rtime, wtime + rtime+ iotime);
                break;
            }
        }
        wSum += wtime;
        rSum += rtime;
        tSum += (wtime + rtime + iotime);
    }
    
    printf(1, "Avg waiting time is %d.\n", wSum / 20 );
    printf(1, "Avg runtime is %d.\n", rSum / 20);
    printf(1, "Avg turnaround time is %d.\n", tSum / 20);
    exit();
}
