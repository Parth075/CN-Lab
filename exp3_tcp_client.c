#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT (10000 + 257)   // Replace PRN with your PRN value
#define BUF_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server;
    char buffer[BUF_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Prepare server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;   // connects to this same machine

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    while (1)
    {
        printf("Enter message: ");

        // Stop on end of input (Ctrl+D)
        if (fgets(buffer, BUF_SIZE, stdin) == NULL)
            break;

        send(sock, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUF_SIZE);

        // Stop if the server closed the connection
        int bytes = read(sock, buffer, BUF_SIZE - 1);
        if (bytes <= 0)
            break;

        printf("Echo from server: %s", buffer);
    }

    close(sock);

    return 0;
}
