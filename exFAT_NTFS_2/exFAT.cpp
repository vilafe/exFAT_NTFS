#include "main.h"

exFAT::exFAT(UnicodeString diskLabel) :
	FileSystem(diskLabel, 0, 0, 512) {

	byte_ptr bootRecord = new BYTE[512];
	UINT64 readSuccess = this->ReadCluster(0, 1, bootRecord);
	if (readSuccess) {
		br_exfat_ptr brExFat = reinterpret_cast<br_exfat_ptr&>(bootRecord);
		const char* exFAT = reinterpret_cast<const char*>(brExFat->OEM_name);
		if (strncmp(exFAT, "EXFAT", 5) == 0) {

			int sectorSize = int(brExFat->Sector_size);
			int clusterMultiplier = int(brExFat->Cluster_multiplier);

			this->FSClustersAmount = brExFat->Number_of_clasters;

			this->FSSize = this->getClusterSize() * this->getFSClustersAmount();
		}
		else std::cout << "This is not an exFAT boot record! Exit." << std::endl;
	}
};