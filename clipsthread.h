//---------------------------------------------------------------------------

#ifndef clipsthreadH
#define clipsthreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Memo.hpp>
#include <clipscpp.h>
//---------------------------------------------------------------------------
class ServerRouter : public CLIPS::CLIPSCPPRouter
{
	String insStdout, insCommand;
	TMemo *Memo;
public:
	ServerRouter(TMemo *OutputMemo)
	{
		Memo=OutputMemo;
	}
	int Query(CLIPS::CLIPSCPPEnv *e, const char * name)
    {
		if ((strcmp(name,"stdout") == 0) ||
		(strcmp(name,"stdin") == 0) ||
		(strcmp(name,"wprompt") == 0) ||
		(strcmp(name,"wdisplay") == 0) ||
		(strcmp(name,"wdialog") == 0) ||
		(strcmp(name,"werror") == 0) ||
		(strcmp(name,"wwarning") == 0) ||
		(strcmp(name,"wtrace") == 0) ||
		(strcmp(name,"top") == 0) )
			return true;
		return false;
	}
	int Print(CLIPS::CLIPSCPPEnv *e, const char * name, const char *p)
	{
		String SS;
		SS=(UnicodeString)(char*)p;
		if (strcmp(name,"stdout") == 0)
		{
			insStdout=insStdout+SS;
		}
		else
		{
			insStdout=insStdout+SS;
		}
		Output();
	}
	int Exit(CLIPS::CLIPSCPPEnv *e,int)
	{
		return(true);
	}
	int Getc(CLIPS::CLIPSCPPEnv *theCPPEnv, const char *name)
	{
		int rv;
		if (insCommand.Length()>0) {
			AnsiString SS=insCommand.SubString(1, 1);
			insCommand=insCommand.SubString(2, insCommand.Length()-1);
			rv=(unsigned char) SS[1];
			return rv;
		}
		else
		{
			return '\n';
		}
	}
	void AssignCommand(String Command)
	{
		insCommand=Command;
	}
	void Output()
	{
		Memo->Lines->Add(insStdout);
		insStdout="";
	}
};


class TClipsThread : public TThread
{
private:
	ServerRouter* sRouter;
protected:
	void __fastcall Execute();
	void __fastcall ExpertSystemRun();
public:
	CLIPS::CLIPSCPPEnv* theEnv;
	String __fastcall ReturnStdout();
	bool bNewinstance;
	bool bDestroy;
	__fastcall TClipsThread(bool CreateSuspended);
	void __fastcall AssignCommand(String Command);
	void __fastcall OnTerminateThread();
	AnsiString sPath;
};

//---------------------------------------------------------------------------
#endif
