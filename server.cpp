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
#include <pthread.h>
#include <thread>
#include "Parser.h"
#include "ClientServerUtilities.h"
#include "KeyValueStoreManager.h"
#include <iostream>

std::unordered_map<std::string, int>  KeyValueStoreManager::readers;
std::unordered_map<std::string, bool> KeyValueStoreManager::writer;
KeyValueStore KeyValueStoreManager::keyValueStore = *(new KeyValueStore());


namespace server{
    std::string runCommand(std::string command){
        Parser parser;
        KeyValueStoreManager keyValueStoreManager;
        std::vector<std::string> functionParameters;
        std::string outputMessage = parser.parseInput(command, functionParameters);
        if(outputMessage == ""){
            if(functionParameters[0] == "get")
                return keyValueStoreManager.get(functionParameters[1]);
            else if(functionParameters[0] == "put")
                keyValueStoreManager.put(functionParameters[1], functionParameters[2]);
        }
        return outputMessage;
    }
}; 
std::unordered_map<int, bool> clients;
std::unordered_map<int, pthread_t> threadMap;


void clientHandler(int clientId) {
    char dataSending[1025];
    int n=read(clientId, dataSending, sizeof(dataSending)-1);
    printf("%d\n",n);
    printf("%s\n", dataSending);
    std::string command(dataSending);
    command = command.substr(0,n);

    char clientOutput[1024];
    std::string outputMessage = server::runCommand(command);
    int m = send(clientId, outputMessage.c_str(), 1024*sizeof(char), 0);
    close(clientId);
    clients[clientId]=false;
}

void stopThread(int clientId){
    if(threadMap.find(clientId) != threadMap.end()){
        pthread_cancel(threadMap[clientId]);
        threadMap.erase(clientId);
        clients.erase(clientId);
    }
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
    int PORT; scanf("%d", &PORT);
    ipOfServer.sin_port = htons(PORT);
    bind(clintListn, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
    listen(clintListn , 20);
    while(1)
    {
        printf("\n\nHi,Iam running server.Some Client hit me\n"); 
        int clintConnt = accept(clintListn, (struct sockaddr*)NULL, NULL);
        printf("connected to client id: %d\n", clintConnt);
        clients[clintConnt] = true;
        std::thread Thread = std::thread(clientHandler, clintConnt);
        Thread.detach();
        threadMap[clintConnt] = Thread.native_handle();   
        
        std::unordered_map<int, bool>::iterator itr;
        for(itr = clients.begin(); itr != clients.end(); itr++)
            if(!itr->second)
                stopThread(itr->first);

     }
     return 0;
}