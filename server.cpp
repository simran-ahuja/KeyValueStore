#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <thread>
#include "Parser.h"
#include "ClientServerUtilities.h"

namespace server{
    std::string parse(std::string command){
        Parser parser;
        std::string outputMessage = parser.parseInput(command);
        printf("%s\n", outputMessage.c_str());
        // return server::getClientOutput(outputMessage, clientOutput);
        return outputMessage;
    }
}; 
std::unordered_map<int, bool> clients;
void clientHandler(int clientId) {
    char dataSending[1025];
    int n=read(clientId, dataSending, sizeof(dataSending)-1);
    printf("%d\n",n);
    printf("%s\n", dataSending);
    std::string command(dataSending);
    command = command.substr(0,n);

    char clientOutput[1024];
    std::string outputMessage = server::parse(command);
    int m = send(clientId, outputMessage.c_str(), 1024*sizeof(char), 0);
    while(1);
    close(clientId);
    clients[clientId]=false;
}

int main(int argc, char const *argv[])
{
    time_t clock;
    char dataSending[1025];
    int clintListn = 0;
    struct sockaddr_in ipOfServer;
    clintListn = socket(AF_INET, SOCK_STREAM, 0);
    memset(&ipOfServer, '0', sizeof(ipOfServer));
    memset(dataSending, '0', sizeof(dataSending));
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(9097);
    bind(clintListn, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
    listen(clintListn , 20);
    std::vector<std::thread> threads;
    while(1)
    {
        printf("\n\nHi,Iam running server.Some Client hit me\n"); 
        int clintConnt = accept(clintListn, (struct sockaddr*)NULL, NULL);
        printf("connected to client id: %d\n", clintConnt);
        clients[clintConnt] = true;
        // int n=read(clintConnt, dataSending, sizeof(dataSending)-1);
        // printf("%d\n",n);
        // printf("%s\n", dataSending);
        // std::string command(dataSending);
        // command = command.substr(0,n);

        // char clientOutput[1024];
        // // std::string x = (std::thread Thread(server::parse, command.substr(0,n)));
        // // server::getClientOutput(x, clientOutput);
        // // int m = send(clintConnt, clientOutput, sizeof(clientOutput), 0);
        threads.push_back(std::thread(clientHandler, clintConnt));
        
        // std::string outputMessage = server::parse(command);
        // server::getClientOutput(outputMessage, clientOutput);
        // int m = send(clintConnt, outputMessage.c_str(), 1024*sizeof(char), 0);

        // // while((n = read(clintListn, dataSending, sizeof(dataSending)-1)) > 0)
        // // {
        // //     printf("1\n");
        // //     dataSending[n] = 0;
        // //     if(fputs(dataSending, stdout) == EOF)
        // //     {
        // //         printf("\nStandard output error");
        // //     }
     
        // //     printf("\n");
        // // }

        // // clock = time(NULL);
        // // snprintf(dataSending, sizeof(dataSending), "%.24s\r\n", ctime(&clock)); // Printing successful message
        // // write(clintConnt, dataSending, strlen(dataSending));
            
     }
 
     return 0;
}