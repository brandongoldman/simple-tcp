#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main(int argc, char *argv[])
{
    int sockfd, port, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    port = atoi(argv[1]);
    
    // The socket system call allows us to prepare our network with the ability
    // to read and write messages between a client and server.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname("localhost"); // using localhost at PORT portno 
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        printf("Cannot connect...");
    
    // Prepare string to send to server
    char message[256] = "Brandon Goldman : 4794-9349";

    // Write message to socket to send to server
    n = write(sockfd, message, strlen(message));

    // Clear the current message and retrieve message from server
    bzero(message, 256);
    n = read(sockfd, message,255);

    // Display the response from the server
    printf("%s\n", message);

    // Exit Program
    return 0;
}