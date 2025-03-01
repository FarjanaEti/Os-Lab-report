*****Source code************
#include <stdio.h>

struct Process {
    int pid;          
    int burstTime;    
    int arrivalTime;  
    int priority;     
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int isCompleted;  // Flag to check if process is completed
};

// Function to find the next process to be executed
int findNextProcess(struct Process proc[], int n, int currentTime) {
    int index = -1;
    int highestPriority = 100000;  // Set to a large number (low priority)

    for (int i = 0; i < n; i++) {
        if (proc[i].arrivalTime <= currentTime && proc[i].isCompleted == 0) {
            if (proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                index = i;
            } else if (proc[i].priority == highestPriority && proc[i].arrivalTime < proc[index].arrivalTime) {
                // If priorities are equal, choose the one with earlier arrival time
                index = i;
            }
        }
    }
    return index;
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int index = findNextProcess(proc, n, currentTime);

        if (index != -1) {
            proc[index].completionTime = currentTime + proc[index].burstTime;
            proc[index].turnaroundTime = proc[index].completionTime - proc[index].arrivalTime;
            proc[index].waitingTime = proc[index].turnaroundTime - proc[index].burstTime;
            proc[index].isCompleted = 1;
            completed++;
            currentTime = proc[index].completionTime;
        } else {
            currentTime++;
        }
    }
}

void printProcessDetails(struct Process proc[], int n) {
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nPID\tPriority\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].priority, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d\n", i + 1);
        proc[i].pid =i + 1;
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &proc[i].burstTime);
        printf("Priority (lower number means higher priority): ");
        scanf("%d", &proc[i].priority);
        proc[i].isCompleted = 0;
    }

    // Calculate waiting and turnaround times
    calculateTimes(proc, n);

    // Print process details
    printProcessDetails(proc, n);

    return 0;
}

****Output*******
Enter the number of processes: 4

Enter details for process 1
Arrival Time: 0
Burst Time: 5
Priority (lower number means higher priority): 3

Enter details for process 2
Arrival Time: 2
Burst Time: 4
Priority (lower number means higher priority): 2

Enter details for process 3
Arrival Time:
2
Burst Time: 3
Priority (lower number means higher priority): 4

Enter details for process 4
Arrival Time: 4
Burst Time: 4
Priority (lower number means higher priority): 1

PID     Priority        Arrival Time    Burst Time      Waiting Time    Turnaround Time
1       3               0               5               0               5
2       2               2               4               7               11
3       4               2               3               11              14
4       1               4               4               1               5

Average Waiting Time: 4.75
Average Turnaround Time: 8.75