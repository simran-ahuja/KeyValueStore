#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <unordered_map>
#include <iostream>
#include <string>

class KeyValueStore{
	std::unordered_map<std::string, std::string> keyPair;
	public:

		void putValue(std::string key, std::string value){
			keyPair[key] = value;
			//if(watching.find(key) != watching.end() && watching[key])
			//	triggerUpdate(key);
		}
	
		std::string getValue(std::string key){
			try{
				std::string value = keyPair[key];
				return value;
			}catch(std::exception &e){
				std::cout << "Error: Key not found!";
				return "";
			}
		}



		void watchValue(std::string key){
			if(keyPair.find(key) == keyPair.end()){
				std::cout << "Error: Key not found!";
				return;
			}

			std::string previousValue = keyPair[key];
			while(true){
				std::string value = getValue(key);
				if(value != previousValue)
					std::cout << "Updated Value is: " << value << std::endl;
			}
		}

};

#endif