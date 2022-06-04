#include "main.h"

int main()
{
    std::cout << "Enter the partition letter to check its exFAT boot record:" << std::endl;
    std::cout << ">: ";

    WSTR partLetter;
    std::wcin >> partLetter;

    FileSystem* fs = FileSystem::newFileSystem(EXFAT, partLetter);

    std::cout << "ClusterSize: " << fs->getClusterSize() << std::endl;
    std::cout << "FSClustersAmount: " << fs->getFSClustersAmount() << std::endl;
    std::cout << "FSSize: " << fs->getFSSize() << std::endl;

	system("PAUSE");
	return 0;
}

