#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <stdlib.h>

using namespace std;

DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID) {
    DWORD dwModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID); // make snapshot of all modules within process
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &ModuleEntry32)) //store first Module in ModuleEntry32
    {
        do {
            if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) // if Found Module matches Module we look for -> done!
            {
                dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &ModuleEntry32)); // go through Module entries in Snapshot and store in ModuleEntry32


    }
    CloseHandle(hSnapshot);
    return dwModuleBaseAddress;
}

DWORD GetPointerAddress(HWND hwnd, DWORD gameBaseAddr, DWORD address, vector<DWORD> offsets)
{
    DWORD pID = NULL; // Game process ID
    GetWindowThreadProcessId(hwnd, &pID);
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if (phandle == INVALID_HANDLE_VALUE || phandle == NULL);

    DWORD offset_null = NULL;
    ReadProcessMemory(phandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
    DWORD pointeraddress = offset_null; // the address we need
    for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
    {
        ReadProcessMemory(phandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }
    return pointeraddress += offsets.at(offsets.size() - 1); // adding the last offset
}

int main()
{
    HWND hwnd = FindWindowA(NULL, "AssaultCube");

    if (hwnd != FALSE);
    DWORD pID = NULL;
    GetWindowThreadProcessId(hwnd, &pID);
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if (phandle == INVALID_HANDLE_VALUE || phandle == NULL);

    char gamemodule1[] = "ac_client.exe";
    DWORD gamebaseaddress1 = GetModuleBaseAddress(_T(gamemodule1), pID); //Getting the module Base Address\


    // Rifle Ammo
    DWORD rifleammoAddr = 0x0017E0A8;
    vector<DWORD> rifleammoOffsets{ 0x140 };
    DWORD rifleammoPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, rifleammoAddr, rifleammoOffsets);


    // Pistol Ammo
    DWORD pistolammoAddr = 0x0018AC00;
    vector<DWORD> pistolammoOffsets{ 0x12C };
    DWORD pistolammoPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, pistolammoAddr, pistolammoOffsets);
    

    // DoublePistol
    DWORD dblpistolAddr = 0x0017E0A8;
    vector<DWORD> dblpistolOffsets{ 0x100 };
    DWORD dblpistolPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, dblpistolAddr, dblpistolOffsets);


    // DoublePistol Ammo
    DWORD dblpistolammoAddr = 0x0017E0A8;
    vector<DWORD> dblpistolammoOffsets{ 0x148 };
    DWORD dblpistolammoPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, dblpistolammoAddr, dblpistolammoOffsets);


    // Granade
    DWORD granadeAddr = 0x0017E0A8;
    vector<DWORD> granadeOffsets{ 0x144 };
    DWORD granadePtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, granadeAddr, granadeOffsets);


    // Heatlh
    DWORD healthAddr = 0x0017E0A8;
    vector<DWORD> healthOffsets{ 0xEC };
    DWORD healthPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, healthAddr, healthOffsets);


    // Armor
    DWORD armorAddr = 0x0017E0A8;
    vector<DWORD> armorOffsets{ 0xF0 };
    DWORD armorPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, armorAddr, armorOffsets);


    // ZX1
    DWORD zx1Addr = 0x0017E0A8;
    vector<DWORD> zx1Offsets{ 0x2C };
    DWORD zx1PtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, zx1Addr, zx1Offsets);


    // ZX2
    DWORD zx2Addr = 0x0017E0A8;
    vector<DWORD> zx2Offsets{ 0x28 };
    DWORD zx2PtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, zx2Addr, zx2Offsets);


    // Y
    DWORD YAddr = 0x0017E0A8;
    vector<DWORD> YOffsets{ 0x30 };
    DWORD YPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, YAddr, YOffsets);


    // Gravitation
    DWORD GravitationAddr = 0x0017E0A8;
    vector<DWORD> GravitationOffsets{ 0x5C };
    DWORD GravitationPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, GravitationAddr, GravitationOffsets);


    // ZX PosVision
    DWORD ZXPosVisionAddr = 0x0017E0A8;
    vector<DWORD> ZXPosVisionOffsets{ 0x34 };
    DWORD ZXPosVisionPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, ZXPosVisionAddr, ZXPosVisionOffsets);


    // Y PosVision
    DWORD YPosVisionAddr = 0x0017E0A8;
    vector<DWORD> YPosVisionOffsets{ 0x38 };
    DWORD YPosVisionPtrAddr = GetPointerAddress(hwnd, gamebaseaddress1, YPosVisionAddr, YPosVisionOffsets);


    while (true) { // MEMORY EDITING
        int nubmer = 1337;
        int infdblpistol = 1;
        int null = -1;
        float number2;
        float zxPosVision;
        float yPosVision;

        WriteProcessMemory(phandle, (LPVOID*)(rifleammoPtrAddr), &nubmer, 4, 0);
        WriteProcessMemory(phandle, (LPVOID*)(pistolammoPtrAddr), &nubmer, 4, 0);
        WriteProcessMemory(phandle, (LPVOID*)(dblpistolPtrAddr), &infdblpistol, 4, 0);
        WriteProcessMemory(phandle, (LPVOID*)(dblpistolammoPtrAddr), &nubmer, 4, 0);
        WriteProcessMemory(phandle, (LPVOID*)(healthPtrAddr), &nubmer, 4, 0);
        WriteProcessMemory(phandle, (LPVOID*)(granadePtrAddr), &nubmer, 4, 0);
        WriteProcessMemory(phandle, (LPVOID*)(armorPtrAddr), &nubmer, 4, 0);

        if (GetAsyncKeyState(0x58) & 0x8000) { // NOCLIP
            ReadProcessMemory(phandle, (LPVOID*)(ZXPosVisionPtrAddr), &zxPosVision, sizeof(float), 0);
            ReadProcessMemory(phandle, (LPVOID*)(YPosVisionPtrAddr), &yPosVision, sizeof(float), 0);

            if (GetAsyncKeyState(0x57) & 0x8000) { // W
                if (zxPosVision <= 230 && zxPosVision >= 130) {
                    ReadProcessMemory(phandle, (LPVOID*)(GravitationPtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(GravitationPtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
                else if (zxPosVision <= 130 && zxPosVision >= 30) { // in A
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
                else if (zxPosVision >= 320 || zxPosVision <= 30) { // in S
                    ReadProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
                else if (zxPosVision <= 320 && zxPosVision >= 230) { // in D
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
            }
            
            if (GetAsyncKeyState(0x53) & 0x8000) { // S
                if (zxPosVision <= 230 && zxPosVision >= 130) {
                    ReadProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
                else if (zxPosVision <= 320 && zxPosVision >= 230) { // in A
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
                else if (zxPosVision <= 130 && zxPosVision >= 30) { // in D
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
                else if (zxPosVision >= 320 || GetAsyncKeyState(0x53) & 0x8000 && zxPosVision <= 30) { // in W
                    ReadProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);

                    Sleep(20);
                }
            }
     
            if (GetAsyncKeyState(0x41) & 0x8000) { // A
                if (zxPosVision <= 230 && zxPosVision >= 130) {
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                }
                else if (zxPosVision <= 130 && zxPosVision >= 30) { // in S
                    ReadProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                }
                else if (zxPosVision >= 320 || zxPosVision <= 30) { // in D
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                }
                else if (zxPosVision <= 320 && zxPosVision >= 230) { // in W
                    ReadProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                }
                Sleep(20);
            }

            if (GetAsyncKeyState(0x44) & 0x8000) { // D
                if (zxPosVision <= 230 && zxPosVision >= 130) {
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                }
                else if (zxPosVision <= 130 && zxPosVision >= 30) { // W
                    ReadProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                }
                else if (zxPosVision >= 320 || zxPosVision <= 30) { // A
                    ReadProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                    number2 += 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx2PtrAddr), &number2, sizeof(float), 0);
                }
                else if (zxPosVision <= 320 && zxPosVision >= 230) { // S
                    ReadProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                    number2 -= 1.0f;
                    WriteProcessMemory(phandle, (LPVOID*)(zx1PtrAddr), &number2, sizeof(float), 0);
                }
                Sleep(20);
            }

            else if (GetAsyncKeyState(0x20) & 0x8000) { // SPACE
                ReadProcessMemory(phandle, (LPVOID*)(YPtrAddr), &number2, sizeof(float), 0);
                number2 += 1.0f;
                WriteProcessMemory(phandle, (LPVOID*)(YPtrAddr), &number2, sizeof(float), 0);

                Sleep(20);
            }
            else if (GetAsyncKeyState(0xA2) & 0x8000) { // CTRL
                ReadProcessMemory(phandle, (LPVOID*)(YPtrAddr), &number2, sizeof(float), 0);
                number2 -= 1.0f;
                WriteProcessMemory(phandle, (LPVOID*)(YPtrAddr), &number2, sizeof(float), 0);

                Sleep(20);  
            }

            Sleep(1);
        }
    }

    return 0;
}