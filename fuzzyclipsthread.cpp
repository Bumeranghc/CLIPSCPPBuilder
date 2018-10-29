//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fuzzyclipsthread.h"
#include "clientform.h"
#include "clientmoduleunit.h"
#include <stdio.h>
extern "C"
{
	#include "clips\clips.h"
}
#pragma package(smart_init)

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TClipsThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
int TFuzzyClipsThread::FindScreen(char *logicalName)
 {
	if ((strcmp(logicalName,"stdout") == 0) ||
	(strcmp(logicalName,"stdin") == 0) ||
	(strcmp(logicalName,"wprompt") == 0) ||
	(strcmp(logicalName,"wdisplay") == 0) ||
	(strcmp(logicalName,"wdialog") == 0) ||
	(strcmp(logicalName,"werror") == 0) ||
	(strcmp(logicalName,"wwarning") == 0) ||
	(strcmp(logicalName,"wtrace") == 0) ||
	(strcmp(logicalName,"top") == 0) )
		return true;
	return false;
 }

int TFuzzyClipsThread::PrintScreen(char *logicalName, char *str)
{
	String SS;
	SS=(UnicodeString)(char*)str;
	if (strcmp(logicalName,"stdout") == 0)
	{
		fClientform->mOutput->Lines->Text=fClientform->mOutput->Lines->Text+SS;
		fClientform->mOutput->SelStart=fClientform->mOutput->Text.Length()-1;
		fClientform->mOutput->SelLength=0;
	}
	else
	{
		fClientform->mOutput->Lines->Add(SS);
	}
}

int TFuzzyClipsThread::GetcScreen(char *logicalName)
 {
	int rv;
	if (fClientform->command.Length()>0) {
		AnsiString SS=fClientform->command.SubString(1, 1);
		fClientform->command=fClientform->command.SubString(2, fClientform->command.Length()-1);
		rv=(unsigned char) SS[1];
		return rv;
	}
	else
	{
		return '\n';
	}
}

__fastcall TFuzzyClipsThread::TFuzzyClipsThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	bNewinstance=false;
	bDestroy=false;
}
//---------------------------------------------------------------------------
void __fastcall TFuzzyClipsThread::Execute()
{
	AddRouter("screen", 10, FindScreen, PrintScreen, GetcScreen, NULL, NULL); //добавление роутинга ввода-вывода для окружения FuzzyCLIPS
	while (!bDestroy) {
		ExpertSystemRun();
	}
	DeleteRouter("screen");
}
//---------------------------------------------------------------------------
void __fastcall TFuzzyClipsThread::CanClose()
{
	fClientform->bClose=true;
}
//---------------------------------------------------------------------------
void __fastcall TFuzzyClipsThread::CantClose()
{
	fClientform->bClose=false;
}
//---------------------------------------------------------------------------
void __fastcall TFuzzyClipsThread::ExpertSystemRun()
{
	if (bNewinstance) {
		Synchronize(&CantClose);
		AnsiString sPath=SystemPath("%APPDATA%")+(ClientModule->cdsExpertsystems->FieldByName("esid")->Value)+".clp";

		TMemoryStream *M1 = new TMemoryStream();
		TStream *B1 = ClientModule->cdsExpertsystems->CreateBlobStream(ClientModule->cdsExpertsystems->FieldByName("eslisting"), bmRead);
		M1->CopyFrom(B1,B1->Size);
		M1->SaveToFile(sPath);
		delete B1;
		delete M1;

		//ClientModule->cdsExpertsystems->FieldByName("eslisting")->Value.SaveToFile(sPath);
		if (Load(sPath.c_str())==1&&FileExists(sPath)) {
			Reset();//
			int i=0;
			while ((Run(1)!=0)&&!bDestroy) {
				i++;
			}
			Clear();
			bNewinstance=false;
		}
		Synchronize(&CanClose);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFuzzyClipsThread::OnTerminateThread()
{
	Clear();
}
//---------------------------------------------------------------------------
String TFuzzyClipsThread::SystemPath(String Directory)
{
	String sPath;
	wchar_t WindowsDirectory[1024];
	ExpandEnvironmentStrings(Directory.w_str(), WindowsDirectory, 1024);
    sPath=WindowsDirectory;
	return sPath+"\\spn\\expertclient\\";
}
