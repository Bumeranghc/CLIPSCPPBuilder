//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "clipsthread.h"
#include <stdio.h>
#include "CLIPSBuilderMain.h"
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

__fastcall TClipsThread::TClipsThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	sPath="SIMPLTST.clp";
	theEnv=new CLIPS::CLIPSCPPEnv();
	sRouter = new ServerRouter(fCLIPSBuilder->mOutput);
	theEnv->AddRouter("serverrouter", 10, sRouter);
	bNewinstance=true;
	bDestroy=false;
}
//---------------------------------------------------------------------------
void __fastcall TClipsThread::Execute()
{
	while (!bDestroy) {
		ExpertSystemRun();
	}
}
//---------------------------------------------------------------------------
void __fastcall TClipsThread::AssignCommand(String Command)
{
	sRouter->AssignCommand(Command);
}
//---------------------------------------------------------------------------
String __fastcall TClipsThread::ReturnStdout()
{

}

void __fastcall TClipsThread::ExpertSystemRun()
{
	if (bNewinstance) {
		if (FileExists(sPath)) {
            theEnv->Clear();
			theEnv->Load(sPath.c_str());
			theEnv->Reset();
			int i=0;
			while ((theEnv->Run(1)!=0)&&!bDestroy)
			{
			i++;
			}
		}
		bNewinstance=false;
	}
}

//---------------------------------------------------------------------------

void __fastcall TClipsThread::OnTerminateThread()
{
	theEnv->Clear();
	delete theEnv;
	delete sRouter;
}
//---------------------------------------------------------------------------

