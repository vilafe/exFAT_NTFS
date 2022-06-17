//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
FSReader *reader;
Updater *updater;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	UnicodeString diskLabel = Form1->Edit1->Text;
	UnicodeString disk = L"\\\\.\\" + diskLabel + L":";

	std::vector<UnicodeString> knowFS;
	knowFS.push_back(L"exFAT");  knowFS.push_back(L"NTFS");
	FileSystem* fs;
	int i = 0;
	while (i < knowFS.size()) {
		fs = FileSystem::newFileSystem(knowFS[i], disk);
		if (fs->getFSClustersAmount() != 0)  break;
	}

	if (i == knowFS.size()) {
		MessageBox(NULL, (LPCWSTR)L"Unknow file system of partition.",
			(LPCWSTR)L"Cannot detect file system", MB_ICONERROR);
		return;
	}

	reader = new FSReader(true, fs);
	reader->FreeOnTerminate = true;
	reader->Start();

	updater = new Updater(true);
	updater->FreeOnTerminate = true;
	updater->Start();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	reader->Terminate();
	updater->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	reader->Terminate();
    //updater->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (!Node) {
		return;
	}

	s_node *p_node_data = (s_node*)VirtualStringTree1->GetNodeData(Node);
	switch (Column) {
		case 0: {
			CellText = UnicodeString(p_node_data->id); break;
		}
		case 1: {
			CellText = p_node_data->signature; break;
		}
		case 2: {
			CellText = p_node_data->sector; break;
		}
	}
}
//---------------------------------------------------------------------------



