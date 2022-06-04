#include "main.h"
#include <typeinfo>

FileSystem::FileSystem(
    WSTR diskLabel,
    UINT64 fsSize,
    UINT64 fsClustersAmount,
    UINT64 clusterSize) :
    FSSize(fsSize),
    FSClustersAmount(fsClustersAmount),
    ClusterSize(clusterSize) 
{
    WSTR disk = L"\\\\.\\" + diskLabel + L":";
    this->DiskHandler = createFileHandler(disk.c_str());
};

UINT64 FileSystem::getClusterSize() const {
	return this->ClusterSize;
}

UINT64 FileSystem::getFSClustersAmount() const {
	return this->FSClustersAmount;
}

UINT64 FileSystem::getFSSize() const {
	return this->FSSize;
}

HANDLE FileSystem::getDiskHandler() const {
	return this->DiskHandler;
}

UINT64 FileSystem::ReadCluster(
	UINT64 clusterNumber,
	UINT64 clusterToRead,
	byte_sptr outBuffer)
{
    setHandlerPosition(this->DiskHandler, clusterNumber * this->getClusterSize());

    DWORD bytesToRead = clusterToRead * this->getClusterSize();
    DWORD bytesReaded = 0;
    
    bool success = ReadFile(
        this->DiskHandler,
        outBuffer.get(),
        bytesToRead,
        &bytesReaded,
        NULL
    );

    if (!success || bytesReaded != bytesToRead) {
        std::cerr << "Misreading bytes. Run program again. Exit." << std::endl;
        CloseHandle(this->DiskHandler);
        system("PAUSE");
        exit(EXIT_FAILURE);
    }
    
	return bytesToRead;
}

FileSystem* FileSystem::newFileSystem(const WSTR fsType, WSTR diskLabel) {
    
    MAP<WSTR, FileSystem*> fsTypes = {
        {EXFAT, new exFAT(diskLabel)}
    };

    return fsTypes[fsType];
}
