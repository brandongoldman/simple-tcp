#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, pid;
     struct sockaddr_in serv_addr, cli_addr;

     // Check to make sure PORT is supplied as argument
     if (argc < 2) {
         fprintf(stderr,"Please enter a port!\n");
         exit(1);
     }
     
     // Create socket for network connection
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     bzero((char *) &serv_addr, sizeof(serv_addr));

     // Obtain port number from console argument
     portno = atoi(argv[1]);

     // Code found in Linux MAN page reference
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     // Catch error if sockets cannot bind
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
         printf("Binding unsuccessful...");
         exit(1);
     }

     // Otherwise, server is running (wait for client to connect)
     listen(sockfd, 5); // we can have up to five connections (1 works just fine here)
     clilen = sizeof(cli_addr);

     // Keep server running so that more than one client can connect
     while (1) {
         // Accept Client entering port
         newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

         // Create a parent process and child process to handle message passing
         // I could have used pipes, but forking makes it easy.
         pid = fork();
         if (pid == 0)  {
             close(sockfd);
             
             int n;
             char message[256];
             
             // Clear buffer, and read message from client
             bzero(message,256);
             n = read(newsockfd, message, 255);    // reads <NAME> : <UFID>
             printf("%s\n", message);             // and stores in buffer

             // Write message to client
             n = write(newsockfd,"Welcome to the server running on MINIX", 38);

             // Message is now passed to client
             exit(0);
         }
         else close(newsockfd);
     } 
     return 0; 
}
