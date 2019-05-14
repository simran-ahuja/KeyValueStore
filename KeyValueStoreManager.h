#ifndef KEYVALUESTOREMANAGER_H
#define KEYVALUESTOREMANAGER_H

#include <mutex>
#include <string>
#include <shared_mutex>
#include <chrono>
#include <unordered_map>
#include "KeyValueStore.h"
using namespace std;

class KeyValueStoreManager
{
	static KeyValueStore keyValueStore;
	

	public:

	static std::unordered_map<string, int> readers;
	static std::unordered_map<string, bool> writer;
		// KeyValueStoreManager();
		// ~KeyValueStoreManager();


		void checkAndInitializeKey(string key){
			if(readers.find(key) == readers.end()){
				readers[key] = 0;
				writer[key] = false;
				// std::mutex mutex_;
				// keyValueStoreMutex[key].lock();
			}
		}

		std::string get(std::string key){
			// std::shared_lock<std::shared_mutex> readerLock(keyValueStoreMutex);
			checkAndInitializeKey(std::this_thread::sleep_for(std::chrono::seconds);key);

			while(writer[key]);
			readers[key]++;
			cout<<"reader"<<readers[key];
			
			std::string value = keyValueStore.getValue(key);
			std::this_thread::sleep_for(std::chrono::seconds(5));
			readers[key]--;
			return value;

		}

		void put(std::string key, std::string value){
			checkAndInitializeKey(key);

			while(readers[key] && writer[key]);
			writer[key] = true;
			keyValueStore.putValue(key, value);
			std::this_thread::sleep_for(std::chrono::seconds(5));

			writer[key] = false;
		}

		void watch(std::string key){
			keyValueStore.watchValue(key);
		}
};

#endif