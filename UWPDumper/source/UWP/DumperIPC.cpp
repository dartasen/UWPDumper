#include "UWP/DumperIPC.hpp"
#include "UWP/AtomicQueue.hpp"

namespace IPC
{
#pragma data_seg("SHARED")
	AtomicQueue<MessageEntry, 1024> MessagePool = {};
	std::atomic<std::size_t> CurMessageCount = 0;

	// The process we are sending our data to
	std::atomic<std::uint32_t> ClientProcess(0);

	// The target UWP process we wish to dump
	std::atomic<std::uint32_t> TargetProcess(0);

	std::atomic<std::int32_t> TargetThread(InvalidThread);

#pragma data_seg()
#pragma comment(linker, "/section:SHARED,RWS")

	void SetClientProcess(std::uint32_t ProcessID)
	{
		ClientProcess.store(ProcessID);
	}

	std::uint32_t GetClientProcess()
	{
		return ClientProcess.load();
	}

	void SetTargetProcess(std::uint32_t ProcessID)
	{
		TargetProcess.store(ProcessID);
	}

	std::uint32_t GetTargetProcess()
	{
		return TargetProcess.load();
	}

	void SetTargetThread(std::int32_t ThreadID)
	{
		TargetThread.store(ThreadID);
	}

	std::int32_t GetTargetThread()
	{
		return TargetThread.load();
	}

	void ClearTargetThread()
	{
		TargetThread.store(InvalidThread);
	}

	void PushMessage(const wchar_t* Format, ...)
	{
		std::va_list Args;
		MessageEntry Entry;

		va_start(Args, Format);
		vswprintf_s(Entry.String, Entry.StringSize, Format, Args);
		va_end(Args);

		MessagePool.Enqueue(Entry);
	}

	std::wstring PopMessage()
	{
		const MessageEntry Entry = MessagePool.Dequeue();

		return std::wstring(Entry.String, wcslen(Entry.String));
	}

	std::size_t MessageCount()
	{
		return MessagePool.Size();
	}
}