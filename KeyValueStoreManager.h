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
	// mutable std::shared_timed_mutex keyValueStoreMutex;
	std::unordered_map<string, std::mutex> keyValueStoreMutex;
	

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
			checkAndInitializeKey(key);

			while(writer[key]);
			keyValueStoreMutex[key].lock();
			readers[key]++;
			std::string value = keyValueStore.getValue(key);
			this_thread::sleep_for(chrono::milliseconds(900));
			readers[key]--;
			if(!readers[key])
				keyValueStoreMutex[key].unlock();
			return value;

		}

		void put(std::string key, std::string value){
			checkAndInitializeKey(key);

			while(readers[key] && writer[key]);
			keyValueStoreMutex[key].lock();
			writer[key] = true;
			keyValueStore.putValue(key, value);
			this_thread::sleep_for(chrono::milliseconds(900));
			writer[key] = false;
			keyValueStoreMutex[key].unlock();
		}

		void watch(std::string key){
			keyValueStore.watchValue(key);
		}
};

#endif