#include "main.h"

FSIReader::FSIReader(FSIterator* fsi) : fsi(fsi) {};

FSIterator* FSIReader::getFSIterator() const {
	return fsi;
};

void FSIReader::operator++() {
	byte_ptr cluster(new BYTE[fsi->getFS()->getClusterSize()]);
	UINT64 readSuccess = fsi->getFS()->ReadCluster(fsi->CurrentIndex(), 1, cluster);
	
	while ((cluster[0] == '0' && cluster[1] == '0')) {
		fsi->setIndex(fsi->CurrentIndex() + 1);
		
		if (fsi->CurrentIndex() > fsi->getFS()->getFSClustersAmount()) {
			fsi->setIndex(0);
			return;
		}
		
		readSuccess = fsi->getFS()->ReadCluster(fsi->CurrentIndex(), 1, cluster);
	}
};