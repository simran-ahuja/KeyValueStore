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
#include "ClientServerUtilities.h"

int main(int argc, char** argv)
{
    int CreateSocket = 0,n = 0;
    char dataReceived[1024];
    struct sockaddr_in ipOfServer;
 
    memset(dataReceived, '0' ,sizeof(dataReceived));
 
    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }
 
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(9095);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }
 
    // while((n = read(CreateSocket, dataReceived, sizeof(dataReceived)-1)) > 0)
    // {
    //     dataReceived[n] = 0;
    //     if(fputs(dataReceived, stdout) == EOF)
    //     {
    //         printf("\nStandard output error");
    //     }
 
    //     printf("\n");
    // }


    // strcpy(dataReceived, "test");
    printf("\n%s\n\n",dataReceived );
       
    char returnCommand[1024];
    int commandLength;

    client::arguementToCommandParser(argc, argv, dataReceived, commandLength);

    std::string key = "";
    std::string command(dataReceived);
    int m = 0;
    if(dataReceived[0] == 'w'
     && client::isValidWatchCommand(command, returnCommand, key, std::min(commandLength, 1024))){
            char value[1024];
            n  = send(CreateSocket, returnCommand,sizeof(returnCommand),0);
            m = read(CreateSocket, value, sizeof(value));
            printf("%s\n", value);
        while(1){
            char newValue[1024];
            // std::this_thread::sleep_for (std::chrono::seconds(1));
            n = send(CreateSocket, returnCommand, sizeof(returnCommand),0);
            m = read(CreateSocket, newValue, sizeof(newValue));
            printf("%s\n", newValue);
            if(!(std::strcmp(value, newValue))){
                printf("New value of %s: %s\n\n", key.c_str(), newValue);
                std::strcpy(value, newValue);
            }
        }
    }else{
        char outputReceived[1024];
        n = send(CreateSocket, dataReceived, sizeof(dataReceived),0);
        m = read(CreateSocket, outputReceived, sizeof(outputReceived));
        printf("%s\n\n", outputReceived);

    } 

    if( n < 0)
    {
        printf("Standard input error \n");
        return 0;
    }


 
    return 0;
}