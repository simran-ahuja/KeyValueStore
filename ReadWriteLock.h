#ifndef READWRITELOCK_H
#define READWRITELOCK_H

#include <mutex>

class ReadWriteLock{
	mutex mutex_;
	conditional_variable readAvailable, writeAvailable;
	bool writeLocks = false;
	int readLocks = 0;

	public:


		int getReaders() const{
			return readLocks;
		}

		void readLock() {
			unique_lock<mutex> mutexManager(mutex_);
			while (writeLocks)
			{
				readingAvailable.wait(mutexManager);
			}
			readLocks++;
		}

		void readUnlock() {
			unique_lock<mutex> mutexManager(mutex_);
			readLocks--;
			if (readLocks == 0)
			{
				writingAvailable.notify_all();
			}
		}

		void writeLock() {
			unique_lock<mutex> mutexManager(mutex_);
			while (writeLocks && readLocks != 0)
			{
				writingAvailable.wait(mutexManager);
			}
			writeLocks = true;
		}

		void writeUnlock() {
			unique_lock<mutex> mutexManager(mutex_);
			writeLocks = false;
			readingAvailable.notify_all();
		}

}

#endif