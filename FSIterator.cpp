#include "main.h"

FSIterator::FSIterator(FileSystem* fs) : fs(fs), index(1) {};
void FSIterator::begin() {
	this->index = 1;
};
void FSIterator::operator++() {
	this->index++;
};
bool FSIterator::end() const {
	return (this->index == fs->getFSClustersAmount()+1);
};
void FSIterator::CurrentSector(byte_ptr sector){
	UINT64 success = fs->ReadCluster(this->index, 1, sector);
};
UINT64 FSIterator::CurrentIndex() const {
	return this->index;
};

