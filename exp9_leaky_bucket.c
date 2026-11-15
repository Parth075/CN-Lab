#include <stdio.h>

int main() {
    int bucket_size, n, i, incoming, outgoing, stored = 0;

    printf("Leaky Bucket Algorithm Simulation\n");
    printf("Enter bucket size (capacity): ");
    if (scanf("%d", &bucket_size) != 1 || bucket_size <= 0) {
        printf("Invalid bucket size.\n");
        return 1;
    }

    printf("Enter outgoing rate: ");
    if (scanf("%d", &outgoing) != 1 || outgoing <= 0) {
        printf("Invalid outgoing rate.\n");
        return 1;
    }

    printf("Enter number of packets (time units): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid number of time units.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nTime unit %d:\n", i + 1);
        printf("Enter number of incoming packets: ");
        if (scanf("%d", &incoming) != 1 || incoming < 0) {
            printf("Invalid number of packets.\n");
            return 1;
        }

        if (incoming + stored > bucket_size) {
            printf("Bucket overflow! Packet loss = %d\n", incoming + stored - bucket_size);
            stored = bucket_size;
        } else {
            stored += incoming;
        }

        if (stored <= outgoing) {
            printf("Packets sent: %d\n", stored);
            stored = 0;
        } else {
            printf("Packets sent: %d\n", outgoing);
            stored -= outgoing;
        }

        printf("Packets remaining in bucket: %d\n", stored);
    }

    // Drain remaining packets
    while (stored > 0) {
        printf("\nDraining remaining packets...\n");
        if (stored <= outgoing) {
            printf("Packets sent: %d\n", stored);
            stored = 0;
        } else {
            printf("Packets sent: %d\n", outgoing);
            stored -= outgoing;
        }
        printf("Packets left in bucket: %d\n", stored);
    }

    printf("\nSimulation complete.\n");
    return 0;
}
