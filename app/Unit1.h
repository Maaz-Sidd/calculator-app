//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <string>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;

	void __fastcall GridButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    HMODULE MyDll;

	typedef double(__stdcall *pGet_Total)();
	typedef void(__stdcall *pInit)();
	typedef void(__stdcall *pCalc)(const char*);
	typedef const char*(__stdcall *pGet_expression)();

	pCalc calc;
	pGet_Total get_total;
	pInit calc_init;
	pGet_expression get_expression;
	TButton ** button;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
