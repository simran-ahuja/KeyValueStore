#include "../src/include/KeyValueStore.h"

class KeyValueStoreTest{
	KeyValueStore keyValueStore;

	bool getValueKeyMissingTest(){
		return (keyValueStore.getValue("TEST_KEY") == "Error: Key not found!");
	}

	bool getValueKeyExistsTest(){
		keyValueStore.putValue("TEST_KEY","TEST_VALUE");
		return (keyValueStore.getValue("TEST_KEY") == "TEST_VALUE");
	}

	public:
		void run(){
			std::cout << "\nTest for GET request when Key-Value pair doesn't exists:  " << 
				(getValueKeyMissingTest() ? "Passed" : "Failed") << "\n\n";

			std::cout << "\nTest for GET request when Key-Value pair exists:  " << 
				(getValueKeyExistsTest() ? "Passed" : "Failed") << "\n\n";
		}
};

int main(){
	KeyValueStoreTest keyValueStoreTest;
	keyValueStoreTest.run();
	return 0;
}