/*
 ============================================================================
 Name        : MyClient_DateTime.c
 Author      : Alexander Meade
 Version     :
 Copyright   : Your copyright notice
 ================================
 Description
 ================================
 This client code can connect to server and receive date and time from server.
1. Since this communication is through socket, we need to create socket.
2. Port number of the process and IP address both bundled in a structure. We connect these with socket.
3. Once sockets are connected, the server sends the date and time to client socket through clients socket descriptor.
================================
Compile and Run Instruction
================================
1- Copy MyClient.c in the folder where you copied the server
2- Open Command Prompt
3- cd to the folder you in step 1
4- Type bash.exe
5- Type gcc MyClient.c -o client
6- Type ./client
7- If success, you should see date and time of the day!
 ============================================================================
 */


#include <stdio.h> // standard input and output library
#include <stdlib.h> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <errno.h> //It defines macros for reporting and retrieving error conditions through error codes
#include <time.h> //contains various functions for manipulating date and time
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses


int main()
{
    int socket_descriptor = 0, n = 0;
    char dataReceived[1024];
    struct sockaddr_in ipOfServer;

    memset(dataReceived, '0' ,sizeof(dataReceived));

    /*
    //Socket() function to create a new socket socket_descriptor, returning an integer which is used as socket descriptor.
    //For IP4 address we are sending first parameter as AF_INET.
    //Use SOCK_STREAM for the socket type (2nd parameter)
    //Use the number zero for the default protocol (3rd parameter)
    //socket() returning an integer for your error checking. Print errors.
     */
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_descriptor < 0)
            {
              perror ("Unable to Connect to Server");
              exit (EXIT_FAILURE);
            }



    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(2017);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");

    /*
    //Connect() function to connect to new socket socket_descriptor,
     //returning an integer for your error checking. Print errors.
    */
    // To Do   (your code goes here)
    socklen_t addrSize= sizeof(ipOfServer);
    //proper function connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    n = connect(socket_descriptor, (struct sockaddr *) &ipOfServer, addrSize);
    	if (n < 0)
                {
                  perror ("Unable to Connect to Server");
                  exit (EXIT_FAILURE);
                }



    while((n = read(socket_descriptor, dataReceived, sizeof(dataReceived)-1)) > 0)
    {
        dataReceived[n] = 0;
        if(fputs(dataReceived, stdout) == EOF)
        {
            printf("\nStandard output error");
        }

        printf("\n");
    }

    if( n < 0)
    {
        printf("Standard input error \n");
    }

    return 0;
}
