#include "main.h"


FileSystem::FileSystem(
	UnicodeString diskLabel,
	UINT64 fsSize,
	UINT64 fsClustersAmount,
	UINT64 clusterSize) :
	FSSize(fsSize),
	FSClustersAmount(fsClustersAmount),
	ClusterSize(clusterSize)
{
	this->DiskHandler = createFileHandler(diskLabel.c_str());
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
	byte_ptr outBuffer)
{
	setHandlerPosition(this->DiskHandler, clusterNumber * this->getClusterSize());

	DWORD bytesToRead = clusterToRead * this->getClusterSize();
	DWORD bytesReaded = 0;
	bool success = ReadFile(
		this->DiskHandler,
		outBuffer,
		bytesToRead,
		&bytesReaded,
		NULL
    );

    if (!success || bytesReaded != bytesToRead) {
		MessageBox(NULL, (LPCWSTR)L"Error FS cluster.", (LPCWSTR)L"Error FS cluster.", MB_ICONERROR);
		CloseHandle(this->DiskHandler);
		exit(EXIT_FAILURE);
	}

	return bytesToRead;
}

FileSystem* FileSystem::newFileSystem(const UnicodeString fsType, UnicodeString diskLabel) {
	MAP<UnicodeString, int> fsTypes;
	fsTypes.insert(std::pair<UnicodeString, int>(L"exFAT", 1));
	int selection = fsTypes[fsType];
	switch(selection)
	{
	case 1:
		 return new exFAT(diskLabel);
	}
    return NULL;
}
