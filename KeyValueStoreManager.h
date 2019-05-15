#ifndef KEYVALUESTOREMANAGER_H
#define KEYVALUESTOREMANAGER_H

#include <mutex>
#include <string>
#include <shared_mutex>
#include <chrono>
#include <unordered_map>
#include "KeyValueStore.h"


class KeyValueStoreManager
{
	static KeyValueStore keyValueStore;
	

	public:

	static std::unordered_map<std::string, int> readers;
	static std::unordered_map<std::string, bool> writer;
		// KeyValueStoreManager();
		// ~KeyValueStoreManager();


		void checkAndInitializeKey(std::string key){
			if(readers.find(key) == readers.end()){
				readers[key] = 0;
				writer[key] = false;
				// std::mutex mutex_;
				// keyValueStoreMutex[key].lock();
			}
		}

		std::string get(std::string key){
			// std::shared_lock<std::shared_mutex> readerLock(keyValueStoreMutex);
			std::cout<<key<<"***";
			checkAndInitializeKey(key);

			while(writer[key]);
			readers[key]++;
			std:: cout<<"reader"<<readers[key] <<"   ..";
			
			std::string value = keyValueStore.getValue(key);

			std::cout<<"value read";
			// std::this_thread::sleep_for(std::chrono::seconds(5));
			readers[key]--;
			return value;

		}

		void put(std::string key, std::string value){
			std::cout<<key<<" "<<value<<" **";
			checkAndInitializeKey(key);

			while(readers[key] && writer[key]);
			writer[key] = true;
			keyValueStore.putValue(key, value);
			// std::this_thread::sleep_for(std::chrono::seconds(5));

			writer[key] = false;
		}

		std::string run(std::vector<std::string> command){
			std::cout<< command[0] <<command[1]<<command[2];
			if(command[0] == "get")
				return get(command[1]);
			else if(command[0] == "put")
				put(command[0], command[1]);
			return "";
		}

		// void watch(std::string key){
		// 	keyValueStore.watchValue(key);
		// }
};

#endif