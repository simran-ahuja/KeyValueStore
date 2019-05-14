#include <thread>
#include "KeyValueStoreManager.h"

// int KeyValueStoreManager::readers = 0;
// int KeyValueStoreManager::writer = 0;
KeyValueStore KeyValueStoreManager::keyValueStore = *(new KeyValueStore());

void foo(std::string s) {
	KeyValueStoreManager k1;	
	// k1 = new KeyValueStoreManager();
	std::cout<<k1.get("1");
	// std::cout<<1;
}

int main(){
	KeyValueStoreManager k1;
	// k1.put("1", "AA");
	// std::cout<<k2.get("1");

	// std::thread writer1(k1.put("1","AA"), );
	// std::thread w1(&KeyValueStoreManager::put, ("1","AA"));
	// std::string s ="1";
	// std::thread w1(foo,s);
	// std::thread w2(foo,"2");
	
	// std::thread r1(k1.put,"2","ab");
	// w1.join();
	// std::thread writer2([]{k1.put("2","AB"); });
	// std::cout << (std::thread reader1([]{k2.get("1"); }));

	return 0;
}


// #include "ReadWriteLock.h"

// int m =0;
// int read const(){
// 	l.readLock();
// 	std::cout << "inside read\n";	
// 	l.readUnlock();
// }

// void write(){
// 	l.writeLock();
// 	std::cout<<"inside write";
// 	m++;
// 	l.writeUnlock();
// }

// int main(){

// }