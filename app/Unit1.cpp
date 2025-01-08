//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <cstdbool>
#pragma hdrstop
#include <typeinfo>
#include <iostream>
#include <fstream>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
std::string expression = "";

//---------------------------------------------------------------------------
void AttachConsole() {
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
}


__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

	//AttachConsole();

	std::cout << "Application Started..." << std::endl;
	MyDll = LoadLibrary(L"../../../calculator-service/x64/Debug/Calculator.dll");

	if (MyDll != NULL) {
		calc = (pCalc)GetProcAddress(MyDll, "calculate");
		get_total = (pGet_Total)GetProcAddress(MyDll, "get_total");
		calc_init = (pInit)GetProcAddress(MyDll, "calculator_init");
		get_expression = (pGet_expression)GetProcAddress(MyDll, "get_expression");

		if((calc && get_total && calc_init && get_expression) != NULL){
			calc_init();

		} else {
			DWORD error = GetLastError();
			MessageBox(NULL,
           (L"Failed to load functions. Error code: " + std::to_wstring(error)).c_str(),
           L"Error",
		   MB_OK);
		   return;
        }

	}   else {
		  DWORD error = GetLastError();

         MessageBox(NULL,
           (L"Failed to load DLL. Error code: " + std::to_wstring(error)).c_str(),
           L"Error",
		   MB_OK);
           return;
	}

    //calculator_init();

	int buttonWidth = 75;
	int buttonHeight = 75;
	int xOffset = 10;
	int yOffset = 10;
	char operations[8] = {'=', '+', '-', '*', '/', '%', 'a', 'C'};

	button = new TButton*[4*5];
	//buttons 1 - 9
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			button[i * 3 + j] = new TButton(this);
			button[i * 3 + j]->Parent = this;
			button[i * 3 + j]->Width = buttonWidth;
			button[i * 3 + j]->Height = buttonHeight;
			button[i * 3 + j]->SetBounds(35 + xOffset + i * buttonWidth, 405 - buttonHeight - yOffset - j * buttonHeight, buttonWidth, buttonHeight);
			button[i * 3 + j]->Caption = IntToStr(i + j * 3 + 1);
			button[i * 3 + j]->Font->Size = 28;
			button[i * 3 + j]->Font->Style = button[i * 3 + j]->Font->Style << fsBold;
			button[i * 3 + j]->OnClick = GridButtonClick;

		}
	}

	//button 0

	button[9] = new TButton(this);
	button[9]->Parent = this;
	button[9]->Width = buttonWidth;
	button[9]->Height = buttonHeight;
	button[9]->SetBounds(35 + xOffset, 395, buttonWidth, buttonHeight);
	button[9]->Font->Size = 28;
	button[9]->Font->Style = button[9]->Font->Style << fsBold;
	button[9]->Caption = IntToStr(0);
	button[9]->OnClick = GridButtonClick;

	// . button
	button[10] = new TButton(this);
	button[10]->Parent = this;
	button[10]->Width = buttonWidth;
	button[10]->Height = buttonHeight;
	button[10]->SetBounds(button[9]->Left + buttonWidth, 395, buttonWidth, buttonHeight);
	button[10]->Font->Size = 28;
	button[10]->Font->Style = button[10]->Font->Style << fsBold;
	button[10]->Caption = ".";
	button[10]->OnClick = GridButtonClick;

	//back button

	button[11] = new TButton(this);
	button[11]->Parent = this;
	button[11]->Width = buttonWidth;
	button[11]->Height = buttonHeight;
	button[11]->SetBounds(button[10]->Left + buttonWidth, 395, buttonWidth, buttonHeight);
	button[11]->Font->Size = 28;
	button[11]->Font->Style = button[11]->Font->Style << fsBold;
	button[11]->Caption = "<";
	button[11]->OnClick = GridButtonClick;

	//equal, +, -, x, / buttons
	for (int i = 0; i < 5; i++) {
		button[12 + i] = new TButton(this);
		button[12 + i]->Parent = this;
		button[12 + i]->Width = buttonWidth;
		button[12 + i]->Height = buttonHeight;
		button[12 + i]->SetBounds(button[11]->Left + buttonWidth, 395 - i * buttonHeight, buttonWidth, buttonHeight);
		button[12 + i]->Caption = operations[i];
		button[12 + i]->Font->Size = 28;
		button[12 + i]->Font->Style = button[12 + i]->Font->Style << fsBold;
		button[12 + i]->OnClick = GridButtonClick;

	}

	//%, (), AC buttons
	for (int i = 0; i < 3; i++) {
		button[17 + i] = new TButton(this);
		button[17 + i]->Parent = this;
		button[17 + i]->Width = buttonWidth;
		button[17 + i]->Height = buttonHeight;
		button[17 + i]->SetBounds(button[16]->Left - (i+1) *buttonWidth, button[16]->Top, buttonWidth, buttonHeight);
		button[17 + i]->Caption = operations[i + 5];
		button[17 + i]->Font->Size = 28;
		button[17 + i]->Font->Style = button[17 + i]->Font->Style << fsBold;
		button[17 + i]->OnClick = GridButtonClick;
	}

}

void __fastcall TForm1::GridButtonClick(TObject *Sender){
	std::cout << "button pressed" << std::endl;
	// Convert TButton's Text (System::String) to std::string
	UnicodeString buttonText = dynamic_cast<TButton*>(Sender)->Caption;
	std::string buttonTextStr = AnsiString(buttonText).c_str();
	// Append the text from the button (now in std::string) to expression
	expression = buttonTextStr;
	// Set Label1's Text (convert std::string back to UnicodeString for the Label)
	std::cout << "expression: " << expression << std::endl;

	// Call the calculate function with the std::string expression converted to const char*
	calc(expression.c_str());

	std::string curr_expression = get_expression();
	std::cout << "curr expression: " << curr_expression << std::endl;

	UnicodeString text = UnicodeString(curr_expression.c_str());

	std::cout << "unicodeString: " << text.c_str() << std::endl;

	Label1->Caption = text;

	//ShowMessage(get_total());
}

//---------------------------------------------------------------------------
