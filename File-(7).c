******Introduction*******
Three common file allocation techniques used in operating systems: 
Sequential Allocation, Indexed Allocation, and Linked Allocation

Sequential Allocation:

Each file is stored in a contiguous block of memory.
The starting block and length of each file are maintained.
Indexed Allocation:

Each file has an index block that stores the addresses of all allocated blocks.
This allows files to be stored non-contiguously.
Linked Allocation:

Each file is stored as linked blocks, where each block contains a pointer to the next block.
It avoids fragmentation and makes use of scattered free blocks.

******code*******
#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

// Structure for Indexed Allocation
struct IndexedFile {
    int indexBlock;
    int blockList[MAX_BLOCKS];
    int totalBlocks;
};

// Sequential Allocation
void sequentialAllocation(int files[], int n) {
    printf("\nSequential Allocation:\n");
    int startBlock = 0;
    for (int i = 0; i < n; i++) {
        printf("File %d: Starts at Block %d, Length: %d\n", i + 1, startBlock, files[i]);
        startBlock += files[i]; // Move to next available block
    }
}

// Indexed Allocation
void indexedAllocation(struct IndexedFile indexed[], int n) {
    printf("\nIndexed Allocation:\n");
    for (int i = 0; i < n; i++) {
        printf("File %d: Index Block -> %d, Blocks: ", i + 1, indexed[i].indexBlock);
        for (int j = 0; j < indexed[i].totalBlocks; j++) {
            printf("%d ", indexed[i].blockList[j]);
        }
        printf("\n");
    }
}

// Linked Allocation
void linkedAllocation(int files[], int n, int blocks[MAX_BLOCKS], int totalBlocks) {
    printf("\nLinked Allocation:\n");
    int startBlock = 0;
    for (int i = 0; i < n; i++) {
        printf("File %d: Blocks -> ", i + 1);
        int currentBlock = startBlock;
        for (int j = 0; j < files[i]; j++) {
            if (currentBlock >= totalBlocks) {
                printf("Allocation Failed (No Space)\n");
                return;
            }
            printf("%d -> ", currentBlock);
            currentBlock++;
        }
        printf("NULL\n");
        startBlock += files[i];
    }
}

// Main Function
int main() {
    int n; // Number of files
    printf("Enter the number of files: ");
    scanf("%d", &n);

    int files[n];
    printf("Enter the sizes (in blocks) of each file:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &files[i]);
    }

    // Sequential Allocation
    sequentialAllocation(files, n);

    // Indexed Allocation
    struct IndexedFile indexed[n];
    for (int i = 0; i < n; i++) {
        indexed[i].indexBlock = i * 10; // Example index block
        indexed[i].totalBlocks = files[i];
        for (int j = 0; j < files[i]; j++) {
            indexed[i].blockList[j] = (i * 10) + j + 1; // Example block allocation
        }
    }
    indexedAllocation(indexed, n);

    // Linked Allocation
    int blocks[MAX_BLOCKS] = {0}; // Simulating memory blocks
    linkedAllocation(files, n, blocks, MAX_BLOCKS);

    return 0;
}

*******Output*******
Enter the number of files: 3
Enter the sizes (in blocks) of each file:
5 3 4

Sequential Allocation:
File 1: Starts at Block 0, Length: 5
File 2: Starts at Block 5, Length: 3
File 3: Starts at Block 8, Length: 4

Indexed Allocation:
File 1: Index Block -> 0, Blocks: 1 2 3 4 5
File 2: Index Block -> 10, Blocks: 11 12 13
File 3: Index Block -> 20, Blocks: 21 22 23 24

Linked Allocation:
File 1: Blocks -> 0 -> 1 -> 2 -> 3 -> 4 -> NULL
File 2: Blocks -> 5 -> 6 -> 7 -> NULL
File 3: Blocks -> 8 -> 9 -> 10 -> 11 -> NULL
