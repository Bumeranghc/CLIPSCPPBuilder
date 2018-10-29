//---------------------------------------------------------------------------

#ifndef CLIPSBuilderMainH
#define CLIPSBuilderMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Types.hpp>
#include "clipsthread.h"
//---------------------------------------------------------------------------
class TfCLIPSBuilder : public TForm
{
__published:	// IDE-managed Components
	TMemo *mOutput;
	TEdit *eInput;
	void __fastcall eInputKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfCLIPSBuilder(TComponent* Owner);
	TClipsThread *ctThread;
	AnsiString command;
	bool bClose;
};
//---------------------------------------------------------------------------
extern PACKAGE TfCLIPSBuilder *fCLIPSBuilder;
//---------------------------------------------------------------------------
#endif
