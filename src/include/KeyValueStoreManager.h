#ifndef KEYVALUESTOREMANAGER_H
#define KEYVALUESTOREMANAGER_H

#include <string>
#include <unordered_map>
#include "KeyValueStore.h"


class KeyValueStoreManager
{
	static KeyValueStore keyValueStore;
	

	public:

	static std::unordered_map<std::string, int> readers;
	static std::unordered_map<std::string, bool> writer;

		void checkAndInitializeKey(std::string key){
			if(readers.find(key) == readers.end()){
				readers[key] = 0;
				writer[key] = false;
			}
		}

		std::string get(std::string key){

			checkAndInitializeKey(key);

			while(writer[key]);
			readers[key]++;
			std::cout << "Fetching value for " << readers[key] << std::endl;
			std::string value = keyValueStore.getValue(key);
			readers[key]--;
			return value;

		}

		void put(std::string key, std::string value){

			checkAndInitializeKey(key);

			while(readers[key] && writer[key]);
			writer[key] = true;
			std::cout << "Putting value for " << key << std::endl;
			keyValueStore.putValue(key, value);
			writer[key] = false;
		}

};

#endif