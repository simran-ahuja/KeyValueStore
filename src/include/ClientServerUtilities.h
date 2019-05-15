#ifndef CLIENTSERVERUTILITIES_H
#define CLIENTSERVERUTILITIES_H
#define PACKET_SIZE 1024

#include <string> 

namespace client{
    bool isValidWatchCommand(std::string command, char (&returnCommand)[PACKET_SIZE], std::string &key, int commandLength){
        key = "";
        char watch[6] = {'w','a','t','c','h',' '};
        for(int i = 0; i < 6; i++){
            if(command[i] != watch[i])
                return false;
        }

        int i;
        for(i = 6; i < commandLength; i++){
            if(command[i] == ' ' || command[i] == '\0')
                break;
            key += command[i];
        }
        
        if(key.length() < 1 || i < commandLength)
            return false;


        memset(returnCommand, '0' ,sizeof(char) * PACKET_SIZE);

        returnCommand[0] = 'g';
        returnCommand[1] = 'e';
        returnCommand[2] = 't';
        returnCommand[3] = ' ';
        i = 4;

        for(int j = 0; j < key.length(); j++){
            returnCommand[i] = (char)key[j];
            i++;
        }
        if(i < PACKET_SIZE)
            returnCommand[i] = '\0';

        return returnCommand;
    }

    void arguementToCommandParser(int argc, char** argv, char (&dataReceived)[PACKET_SIZE], int &commandLength){
	    int j =0;
	    for(int i = 0; i < argc && j < PACKET_SIZE; ++i){
	        if(i != 0){
	            for(int k = 0; argv[i][k] != '\0' && j < PACKET_SIZE; ++k){
	                dataReceived[j] = argv[i][k];
	                j++;
	            }
	            dataReceived[j] = ' ';
	            j++;
	        }

	    }
	    j--;
	    dataReceived[j] = '\0';
	    commandLength = j;
	    }
};

namespace server{
	void getClientOutput(std::string outputMessage, char (&clientOutput)[PACKET_SIZE]){
		memset(clientOutput, '0', sizeof(clientOutput));
		int n = outputMessage.length();
		int i;
		for(i = 0; i < n ; i++)
			clientOutput[i] = (char)outputMessage[i];
		clientOutput[i] = '\0';
	} 
};


#endif