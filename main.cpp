#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <float.h>
using namespace std;
 
DWORD WINAPI LoopFunction( LPVOID lpParam )
{
 
    BYTE StandingON[] = {0x8B, 0x02, 0x90};
    BYTE CrouchingON[] = {0x8B, 0x11, 0x90};
    BYTE ProneON[] = {0x8B, 0x08, 0x90};
    BYTE StandingOFF[] = {0x8B, 0x42, 0x4C};
    BYTE CrouchingOFF[] = {0x8B, 0x51, 0x50};
    BYTE ProneOFF[] = {0x8B, 0x48, 0x54};
 
    bool Crosshair = false;
 
    HANDLE bf2142 = GetCurrentProcess();
 
    while(1) {
        if (GetAsyncKeyState(VK_F1)&0x80000) {
            if (Crosshair == true) {
                WriteProcessMemory(bf2142, (void*)(0x05E2C88), &StandingOFF, 3, 0);
                WriteProcessMemory(bf2142, (void*)(0x05E2C93), &CrouchingOFF, 3, 0);
                WriteProcessMemory(bf2142, (void*)(0x05E2C9E), &ProneOFF, 3, 0);
                Crosshair = false;
 
            }
            else if( Crosshair == false) {
                WriteProcessMemory(bf2142, (void*)(0x05E2C88), &StandingON, 3, 0);
                WriteProcessMemory(bf2142, (void*)(0x05E2C93), &CrouchingON, 3, 0);
                WriteProcessMemory(bf2142, (void*)(0x05E2C9E), &ProneON, 3, 0);
                Crosshair = true;
            }
 
        }
    }
//some CPU relief
    Sleep(200);
    return 0;
}
 
BOOL WINAPI DllMain (HINSTANCE hModule, DWORD dwAttached, LPVOID lpvReserved)
{
    if (dwAttached == DLL_PROCESS_ATTACH) {
        CreateThread(NULL,0,&LoopFunction,NULL,0,NULL);
    }
    return 1;
}