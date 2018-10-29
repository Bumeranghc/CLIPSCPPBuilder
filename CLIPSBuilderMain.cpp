//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CLIPSBuilderMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfCLIPSBuilder *fCLIPSBuilder;
//---------------------------------------------------------------------------
__fastcall TfCLIPSBuilder::TfCLIPSBuilder(TComponent* Owner)
	: TForm(Owner)
{
		ctThread=new TClipsThread(false);
}
//---------------------------------------------------------------------------
void __fastcall TfCLIPSBuilder::eInputKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key==13) {
		mOutput->Lines->Add(eInput->Text+"\n");
		command=eInput->Text;
        ctThread->AssignCommand(command);
		eInput->Text="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TfCLIPSBuilder::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (ctThread) ctThread;
}
//---------------------------------------------------------------------------

