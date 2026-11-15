#include <stdio.h>

int main() {
    int bucket_size, n, rate, tokens = 0, incoming, i;

    printf("Token Bucket Algorithm Simulation\n");
    printf("Enter bucket size (capacity): ");
    if (scanf("%d", &bucket_size) != 1 || bucket_size <= 0) {
        printf("Invalid bucket size.\n");
        return 1;
    }

    printf("Enter token generation rate: ");
    if (scanf("%d", &rate) != 1 || rate < 0) {
        printf("Invalid token rate.\n");
        return 1;
    }

    printf("Enter number of packets (time units): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid number of time units.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nTime unit %d:\n", i + 1);

        tokens += rate;
        if (tokens > bucket_size) {
            tokens = bucket_size;
        }

        printf("Enter number of packets to send: ");
        if (scanf("%d", &incoming) != 1 || incoming < 0) {
            printf("Invalid number of packets.\n");
            return 1;
        }

        if (tokens >= incoming) {
            printf("Packets sent: %d\n", incoming);
            tokens -= incoming;
        } else {
            printf("Only %d tokens available, packets sent: %d, packets dropped: %d\n",
                   tokens, tokens, incoming - tokens);
            tokens = 0;
        }

        printf("Tokens left: %d\n", tokens);
    }

    printf("\nSimulation complete.\n");
    return 0;
}
