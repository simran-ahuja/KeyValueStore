#ifndef CLIENTSERVERUTILITIES_H
#define CLIENTSERVERUTILITIES_H

#include <string> 

namespace client{
    bool isValidWatchCommand(std::string command, char (&returnCommand)[1024], std::string &key, int commandLength){
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


        memset(returnCommand, '0' ,sizeof(char) * 1024);

        returnCommand[0] = 'g';
        returnCommand[1] = 'e';
        returnCommand[2] = 't';
        returnCommand[3] = ' ';
        i = 4;

        for(int j = 0; j < key.length(); j++){
            returnCommand[i] = (char)key[j];
            i++;
        }
        if(i < 1024)
            returnCommand[i] = '\0';

        return returnCommand;
    }

    void arguementToCommandParser(int argc, char** argv, char (&dataReceived)[1024], int &commandLength){
	    int j =0;
	    for(int i = 0; i < argc && j < 1024; ++i){
	        // printf("%s%d%d\n",argv[i],i,argc);
	        // (argv[i][k] != ' ' || argv[i][k] != '\n' || argv[i][k] != '\0'
	        if(i != 0){
	            for(int k = 0; argv[i][k] != '\0' && j < 1024; ++k){
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
	void getClientOutput(std::string outputMessage, char (&clientOutput)[1024]){
		memset(clientOutput, '0', sizeof(clientOutput));
		int n = outputMessage.length();
		int i;
		for(i = 0; i < n ; i++)
			clientOutput[i] = (char)outputMessage[i];
		clientOutput[i] = '\0';
	} 
};


#endif