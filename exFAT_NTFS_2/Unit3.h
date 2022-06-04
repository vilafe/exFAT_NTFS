//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
#include "main.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Updater : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Updater(bool CreateSuspended);
    void __fastcall Updater::UpdateVST();
};
//---------------------------------------------------------------------------
#endif
