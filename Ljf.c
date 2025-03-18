*****Introduction********
Longest Job First (LJF) is a CPU scheduling algorithm that
 selects the process with the longest burst time for execution 
 first. It is a non-preemptive scheduling technique, meaning once
  a process starts execution, it cannot be interrupted until it 
  completes.

  *******Code***
  #include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time < processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}


void calculateTimes(struct Process processes[], int n) {
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;

        processes[i].turnaround_time = processes[i].completion_time;

        
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}


void displayResults(struct Process processes[], int n) {
    float total_tat = 0, total_wt = 0;

    printf("\nProcess | Burst Time | Completion Time | Turnaround Time | Waiting Time\n");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("  P%d    |     %d      |        %d       |        %d       |      %d\n",
               processes[i].id, processes[i].burst_time, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);

        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
}

// Main function
int main() {
    int n;

    // Get number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Get burst times
    printf("Enter the burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Sort processes based on LJF scheduling
    sortProcesses(processes, n);

    // Calculate Completion, Turnaround, and Waiting Times
    calculateTimes(processes, n);

    // Display results
    displayResults(processes, n);

    return 0;
}

****Output********
Enter the number of processes: 4
Enter the burst times for each process:
Process 1: 6
Process 2: 8
Process 3: 7
Process 4: 3

Process | Burst Time | Completion Time | Turnaround Time | Waiting Time
--------------------------------------------------------------------
  P2    |     8      |        8       |        8       |      0
  P3    |     7      |        15      |        15      |      8
  P1    |     6      |        21      |        21      |      15
  P4    |     3      |        24      |        24      |      21

Average Turnaround Time: 17.00
Average Waiting Time: 11.00