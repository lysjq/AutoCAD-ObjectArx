#include <aced.h>
#include <rxregsvc.h>

void InitApp();
void UnloadApp();
void HelloWorld();

void InitApp() {
	acedRegCmds->addCommand(L"hello1", L"hello", L"hello", ACRX_CMD_MODAL, HelloWorld);
}

void UnloadApp() {
	acedRegCmds->removeGroup(L"hello1");
}

void HelloWorld() { 
	acutPrintf(L"hello world!");
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt){
	switch (msg)
	{
	case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		InitApp();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApp();
		break;
	default:
		break;
	}
	return AcRx::kRetOK;
}