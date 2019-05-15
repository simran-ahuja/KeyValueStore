#include <iostream>
#include "../src/include/ClientServerUtilities.h"

class ClientServerUtilitiesTest{
	bool isValidWatchCommandForSomeRandomCommandTest(){
		std::string command = "wSOME RANDOM COMMAND";
		char returnCommand[1024];
		std::string key;
		int commandLength = command.length();
		return (!client::isValidWatchCommand(command, returnCommand, key, commandLength));
	}

	bool isValidWatchCommandWithMultipleArguementsTest(){
		std::string command = "watch INPUT1 INPUT2";
		char returnCommand[1024];
		std::string key;
		int commandLength = command.length();
		return (!client::isValidWatchCommand(command, returnCommand, key, commandLength));
	}

	bool isValidWatchCommandWithNoArguementsTest(){
		std::string command = "watch ";
		char returnCommand[1024];
		std::string key;
		int commandLength = command.length();
		return (!client::isValidWatchCommand(command, returnCommand, key, commandLength));
	}

	bool isValidWatchCommandWithCorrectArguementsTest(){
		std::string command = "watch TEST_KEY";
		char returnCommand[1024];
		std::string key;
		int commandLength = command.length();
		return (client::isValidWatchCommand(command, returnCommand, key, commandLength) 
			&& key == "TEST_KEY");
	}

	bool getClientOutputTest(){
		std::string message = "SOME RANDOM MESSAGE";
		char expectedOutput[1024];
		char clientOutput[1024];

		memset(expectedOutput, '0', sizeof(expectedOutput));
		strcpy(expectedOutput, message.c_str());
		server::getClientOutput(message, clientOutput);

		return !strcmp(expectedOutput, clientOutput);
	}

	public:
		void run(){
			std::cout << "\nisValidWatchCommandForSomeRandomCommandTest: " << 
				(isValidWatchCommandForSomeRandomCommandTest() ? "passed\n" :
				"failed\n") << std::endl;

			std::cout << "isValidWatchCommandWithMultipleArguementsTest: " << 
				(isValidWatchCommandWithMultipleArguementsTest() ? "passed\n" :
				"failed\n") << std::endl;

			std::cout << "isValidWatchCommandWithNoArguementsTest: " << 
				(isValidWatchCommandWithNoArguementsTest() ? "passed\n" :
				"failed\n") << std::endl;

			std::cout << "isValidWatchCommandWithCorrectArguementsTest: " << 
				(isValidWatchCommandWithCorrectArguementsTest() ? "passed\n" :
				"failed\n") << std::endl;

			std::cout << "getClientOutputTest: " << (getClientOutputTest() ? 
				"passed\n" : "failed\n") << std::endl;
		}
};

int main(){
	ClientServerUtilitiesTest clientServerUtilitiesTest;
	clientServerUtilitiesTest.run();
	return 0;
}