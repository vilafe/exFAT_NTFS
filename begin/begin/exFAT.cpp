#include "main.h"

exFAT::exFAT(WSTR diskLabel) : 
	FileSystem(diskLabel, 0, 0, 512) {

	byte_sptr bootRecord(new BYTE[512]);
	UINT64 readSuccess = this->ReadCluster(0, 1, bootRecord);
	if (readSuccess) {
		br_exfat_sptr brExFat = reinterpret_cast<br_exfat_sptr&>(bootRecord);
		const char* exFAT = reinterpret_cast<const char*>((brExFat.get())->OEM_name);
		if (strncmp(exFAT, "EXFAT", 5) == 0) {
			std::cout << "This is an exFAT boot record!" << std::endl;

			int sectorSize = int(brExFat.get()->Sector_size);
			int clusterMultiplier = int(brExFat.get()->Cluster_multiplier);
			this->ClusterSize = pow(2, sectorSize) * pow(2, clusterMultiplier);

			this->FSClustersAmount = brExFat.get()->Number_of_clasters;

			this->FSSize = this->getClusterSize() * this->getFSClustersAmount();
		}
		else std::cout << "This is not an exFAT boot record! Exit." << std::endl;
	}
};