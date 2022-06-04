//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit3.h"
#pragma package(smart_init)
sqlite3*  database;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Updater::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall Updater::Updater(bool CreateSuspended)
	: TThread(CreateSuspended)
{
    int db_not_opened = sqlite3_open("db.sqlite", &database);
	if (db_not_opened) {
		MessageBox(NULL, (LPCWSTR)L"DB not opened.",
			(LPCWSTR)L"Cannot open DB", MB_ICONERROR);;
	}
}
//---------------------------------------------------------------------------
void __fastcall Updater::Execute()
{
	while(true) {
		Synchronize(&UpdateVST);
		Sleep(1000);
		if (Terminated) break;
	}

}
//---------------------------------------------------------------------------

void __fastcall Updater::UpdateVST()
{
	Form2->VirtualStringTree1->Clear();
	Form2->VirtualStringTree1->BeginUpdate();
	sqlite3_stmt	*p_statement;
	int result = sqlite3_prepare_v2(database,"SELECT id, signature, sector FROM finded",-1,&p_statement,NULL);
	while(true) {
		result = sqlite3_step(p_statement);
		if(result != SQLITE_ROW) break;

		int id = sqlite3_column_int(p_statement, 0);
		unsigned char *p_signature = (unsigned char *)sqlite3_column_text(p_statement, 1);
		int sector = sqlite3_column_int(p_statement, 2);

		PVirtualNode entry_node = Form2->VirtualStringTree1->AddChild(Form2->VirtualStringTree1->RootNode);
		s_node *p_node_data = (s_node*)Form2->VirtualStringTree1->GetNodeData(entry_node);
		p_node_data->id = int(id);
		p_node_data->signature = (UnicodeString)(char*)p_signature;
		p_node_data->sector = int(sector);

	}

	Form2->VirtualStringTree1->EndUpdate();
	sqlite3_finalize(p_statement);
}