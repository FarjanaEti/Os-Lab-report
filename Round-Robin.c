*****Source code****
#include <stdio.h>

void roundRobinScheduling(int processes[], int n, int burst_time[], int quantum) {
    int remaining_time[n];
    int waiting_time[n], turnaround_time[n];
    int time = 0, done = 0;

    // Copy burst times into remaining times
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        waiting_time[i] = 0;
    }

    // Execute processes in a round-robin manner
    while (done != n) {
        done = 0;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - burst_time[i];
                    remaining_time[i] = 0;
                    done++;
                }
            } else {
                done++;
            }
        }
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    // Print results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Calculate average waiting time and turnaround time
    float avg_wait = 0, avg_turn = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += waiting_time[i];
        avg_turn += turnaround_time[i];
    }
    avg_wait /= n;
    avg_turn /= n;

    printf("\nAverage Waiting Time: %.2f", avg_wait);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turn);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobinScheduling(processes, n, burst_time, quantum);

    return 0;
}



******Output*******
Enter the number of processes: 5
Enter burst time for process 1: 8
Enter burst time for process 2: 3
Enter burst time for process 3: 2
Enter burst time for process 4: 1
Enter burst time for process 5: 4
Enter the time quantum: 1

Process Burst Time      Waiting Time    Turnaround Time
1       8               10              18
2       3               8               11
3       2               6               8
4       1               3               4
5       4               10              14