#include "../src/include/Parser.h"

class ParserTest{
	Parser parser;
	BadInputException badInputException;

	void parseGetCommandWithOneArguementsTest(){
		std::vector<std::string> functionParameters;
		std::string command = "get TEST_KEY";
		std::string exceptionMessage =  parser.parseInput(command, functionParameters);
		
		std::cout << "\nparseGetCommandWithOneArguementsTest: " << ((exceptionMessage == "") ? "passed\n" 
		: "failed\n") << std::endl;
	}

	void parseGetCommandWithMoreThanOneArguementsTest(){
		std::vector<std::string> functionParameters;
		std::string command = "get INPUT1 INPUT2";
		std::string exceptionMessage =  parser.parseInput(command, functionParameters);
		std::cout << "parseGetCommandWithMoreThanOneArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed\n" : "failed\n") << std::endl;
	}

	void parsePutCommandWithTwoArguementsTest(){
		std::vector<std::string> functionParameters; 
		std::string command = "put TEST_KEY TEST_VALUE";
		std::string exceptionMessage =  parser.parseInput(command, functionParameters);
		
		std::cout << "parsePutCommandWithTwoArguementsTest: " << ((exceptionMessage == "" ) ? "passed\n" 
		: "failed\n") << std::endl;
	}

	void parsePutCommandWithMoreThanTwoArguementsTest(){
		std::vector<std::string> functionParameters;
		std::string command = "put STRING1 STRING2 STRING3";
		std::string exceptionMessage =  parser.parseInput(command, functionParameters);
		std::cout << "parsePutCommandWithMoreThanTwoArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed\n" : "failed\n") << std::endl;
	}

	void parseAnyCommandWithLessThanOneArguementsTest(){
		std::vector<std::string> functionParameters; 
		std::string command = "get";
		std::string exceptionMessage =  parser.parseInput(command, functionParameters);
		std::cout << "parseAnyCommandWithLessThanOneArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed\n" : "failed\n") << std::endl;
	}

	void parseAnyCommandWithMoreThreeArguementsTest(){
		std::vector<std::string> functionParameters;
		std::string command = "watch STRING1 STRING2 STRING3 ...";
		std::string exceptionMessage =  parser.parseInput(command, functionParameters);
		std::cout << "parseAnyCommandWithMoreThanOThreeArguementsTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed\n" : "failed\n") << std::endl;
	}

	void parseSomeRandomMessageTest(){
		std::vector<std::string> functionParameters;
		std::string command = "SOME RANDOM MESSAGE";
		std::string exceptionMessage =  parser.parseInput(command, functionParameters);
		std::cout << "parseSomeRandomMessageTest: " << 
		((exceptionMessage == "Bad Input Exception occured!" ) ? "passed\n" : "failed\n") << std::endl;
	}

	public:
		void run(){
			parseGetCommandWithOneArguementsTest();
			parseGetCommandWithMoreThanOneArguementsTest();
			parsePutCommandWithTwoArguementsTest();
			parsePutCommandWithMoreThanTwoArguementsTest();
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