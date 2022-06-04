#include "main.h"

FSIterator::FSIterator(FileSystem* fs) : fs(fs), index(0) {};

void FSIterator::First() {
	this->index = 0;
};

void FSIterator::Next() {
	this->index++;
};

bool FSIterator::IsDone() const {
	return (this->index == fs->FSClustersAmount+1);
};

byte_sptr FSIterator::Current() const {
	byte_sptr sector;
	UINT64 success = fs->ReadCluster(this->index, 1, sector);
	return sector;
};

UINT64 FSIterator::CurrentIndex() const {
	return this->index;
};