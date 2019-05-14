#ifndef KEYVALUESTOREMANAGER_H
#define KEYVALUESTOREMANAGER_H

#include <mutex>
#include <string>
#include <shared_mutex>
#include "KeyValueStore.h"


class KeyValueStoreManager
{
	static KeyValueStore keyValueStore;
	// mutable std::shared_timed_mutex keyValueStoreMutex;
	std::mutex keyValueStoreMutex;
	

	public:

	static int readers;
	static int writer;
		// KeyValueStoreManager();
		// ~KeyValueStoreManager();


		std::string get(std::string key){
			// std::shared_lock<std::shared_mutex> readerLock(keyValueStoreMutex);
			while(writer);
			keyValueStoreMutex.lock();
			readers++;
			std::string value = keyValueStore.getValue(key);
			readers--;
			if(!readers)
				keyValueStoreMutex.unlock();
			return value;

		}

		void put(std::string key, std::string value){
			while(readers && writer);
			keyValueStoreMutex.lock();
			keyValueStore.putValue(key, value);
			keyValueStoreMutex.unlock();
		}

		void watch(std::string key){
			keyValueStore.watchValue(key);
		}
};

#endif