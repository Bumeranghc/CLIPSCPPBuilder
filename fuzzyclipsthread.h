//---------------------------------------------------------------------------

#ifndef fuzzyclipsthreadH
#define fuzzyclipsthreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TFuzzyClipsThread : public TThread
{
private:
protected:
	void __fastcall Execute();
	void __fastcall ExpertSystemRun();
	static int GetcScreen(char *logicalName);
	static int FindScreen(char *logicalName);
	static int PrintScreen(char *logicalName, char *str);
	void __fastcall CanClose();
	void __fastcall CantClose();
	String SystemPath(String Directory);
public:
	__fastcall TFuzzyClipsThread(bool CreateSuspended);
	void __fastcall OnTerminateThread();
	bool bNewinstance;
	bool bDestroy;
	//String sInput;
};
//---------------------------------------------------------------------------
#endif
