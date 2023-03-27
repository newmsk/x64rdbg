#include "plugin.h"
#include "server.h"

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    HANDLE x64rdbg_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Run, 0, 0, 0);
    if (!x64rdbg_thread)
        return false;
    CloseHandle(x64rdbg_thread);
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}
