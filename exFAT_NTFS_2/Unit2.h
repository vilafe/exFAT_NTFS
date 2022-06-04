//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include "sqlite3.h"
#include "main.h"
#include "Unit1.h"
#include "Unit3.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "windows.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree1;
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);




private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------

typedef struct {
	 int 			id;
	 UnicodeString	signature;
	 int	sector;
} s_node;



#endif
