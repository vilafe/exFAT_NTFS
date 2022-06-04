#pragma once
#include <memory>
#include <Windows.h>
#include <iostream>
#include <map>
//---------------------------------------------------------------------
#define MAP std::map

//---------------------------------------------------------------------
using BYTE = unsigned char;
using UINT64 = unsigned __int64;
using UINT32 = unsigned __int32;
using byte_sptr = std::shared_ptr<BYTE>;
using WSTR = std::wstring;

//---------------------------------------------------------------------

//---------------------------------------------------------------------
#pragma pack(push,1)
using BR_exFAT = struct {
	BYTE Padding_1[3];
	BYTE OEM_name[8];
	BYTE Padding_2[61];
	ULONGLONG Sectors_number;
	ULONG First_sector;
	ULONG Size_in_sectors;
	ULONG Sector_of_bitmap;
	ULONG Number_of_clasters;
	ULONG Root_directory_cluster;
	ULONG Volume_serial_number;
	ULONG Padding_3;
	BYTE Sector_size;
	BYTE Cluster_multiplier;
	BYTE Padding_4[400];
	BYTE Signature[2];
};
#pragma pack(pop)

//---------------------------------------------------------------------


using br_exfat_sptr = std::shared_ptr<BR_exFAT>;


//---------------------------------------------------------------------

HANDLE  createFileHandler(const WCHAR* file_name);
void    setHandlerPosition(HANDLE& fileHandler, UINT32 offset);

//---------------------------------------------------------------------

class FileSystem {

protected:
	HANDLE DiskHandler;
	UINT64 FSSize;
	UINT64 FSClustersAmount;
	UINT64 ClusterSize;

public:
	friend class FSIterator;

	FileSystem(
		WSTR diskLabel,
		UINT64 fsSize,
		UINT64 fsClustersAmount,
		UINT64 clusterSize);

	UINT64 getFSSize() const;
	UINT64 getFSClustersAmount()  const;
	UINT64 getClusterSize()  const;
	HANDLE getDiskHandler() const;

	UINT64 ReadCluster(
		UINT64 clusterNumber, // cluster number to read 
		UINT64 clustersToRead, // number of clusters to read
		byte_sptr outBuffer // read cluster data
	);

	static FileSystem* newFileSystem(const WSTR fsType, WSTR diskLabel);

};

//---------------------------------------------------------------------

class FSIterator {
protected:
	FileSystem* fs;
	UINT64 index;
public:
	friend class FileSystem;
	FSIterator(FileSystem* fs);
	void First();
	void Next();
	bool IsDone() const;
	byte_sptr Current() const;
	UINT64 CurrentIndex() const;
};

//---------------------------------------------------------------------

class FSIDecorator {
protected:
	FileSystem* fs;
public:
	FSIDecorator(FileSystem* fs);
	bool clusterEmpty() const;
};

//---------------------------------------------------------------------

class exFAT : public FileSystem {


public:

	exFAT(WSTR diskLabel);
};

//---------------------------------------------------------------------

class NTFS : public FileSystem {
public:

	NTFS(WSTR diskLabel);
};

//---------------------------------------------------------------------

const WSTR EXFAT = L"exFAT";

