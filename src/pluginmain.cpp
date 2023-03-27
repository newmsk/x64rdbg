#include "pluginmain.h"
#include "plugin.h"

int pluginHandle;
HWND hwndDlg;
int hMenu;
int hMenuDisasm;
int hMenuDump;
int hMenuStack;
wchar_t g_iniPath[MAX_PATH];

PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    initStruct->pluginVersion = PLUGIN_VERSION;
    initStruct->sdkVersion = PLUG_SDKVERSION;
    strncpy_s(initStruct->pluginName, PLUGIN_NAME, _TRUNCATE);
    pluginHandle = initStruct->pluginHandle;
    return pluginInit(initStruct);
}

PLUG_EXPORT bool plugstop()
{
    pluginStop();
    return true;
}

PLUG_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
    hwndDlg = setupStruct->hwndDlg;
    hMenu = setupStruct->hMenu;
    hMenuDisasm = setupStruct->hMenuDisasm;
    hMenuDump = setupStruct->hMenuDump;
    hMenuStack = setupStruct->hMenuStack;
    pluginSetup();
}

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		HINSTANCE hinst = hInstDLL;

		wchar_t pluginPath[MAX_PATH] = { 0 };
		wchar_t iniFile[] = L"x64rdbg.ini";

		GetModuleFileNameW(hinst, pluginPath, MAX_PATH);
		wcsncpy_s(wcsrchr(pluginPath, L'\\') + 1, _countof(iniFile), iniFile, _countof(pluginPath));
		wcsncpy_s(g_iniPath, _countof(pluginPath), pluginPath, _countof(g_iniPath));
	}

	return TRUE;
}