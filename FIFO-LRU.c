******Source Code*******
_____________FIFO________
#include <stdio.h>

void fifo(int pages[], int n, int capacity) {
    int frame[capacity], front = 0, faults = 0;

    // Initialize frame slots with -1 (empty)
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault occurs
            frame[front] = pages[i]; // Replace the oldest page
            front = (front + 1) % capacity; // Move the front pointer
            faults++;
        }

        // Print the current frame status
        printf("Page %d -> Frame: ", pages[i]);
        for (int j = 0; j < capacity; j++)
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        printf("\n");
    }

    printf("Total Page Faults: %d\n", faults);
}

int main() {
    // Predefined page reference string and number of frames
    int pages[] = {3, 1, 4, 1, 2, 1, 3, 4}; // Example reference string
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3; // Number of available frames

    // Run FIFO Page Replacement Algorithm
    printf("\n--- FIFO Page Replacement Simulation ---\n");
    printf("Page Reference String: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pages[i]);
    printf("\nNumber of Frames: %d\n", capacity);

    fifo(pages, n, capacity);

    return 0;
}

__________LRU___________
#include <stdio.h>
#include <limits.h>

void lru(int pages[], int n, int capacity) {
    int frame[capacity], index[capacity], faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1; // Initialize frames to -1 (empty)

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                index[j] = i; // Update last used index
                break;
            }
        }

        if (!found) { // Page fault occurs
            int lru_index = 0, min = INT_MAX;

            // Find the least recently used page
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) { // If an empty slot is available
                    lru_index = j;
                    break;
                }
                if (index[j] < min) {
                    min = index[j];
                    lru_index = j;
                }
            }

            frame[lru_index] = pages[i];
            index[lru_index] = i;
            faults++;
        }

        // Print the current frame status
        printf("Page %d -> Frame: ", pages[i]);
        for (int j = 0; j < capacity; j++)
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        printf("\n");
    }

    printf("Total Page Faults: %d\n", faults);
}

int main() {
    // Predefined page reference string and number of frames
    int pages[] = {3, 1, 4, 1, 2, 1, 3, 4}; // Example reference string
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3; // Number of available frames

    // Run LRU Page Replacement Algorithm
    printf("\n--- LRU Page Replacement Simulation ---\n");
    printf("Page Reference String: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pages[i]);
    printf("\nNumber of Frames: %d\n", capacity);

    lru(pages, n, capacity);

    return 0;
}

*****Output********
----FIFO------
--- FIFO Page Replacement Simulation ---
Page Reference String: 3 1 4 1 2 1 3 4
Number of Frames: 3
Page 3 -> Frame: 3 - -
Page 1 -> Frame: 3 1 -
Page 4 -> Frame: 3 1 4
Page 1 -> Frame: 3 1 4
Page 2 -> Frame: 2 1 4
Page 1 -> Frame: 2 1 4
Page 3 -> Frame: 2 3 4
Page 4 -> Frame: 2 3 4
Total Page Faults: 5

-----LRU-----
--- LRU Page Replacement Simulation ---
Page Reference String: 3 1 4 1 2 1 3 4
Number of Frames: 3
Page 3 -> Frame: 3 - -
Page 1 -> Frame: 3 1 -
Page 4 -> Frame: 3 1 4
Page 1 -> Frame: 3 1 4
Page 2 -> Frame: 2 1 4
Page 1 -> Frame: 2 1 4
Page 3 -> Frame: 2 1 3
Page 4 -> Frame: 4 1 3
Total Page Faults: 6