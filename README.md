# simple-tcp
A simple TCP client-server created to run in Minix 3.

## How it Works
In order to run the program, you must first start the server. Once the server is running, it is listening on a port that I enter as an argument. You can then run the client on the same port that the server is listening to. Once the client connects, it sends a message to the server and waits for the server to respond. The server immediately responds after accepting the message and sends the message defined in the exercise. The program terminates the client once this message is received, but the server remains functional so that another client can connect. 

To run the server: `cc server.c -w && ./a.out <PORT #>`

To run the client: `cc client.c -w && ./a.out <PORT #>`
