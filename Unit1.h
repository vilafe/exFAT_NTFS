//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
#include "main.h"
#include "Unit2.h"
#include <string.h>

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class FSReader : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	FSIterator* fsi;
	__fastcall FSReader(bool CreateSuspended, FileSystem* fs);
};
//---------------------------------------------------------------------------
#endif
