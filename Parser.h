#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>

class BadInputException: public std::exception
{
	virtual const char* what() const throw()
	{
    	return "Bad Input Exception occured!";
	}
};

class Parser{ 
	std::vector<std::string> splitStringBySpace(std::string command) 
	{ 
	    std::istringstream iStringStream(command); 
	    std::vector<std::string> functionParameters;
	    do { 
	        std::string parameter; 
	        iStringStream >> parameter; 

	        // std:: cout<< parameter <<"..\n";
	  		if(parameter.length() !=0 && parameter != " ")
	        	functionParameters.push_back(parameter);
	    } while (iStringStream); 

	    return functionParameters;
	} 

	public:
		std::string parseInput(std::string command, std::vector<std::string> &functionParameters){
			std::cout<<command<<"\n";
			BadInputException ex;
			functionParameters = splitStringBySpace(command);
			int noOfParameters = functionParameters.size();

			// for(int i =0 ; i<functionParameters.size();i++)
				// std::cout<<functionParameters[i]<<".."<<noOfParameters<<"..";
			try{
				if(noOfParameters == 2){
					if(functionParameters[0] == "put"){
						std::cout << "2 arguements expected with PUT command." << 
							"Please check and retry!" << std::endl;
						throw ex;
					}
					else if(functionParameters[0] == "get")
						return "";
						// return keyValueStoreManager.get(functionParameters[1]);
					// else if(functionParameters[0] == "watch")
					// 	keyValueStoreManager.watch(functionParameters[1]);
					else{
						std::cout << "Invalid command! Please check and retry!" << std::endl;
						throw ex;
					}
				}
				else if(noOfParameters == 3){
					if(functionParameters[0] == "put")
						return "";
						// keyValueStoreManager.put(functionParameters[1], functionParameters[2]);

					else{
						std::cout << "Invalid command! Please check and retry!" << std::endl;
						throw ex;
					}
				}else {
					std::cout << "Invalid command! Please check and retry!" << std::endl;
					throw ex;
				}

			}catch(std::exception &e){
				return e.what();
			}

			return "";
		}

};
 

#endif