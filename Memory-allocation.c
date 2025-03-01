 *******Source Code********
 #include <stdio.h>

 #define MAX_BLOCKS 10
 #define MAX_PROCESSES 10
 
 // Function to implement First Fit
 void firstFit(int blocks[], int m, int processes[], int n) {
     int allocation[n];
     for (int i = 0; i < n; i++)
         allocation[i] = -1;
 
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
             if (blocks[j] >= processes[i]) {
                 allocation[i] = j;
                 blocks[j] -= processes[i];
                 break;
             }
         }
     }
 
     printf("\nFirst Fit Allocation:\n");
     for (int i = 0; i < n; i++) {
         printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
     }
 }
 
 // Function to implement Best Fit
 void bestFit(int blocks[], int m, int processes[], int n) {
     int allocation[n];
     for (int i = 0; i < n; i++)
         allocation[i] = -1;
 
     for (int i = 0; i < n; i++) {
         int bestIdx = -1;
         for (int j = 0; j < m; j++) {
             if (blocks[j] >= processes[i]) {
                 if (bestIdx == -1 || blocks[j] < blocks[bestIdx]) {
                     bestIdx = j;
                 }
             }
         }
         if (bestIdx != -1) {
             allocation[i] = bestIdx;
             blocks[bestIdx] -= processes[i];
         }
     }
 
     printf("\nBest Fit Allocation:\n");
     for (int i = 0; i < n; i++) {
         printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
     }
 }
 
 // Function to implement Worst Fit
 void worstFit(int blocks[], int m, int processes[], int n) {
     int allocation[n];
     for (int i = 0; i < n; i++)
         allocation[i] = -1;
 
     for (int i = 0; i < n; i++) {
         int worstIdx = -1;
         for (int j = 0; j < m; j++) {
             if (blocks[j] >= processes[i]) {
                 if (worstIdx == -1 || blocks[j] > blocks[worstIdx]) {
                     worstIdx = j;
                 }
             }
         }
         if (worstIdx != -1) {
             allocation[i] = worstIdx;
             blocks[worstIdx] -= processes[i];
         }
     }
 
     printf("\nWorst Fit Allocation:\n");
     for (int i = 0; i < n; i++) {
         printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
     }
 }
 
 // Main function
 int main() {
     int blocks[MAX_BLOCKS], processes[MAX_PROCESSES];
     int m, n;
 
     printf("Enter number of memory blocks: ");
     scanf("%d", &m);
     printf("Enter sizes of memory blocks: ");
     for (int i = 0; i < m; i++)
         scanf("%d", &blocks[i]);
 
     printf("Enter number of processes: ");
     scanf("%d", &n);
     printf("Enter sizes of processes: ");
     for (int i = 0; i < n; i++)
         scanf("%d", &processes[i]);
 
     // Preserve the original block sizes for all methods
     int blocksCopy[MAX_BLOCKS];
 
     for (int i = 0; i < m; i++) blocksCopy[i] = blocks[i];
     firstFit(blocksCopy, m, processes, n);
 
     for (int i = 0; i < m; i++) blocksCopy[i] = blocks[i];
     bestFit(blocksCopy, m, processes, n);
 
     for (int i = 0; i < m; i++) blocksCopy[i] = blocks[i];
     worstFit(blocksCopy, m, processes, n);
 
     return 0;
 }
 
 
 ****Output*****
 Enter number of memory blocks: 5
Enter sizes of memory blocks: 100 500 200 300 600
Enter number of processes: 4
Enter sizes of processes: 212 417 112 426

First Fit Allocation:
Process 1 -> Block 2
Process 2 -> Block 5
Process 3 -> Block 2
Process 4 -> Block 0

Best Fit Allocation:
Process 1 -> Block 4
Process 2 -> Block 2
Process 3 -> Block 3
Process 4 -> Block 5

Worst Fit Allocation:
Process 1 -> Block 5
Process 2 -> Block 2
Process 3 -> Block 5
Process 4 -> Block 0