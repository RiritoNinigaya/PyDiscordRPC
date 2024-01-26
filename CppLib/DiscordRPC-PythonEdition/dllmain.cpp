// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <discord_register.h>
#include <discord_rpc.h>
#define DLLEXPORT extern "C" __declspec(dllexport)
int64_t TimeNow = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
DLLEXPORT void SetDiscordRPC(const char* id, const char* state, const char* details, const char* largeKeyImage, const char* largeText, const char* smallImageText) {
	bool initRPC = true;
	DiscordEventHandlers hand = DiscordEventHandlers();
	memset(&hand, 0, sizeof(hand));
	Discord_Initialize(id, &hand, 1, "0");
	if (initRPC)
	{
		DiscordRichPresence rich = DiscordRichPresence();
		memset(&rich, 0, sizeof(rich));
		rich.state = state;
		rich.details = details;
		rich.startTimestamp = TimeNow;
		rich.endTimestamp = NULL; //NULL it's UNLIMITED END TIMESTAMP!!!!.
		rich.largeImageKey = largeKeyImage;
		rich.largeImageText = largeText;
		rich.smallImageText = smallImageText;

		Discord_UpdatePresence(&rich);
	}
	else
	{
		MessageBoxA(0, "Failed to Allocate Memory or bool not worked!!!", "DiscordRPC PyEdition", MB_ICONERROR | MB_OK);
	}

}
DLLEXPORT void ShutdownDiscordRPC() {
	Discord_ClearPresence();
	Discord_Shutdown();

}
DLLEXPORT int64_t GetTime() {
    return TimeNow;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

