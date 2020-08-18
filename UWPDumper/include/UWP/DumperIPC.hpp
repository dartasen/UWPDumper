#pragma once

#include <array>
#include <atomic>
#include <thread>
#include <cstdarg>
#include <cstdint>
#include <cstddef>
#include <string>

#ifdef IPC_EXPORT
#define IPC_API __declspec(dllexport)
#else
#define IPC_API __declspec(dllimport)
#endif

namespace IPC
{
	/************************************************************************************************************************************************
	*  TYPES
	*********************************************************************************************************************************************** */

	struct MessageEntry
	{
		static constexpr std::size_t StringSize = 1024;
		wchar_t String[StringSize];

		MessageEntry() : String(L"")
		{

		}

		explicit MessageEntry(const wchar_t* String)
		{
			wcscpy_s(this->String, MessageEntry::StringSize, String);
		}

		~MessageEntry() = default;
	};

	/************************************************************************************************************************************************
	*  PROTOTYPES
	************************************************************************************************************************************************ */

	void IPC_API SetClientProcess(std::uint32_t ProcessID);
	std::uint32_t IPC_API GetClientProcess();
	void IPC_API SetTargetProcess(std::uint32_t ProcessID);
	std::uint32_t IPC_API GetTargetProcess();

	constexpr std::int32_t InvalidThread = -1;

	void IPC_API SetTargetThread(std::int32_t ThreadID);
	std::int32_t IPC_API GetTargetThread();
	void IPC_API ClearTargetThread();

	void IPC_API PushMessage(const wchar_t* Format, ...);
	std::wstring IPC_API PopMessage();
	std::size_t IPC_API MessageCount();
}