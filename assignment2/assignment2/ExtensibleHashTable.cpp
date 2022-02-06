#include "bucket.h"
#include "extensiblehashtable.h"
#include <iostream>
#include <string>

using namespace std;

//default constructor
ExtensibleHashTable::ExtensibleHashTable() {
    globalDepth = 1;
    int directorySize = pow(2, globalDepth);
    buckets = new Bucket* [directorySize];
    for (int i = 0; i < directorySize; i++) {
        buckets[i] = new Bucket();
        //cout << i << endl;//test
    }
}

//copy Constructor
ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable& temp) {
    globalDepth = temp.globalDepth;
    int directorySize = pow(2, globalDepth);
    buckets = new Bucket * [directorySize];
    for (int i = 0; i < directorySize; i++) {
        buckets[i] = temp.buckets[i];
    }
}

//destructor
ExtensibleHashTable::~ExtensibleHashTable() {
    if (buckets == nullptr)
        return;
    delete buckets;
    buckets = nullptr;
}

//constructor
ExtensibleHashTable::ExtensibleHashTable(int numberOfBuckets) {
    globalDepth = 1;
    int directorySize = pow(2, globalDepth);
    buckets = new Bucket * [directorySize];
    for (int i = 0; i < directorySize; i++) {
        buckets[i] = new Bucket(numberOfBuckets);
        //cout << i << endl;//test
    }
}

ExtensibleHashTable& ExtensibleHashTable::operator = (const ExtensibleHashTable& temp) {
    if (this == &temp)
        return *this;
    for (int i = 0; i < pow(2, globalDepth); i++) {
        delete buckets[i];
    }
    delete buckets;

    globalDepth = temp.globalDepth;
    buckets = new Bucket * [pow(2, globalDepth)];
    for (int i = 0; i < pow(2, globalDepth); i++) {
        buckets[i] = temp.buckets[i];
    }
    return *this;
}

//double directory size
void ExtensibleHashTable::doubleSize() {
    //cout << buckets[0]->getDepth() << "local depth of buckets[0] before double" << endl;
    int oldDirectorySize = pow(2, globalDepth);
    globalDepth++;
    int directorySize = pow(2, globalDepth);
    Bucket** newbuckets = new Bucket * [directorySize];
    for (int i = 0; i < directorySize; i++) {
        int index = i % oldDirectorySize; // index of bucket which new buckets should point to
        newbuckets[i] = buckets[index];
    }
    delete buckets;
    buckets = newbuckets;
    //cout << buckets[0]->getDepth() << "local depth of buckets[0] after double" << endl;
}

// redistribute keys in oldIndex into oldIndex and (oldIndex)+pow(2,localDepth) which is oldIndex adding leftmost bit 1
void ExtensibleHashTable::redistribute(int key,int lDepth) {
    //int lDepth = buckets[oldIndex]->getDepth(); // depth used to decide which entry should key be distributed
    //cout << buckets[0]->getDepth() << "depth of bucket 0" << endl;
    //int bSize = buckets[oldIndex]->getSize(); //bucketSize
    //int newIndex = oldIndex + pow(2, lDepth);// these two array indexes are only diffrent in (lDepth)th bit
    //buckets[oldIndex]->changeDepth();//localdepth++
    //int maxIndex = pow(2, globalDepth);
    //buckets[newIndex] = new Bucket(lDepth+1, bSize);
    //cout << "print bucket" << newIndex << endl;
    //buckets[newIndex]->print();
    //cout << endl;
    //int* temp = new int[maxIndex];//temp array to store reallocated keys
    //for (int i = 0; i < maxIndex; i++) {
    //    temp[i] = buckets[oldIndex]->getKey(i);
    //}
    //for (int i = 0; i < maxIndex; i++) {
    //    int n = pow(2, lDepth);//last n bits we need
    //    if(temp[i]==-1)
    //        continue;
    //    if (temp[i] % n == newIndex) {
    //        buckets[oldIndex]->remove(temp[i]);
    //        buckets[newIndex]->insert(temp[i]);
    //    }
    //}
    //delete[] temp;
    int temp1;
    int index;
    int oldSize = pow(2, lDepth);
    int newSize = pow(2, lDepth+1);
    int oldIndex = key % oldSize;
    int newIndex = oldSize + oldIndex;
    int* temp2 = buckets[key % oldSize]->getKey();
    buckets[oldIndex] = new Bucket(buckets[oldIndex]->getSize());
    buckets[oldIndex]->setDepth(lDepth + 1);
    buckets[newIndex] = new Bucket(buckets[oldIndex]->getSize());
    buckets[newIndex]->setDepth(lDepth + 1);
    for (int i = 0; i < buckets[oldIndex]->getSize(); i++) {
        temp1 = temp2[i];
        index = temp1 % newSize;
        buckets[index]->insert(temp1);
    }
}

//searches the hash table for the key, if found returns true
bool ExtensibleHashTable::find(int key) {
    int n = pow(2, globalDepth);//last n bits we want
    return buckets[key % n]->find(key);
}

//inserts the key into the hash table in the appropriate bucket
void ExtensibleHashTable::insert(int key) {
    //doubleSize();
    int n = pow(2, globalDepth);//last n bits we want
    while (buckets[key % n]->checkFull() == true) {
        int oldlocalDepth = buckets[key % n]->getDepth();
        // check runtime_error first
        if (buckets[key % n]->runtime_error(key) == true) {
            cout << "runtime_error, failed to insert: " << key << endl;
            return;
        }
        else if (buckets[key % n]->getDepth() != globalDepth) {
            int lDepth = buckets[key % n]->getDepth();
            redistribute(key,lDepth);
        }// redistribute keys

        else if (buckets[key % n]->getDepth() == globalDepth) {
            doubleSize(); 
            int lDepth = buckets[key % n]->getDepth();
            redistribute(key, lDepth);
            //print();
            //cout << "print after double" << endl;
        }// gobaldepth and localdepth are equal, double directory size
        
        n = pow(2, globalDepth);
    }
    n = pow(2, globalDepth);//last n bits we need
    buckets[key % n]->insert(key);
    //buckets[1]->insert(key);//test
}

//searches the hash table for the key; if found, removes all matching values (as there may be duplicate keys) from the hash table
//returns true if the key was found and removed, false otherwise
bool ExtensibleHashTable::remove(int key) {
    if (find(key) == 0)
        return false;
    int n = pow(2, globalDepth);//last n bits we want
    return buckets[key % n]->remove(key);
}

//prints the contents of the directory and buckets; see below for exactly what should be printed
void ExtensibleHashTable::print() {
    bool duplicate = 0;
    int n = pow(2, globalDepth);//last n bits we want
    for (int i = 0; i < n; i++) {
        cout << i << ": " << buckets[i] << " --> ";
        for (int j = 0; j < i; j++) {
            if (buckets[i] == buckets[j]) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate == 1) {
            duplicate = 0;
            cout << endl;
            continue;
        }
        buckets[i]->print();
        cout << endl;
    }
}
