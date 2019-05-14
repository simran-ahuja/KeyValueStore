#include "KeyValueStore.h"

class KeyValueStoreTest{
	KeyValueStore keyValueStore;

	bool getValueKeyMissingTest(){
		return (keyValueStore.getValue("TEST_KEY") == "");
	}

	bool getValueKeyExistsTest(){
		keyValueStore.putValue("TEST_KEY","TEST_VALUE");
		return (keyValueStore.getValue("TEST_KEY") == "TEST_VALUE");
	}

	public:
		void run(){
			std::cout << "Test for GET request when Key-Value pair doesn't exists:  " << 
				(getValueKeyMissingTest() ? "Passed" : "Failed") << "\n";

			std::cout << "Test for GET request when Key-Value pair exists:  " << 
				(getValueKeyMissingTest() ? "Passed" : "Failed") << "\n";
		}
};

int main(){
	KeyValueStoreTest keyValueStoreTest;
	keyValueStoreTest.run();
	return 0;
}