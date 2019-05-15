#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/ClientServerUtilities.h"

#define PACKET_SIZE 1024

int main(int argc, char** argv)
{
    int CreateSocket = 0,n = 0;
    char dataReceived[PACKET_SIZE];
    struct sockaddr_in ipOfServer;
 
    memset(dataReceived, '0' ,sizeof(dataReceived));
 
    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }
 
    ipOfServer.sin_family = AF_INET;
    int PORT; 
    printf("Please enter the port no:\n");
    scanf("%d", &PORT);
    ipOfServer.sin_port = htons(PORT);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }
       
    char returnCommand[PACKET_SIZE];
    int commandLength;

    client::arguementToCommandParser(argc, argv, dataReceived, commandLength);

    std::string key = "";
    std::string command(dataReceived);
    int m = 0;
    if(dataReceived[0] == 'w'
     && client::isValidWatchCommand(command, returnCommand, key, std::min(commandLength, PACKET_SIZE))){
            char value[PACKET_SIZE];
            n  = send(CreateSocket, returnCommand,sizeof(returnCommand),0);
            m = read(CreateSocket, value, sizeof(value));
            printf("%s\n", value);
        while(1){
            close(CreateSocket);
            std::this_thread::sleep_for (std::chrono::seconds(1));  
            if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
            {
                printf("Socket not created \n");
                return 1;
            }
            if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
            {
                printf("Connection failed due to port and ip problems\n");
                return 1;
            }            
            char newValue[PACKET_SIZE];
            n = send(CreateSocket, returnCommand, sizeof(returnCommand),0);
            m = read(CreateSocket, newValue, sizeof(newValue));
            if(std::strcmp(value, newValue)){
                printf("\nNew value of %s: %s\n\n", key.c_str(), newValue);
                std::strcpy(value, newValue);
            }
        }
    }else{
        char outputReceived[PACKET_SIZE];
        n = send(CreateSocket, dataReceived, sizeof(dataReceived),0);
        m = read(CreateSocket, outputReceived, sizeof(outputReceived));
        printf("\n%s\n\n", outputReceived);

    } 

    if( n < 0)
    {
        printf("Standard input error \n");
        return 0;
    }
    

    close(CreateSocket);              

 
    return 0;
}