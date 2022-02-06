#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include "Bucket.h"

class ExtensibleHashTable {
private:
	int globalDepth;
	Bucket* *buckets;
	void doubleSize();
	void redistribute(int key,int lDepth);
public:
	//default constructor
	ExtensibleHashTable();

	//copy Constructor
	ExtensibleHashTable(const ExtensibleHashTable& other);

	//destructor
	~ExtensibleHashTable();

	//constructor
	ExtensibleHashTable(int numberOfBuckets);

	//assignment operator
	ExtensibleHashTable& operator = (const ExtensibleHashTable&);

	//searches the hash table for the key, if found returns true
	bool find(int);

	//inserts the key into the hash table in the appropriate bucket
	void insert(int);

	//searches the hash table for the key; if found, removes all matching values (as there may be duplicate keys) from the hash table
	//returns true if the key was found and removed, false otherwise
	bool remove(int);

	//prints the contents of the directory and buckets; see below for exactly what should be printed
	void print();

};
#endif