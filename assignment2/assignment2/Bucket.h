#ifndef BUCKET_H
#define BUCKET_H

class Bucket {
private:
	int localDepth;
	int bucketSize;
	int* block;
public:
	//default constructor
	Bucket();

	//copy Constructor
	Bucket(const Bucket&);

	//destructor
	~Bucket();

	//constructor
	Bucket(int numberOfBucket);

	//assign operator
	Bucket& operator = (const Bucket&);

	//find value
	bool find(int);

	//print array
	void print();

	//remove key and rearrange array
	bool remove(int);

	//check current block is full or not, if it is full, then return true
	bool checkFull();

	//insert key
	void insert(int);

	//check runtime_error, if error, then exit
	bool runtime_error(int key);

	int getDepth();

	void setDepth(int);

	//return key value in current index
	int* getKey();

	//get bucketSize
	int getSize();
};
#endif 