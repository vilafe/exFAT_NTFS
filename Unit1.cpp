//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "Unit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//      void __fastcall FSReader::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

sqlite3*  database;

__fastcall FSReader::FSReader(bool CreateSuspended, FileSystem* fs)
	: TThread(CreateSuspended)
{
    fsi = new FSIterator(fs);
	/*log((char*)"BEGIN OF ITERATOR");
	char s2[10]; ltoa(fsi->CurrentIndex(), s2, 10);
	log(s2);
	log((char*)"END OF ITERATOR");;*/
	int db_not_opened = sqlite3_open("db.sqlite", &database);
	if (db_not_opened) {
		MessageBox(NULL, (LPCWSTR)L"DB not opened.",
			(LPCWSTR)L"Cannot open DB", MB_ICONERROR);;
	}
}
//---------------------------------------------------------------------------

bool insert(UnicodeString signature, UINT64 sector) {
	sqlite3_stmt *p_statement;

	UnicodeString prep_stm = "INSERT INTO finded (signature,sector) VALUES (\"" + signature + "\", " + sector + ");";
	wchar_t *p_sql_stm_wchar = prep_stm.c_str();
	char sql_stm[256];
	wcstombs(sql_stm, p_sql_stm_wchar, wcslen(p_sql_stm_wchar)+1);
	log(sql_stm);

	int result = sqlite3_prepare_v2(database,sql_stm,-1,&p_statement,NULL);
	result = sqlite3_step(p_statement);
	log((char*)sqlite3_errmsg(database));
	if(result != SQLITE_DONE) {
		return false;
	}
	return true;
};
//---------------------------------------------------------------------------
bool isSQLiteDB(byte_ptr cluster) {

	char s1[] = "SQLite";

	char s2[7];
	strncpy(s2, cluster, 6);
	s2[6] = '\0';

	if (!strncmp(s1, s2, 6)) {
		log((char*)"cancel isSQLiteDB");
		return true;
	}
	return false;
}

void __fastcall FSReader::Execute()
{
	byte_ptr cluster = new BYTE[fsi->getFS()->getClusterSize()];
	UnicodeString sign;
	char s2[10];
	while (!fsi->end()) {
		log((char*)"CURRENT OF ITERATOR"); ltoa(fsi->CurrentIndex(), s2, 10); log(s2);

		sign = UnicodeString(0);
		fsi->CurrentSector(cluster);
		if (cluster[0] == 0 && cluster[1] == 0) {fsi->operator ++();log((char*)"EMPTY");continue;}
		else if (cluster[1] == 'P' && cluster[2] == 'N' && cluster[3] == 'G') sign = UnicodeString(L"PNG");
		else if (isSQLiteDB(cluster)) sign = UnicodeString(L"SQLite");
		else if (cluster[6] == 'J' && cluster[7] == 'F' && cluster[8] == 'I' && cluster[9] == 'F') sign = UnicodeString(L"JPG");
		else if (cluster[0] == 49 && cluster[1] == 44 && cluster[2] == 33) sign = UnicodeString(L"MP3");



		if (sign != UnicodeString(0)) {
			if (!insert(sign, fsi->CurrentIndex())) MessageBox(NULL, (LPCWSTR)L"Error insert to DB.",
			(LPCWSTR)L"Error insert.", MB_ICONERROR);
		}

		log((char*)"IS TERMINATED");
		s2[10]; ltoa(Terminated, s2, 10); log(s2);
		if (Terminated) return;
		fsi->operator ++();
	}
	MessageBox(NULL, (LPCWSTR)L"OK",
			(LPCWSTR)L"Finished", MB_OK);
	delete[] cluster;
}
//---------------------------------------------------------------------------

