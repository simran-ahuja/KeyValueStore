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
		}
	
		std::string getValue(std::string key){
			if(keyPair.find(key) == keyPair.end())
				std::cout << "Error: Key not found!\n";
			else
				return keyPair[key];
			return "Error: Key not found!";
		}
};

#endif