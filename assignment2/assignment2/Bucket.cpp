#include "Bucket.h"
#include <iostream>
#include <string>
#include "math.h"

using namespace std;

//default constructor
Bucket::Bucket() {
	localDepth = 1;
	bucketSize = 4;
	block = new int[bucketSize];
	// assign -1 value for empty entry
	for (int i = 0; i < bucketSize; i++) {
		block[i] = -1;
	}
}

//copy constructor
Bucket::Bucket(const Bucket& temp) {
	localDepth = temp.localDepth;
	bucketSize = temp.bucketSize;
	block = new int[bucketSize];
	for (int i = 0; i < bucketSize; i++) {
		block[i] = temp.block[i];
	}
}

//destructor
Bucket::~Bucket() {
	if (block != nullptr) {
		delete block;
		block = nullptr;
		//cout << "delete block" << endl;//test
	}
}
//constructor
Bucket::Bucket(int numberOfBucket) {
	localDepth = 1;
	bucketSize = numberOfBucket;
	block = new int[bucketSize];
	// assign -1 value for empty entry
	for (int i = 0; i < bucketSize; i++) {
		block[i] = -1;
	}
}

//assign operator
Bucket& Bucket::operator = (const Bucket& temp) {
	if (this == &temp)
		return *this;
	delete block;
	localDepth = temp.localDepth;
	bucketSize = temp.bucketSize;
	block = new int[bucketSize];
	for (int i = 0; i < bucketSize; i++) {
		block[i] = temp.block[i];
	}
	return *this;
}

bool Bucket::find(int key) {
	for (int i = 0; i < bucketSize; i++) {
		if (block[i] == key)
			return true;
		else if (block[i] == -1)//current entry is empty stop searching
			break;
	}
	return false;
}

void Bucket::print() {
	cout << " [";
	for (int i = 0; i < bucketSize-1; i++) {
		if (block[i] == -1)
			cout << "-,";
		else
			cout << block[i] << ",";
	}
	if (block[bucketSize - 1] == -1)
		cout << "-] (" << localDepth << ")";
	else
		cout << block[bucketSize-1] << "] (" << localDepth << ")";
}

bool Bucket::remove(int key) {
	for (int i = 0; i < bucketSize; i++) {
		if (block[i] == key) {
			block[i] == -1;//-1 means empty
			for (int j = i + 1; j < bucketSize; j++) {
				if (block[j] != -1) {
					int temp = block[j];
					block[j] = -1;
					block[j - 1] = temp;
				}
				else
					break;
			}// rearrange array
			i--;//need to check current index again
		}
		else if (block[i] == -1)//current entry is empty stop searching
			break;
	}
	return true;
}

//check current block is full or not, if it is full, then return true
bool Bucket::checkFull() {
	return block[bucketSize - 1] != -1;
}

//insert key
void Bucket::insert(int key) {
	for (int i = 0; i < bucketSize; i++) {
		if (block[i] == -1) {
			block[i] = key;
			return;
		}
	}
}

//check runtime_error, if error, then exit
bool Bucket::runtime_error(int key) {
	int temp = key;
	for (int i = 0; i < bucketSize; i++) {
		if (block[i] != temp) 
			return false;
	}
	return true;
}

int Bucket::getDepth() {
	return localDepth;
}

void Bucket::setDepth(int dp) {
	localDepth = dp;
}

int* Bucket::getKey() {
	return this->block;
}

int Bucket::getSize() {
	return bucketSize;
}