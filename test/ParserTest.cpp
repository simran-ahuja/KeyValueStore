#include "Parser.h"

// std::unordered_map<std::string, int>  KeyValueStoreManager::readers;
// std::unordered_map<std::string, bool> KeyValueStoreManager::writer;
// KeyValueStore KeyValueStoreManager::keyValueStore = *(new KeyValueStore());

class ParserTest{
	Parser parser;
	BadInputException badInputException;
	KeyValueStoreManager keyValueStoreManager;

	void parseGetCommandWithOneArguementsTest(){
		std::string command = "get TEST_KEY";
		std::string exceptionMessage =  parser.parseInput(command);
		
		std::cout << "parseGetCommandWithOneArguementsTest: " << ((exceptionMessage == "" ) ? "passed" 
		: "failed") << std::endl;
	}

	void parseGetCommandWithMoreThanOneArguementsTest(){
		std::string command = "get INPUT1 INPUT2";
		std::string exceptionMessage =  parser.parseInput(command);
		std::cout << "parseGetCommandWithMoreThanOneArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed" : "failed") << std::endl;
	}

	void parsePutCommandWithTwoArguementsTest(){ 
		std::string command = "put TEST_KEY TEST_VALUE";
		std::string exceptionMessage =  parser.parseInput(command);
		
		std::cout << "parsePutCommandWithTwoArguementsTest: " << ((exceptionMessage == "" ) ? "passed" 
		: "failed") << std::endl;
	}

	void parsePutCommandWithMoreThanTwoArguementsTest(){
		std::string command = "put STRING1 STRING2 STRING3";
		std::string exceptionMessage =  parser.parseInput(command);
		std::cout << "parsePutCommandWithMoreThanTwoArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed" : "failed") << std::endl;
	}

	void parseWatchCommandWithOneArguementsTest(){ 
		std::string command = "watch TEST_KEY";
		std::string exceptionMessage =  parser.parseInput(command);
		
		std::cout << "parseWatchCommandWithOneArguementsTest: " << ((exceptionMessage == "" ) ? "passed" 
		: "failed") << std::endl;
	}

	void parseWatchCommandWithMoreThanTwoArguementsTest(){
		std::string command = "watch STRING1 STRING2 STRING3 ...";
		std::string exceptionMessage =  parser.parseInput(command);
		std::cout << "parseWatchCommandWithMoreThanTwoArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed" : "failed") << std::endl;
	}

	void parseAnyCommandWithLessThanOneArguementsTest(){ 
		std::string command = "get";
		std::string exceptionMessage =  parser.parseInput(command);
		std::cout << "parseAnyCommandWithLessThanOneArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed" : "failed") << std::endl;
	}

	void parseAnyCommandWithMoreThreeArguementsTest(){
		std::string command = "watch STRING1 STRING2 STRING3 ...";
		std::string exceptionMessage =  parser.parseInput(command);
		std::cout << "parseAnyCommandWithMoreThanOThreeArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed" : "failed") << std::endl;
	}

	void parseSomeRandomMessageTest(){
		std::string command = "SOME RANDOM MESSAGE";
		std::string exceptionMessage =  parser.parseInput(command);
		std::cout << "parseSomeRandomMessageTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed" : "failed") << std::endl;
	}

	public:
		void run(){
			parseGetCommandWithOneArguementsTest();
			parseGetCommandWithMoreThanOneArguementsTest();
			parsePutCommandWithTwoArguementsTest();
			parsePutCommandWithMoreThanTwoArguementsTest();
			// parseWatchCommandWithOneArguementsTest();
			parseWatchCommandWithMoreThanTwoArguementsTest();
			parseAnyCommandWithLessThanOneArguementsTest();
			parseAnyCommandWithMoreThreeArguementsTest();
			parseSomeRandomMessageTest();
		}

};

int main(){
	ParserTest parserTest;
	parserTest.run();
	return 0;
}