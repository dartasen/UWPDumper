#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <chrono>

#include <windows.h>
#include <psapi.h> //GetModuleFileNameEx
#include <TlHelp32.h>

// Setting DLL access controls
#include <AccCtrl.h>
#include <Aclapi.h>
#include <Sddl.h>

// UWP
#include <atlbase.h>
#include <appmodel.h>

#include <UWP/DumperIPC.hpp>

/* **********************************************************************************************************************************************
 *  PROTOYPES
 * ********************************************************************************************************************************************** */

void SetAccessControl(const std::wstring& ExecutableName, const wchar_t* AccessString);
bool DLLInjectRemote(uint32_t ProcessID, const std::wstring& DLLpath);
std::wstring GetRunningDirectory();
void DisplayRunningUWPApps();
void SetupConsole();

/* **********************************************************************************************************************************************
 *  USINGS
 * ********************************************************************************************************************************************** */

using ThreadCallback = bool(*)(std::uint32_t ThreadID, void* Data);