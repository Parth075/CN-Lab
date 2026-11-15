#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 50

void sender(int frames[], int size, int window_size);
void receiver(int frames[], int start, int size, int window_size);

int main() {
    int n, window_size;
    int frames[MAX_FRAMES];

    printf("Sliding Window Protocol Simulation (Go-Back-N)\n");
    printf("Enter number of frames to send (max %d): ", MAX_FRAMES);
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n > MAX_FRAMES || n <= 0) {
        printf("Invalid number of frames.\n");
        return 0;
    }

    printf("Enter window size: ");
    if (scanf("%d", &window_size) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (window_size <= 0 || window_size > n) {
        printf("Invalid window size.\n");
        return 0;
    }

    // Fill frames with sequence numbers
    for (int i = 0; i < n; i++) {
        frames[i] = i;
    }

    sender(frames, n, window_size);

    return 0;
}

void sender(int frames[], int size, int window_size) {
    int base = 0;
    char choice;

    while (base < size) {
        printf("\nSender window: ");

        for (int i = base; i < base + window_size && i < size; i++) {
            printf("[%d] ", frames[i]);
        }

        printf("\nSending frames...\n");

        for (int i = base; i < base + window_size && i < size; i++) {
            printf("Sent frame: %d\n", frames[i]);
        }

        printf("\nSimulating receiver...\n");
        receiver(frames, base, size, window_size);

        printf("\nDid all frames receive correctly? (y/n): ");
        if (scanf(" %c", &choice) != 1) {
            printf("\nInput ended. Stopping simulation.\n");
            return;
        }

        if (choice == 'y' || choice == 'Y') {
            base += window_size;
        } else {
            printf("Resending from frame %d...\n", frames[base]);
            // In Go-Back-N, we resend from base
        }
    }

    printf("\nAll frames sent successfully!\n");
}

void receiver(int frames[], int start, int size, int window_size) {
    for (int i = start; i < start + window_size && i < size; i++) {
        printf("Received frame: %d, sending ACK: %d\n",
               frames[i], frames[i] + 1);
    }
}
