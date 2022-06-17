#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <map>
#include <System.hpp>
#include <typeinfo>
#include <fstream>
#include <ios>
//---------------------------------------------------------------------
#define MAP std::map
//---------------------------------------------------------------------
typedef unsigned char BYTE;
typedef unsigned __int32 UINT32;
typedef unsigned __int64 UINT64;
typedef BYTE* byte_ptr;

//---------------------------------------------------------------------

//---------------------------------------------------------------------
#pragma pack(push,1)
typedef struct {
	BYTE Padding_1[3];
	BYTE OEM_name[8];
	BYTE Padding_2[61];
	ULONGLONG Sectors_number;
	ULONG First_sector;
	ULONG Size_in_sectors;
	ULONG Root_directory_cluster;
	ULONG Volume_serial_number;
	ULONG Padding_3;
	BYTE Sector_size;
	BYTE Cluster_multiplier;
	BYTE Padding_4[400];
	BYTE Signature[2];
} BR_exFAT;
#pragma pack(pop)
//---------------------------------------------------------------------
typedef BR_exFAT* br_exfat_ptr;
//---------------------------------------------------------------------
HANDLE  createFileHandler(const WCHAR* file_name);
void    setHandlerPosition(HANDLE& fileHandler, UINT32 offset);
void	log(char* log);
//---------------------------------------------------------------------
class FileSystem {
protected:
	HANDLE DiskHandler;
	UINT64 FSSize;
	UINT64 ClusterSize;
public:
	friend class FSIterator;
	FileSystem(UnicodeString diskLabel,
		UINT64 fsSize,
		UINT64 fsClustersAmount,
	UINT64 getFSSize() const;
	UINT64 getFSClustersAmount()  const;
	UINT64 getClusterSize()  const;
	HANDLE getDiskHandler() const;
	UINT64 ReadCluster(
		UINT64 clusterNumber,
		UINT64 clustersToRead, 
		byte_ptr outBuffer
	);
	static FileSystem* newFileSystem(const UnicodeString fsType, UnicodeString diskLabel);
};
//---------------------------------------------------------------------
class FSIterator {
protected:
	FileSystem* fs;
	UINT64 index;
public:
	friend class FileSystem;
	FSIterator(FileSystem* fs);
	void begin();
	bool end() const;
	void CurrentSector(byte_ptr sector);
	UINT64 CurrentIndex() const;
	void setIndex(UINT64 index);
};
//---------------------------------------------------------------------
class FSIReader {
public:
	FSIterator* fsi;
	FSIReader(FSIterator* fsi);
	void operator++();
	FSIterator* getFSIterator() const;
};
//---------------------------------------------------------------------
class exFAT : public FileSystem {
public:
	exFAT(UnicodeString diskLabel);
};
//---------------------------------------------------------------------
class NTFS : public FileSystem {
public:
	NTFS(UnicodeString diskLabel);
};
//---------------------------------------------------------------------

