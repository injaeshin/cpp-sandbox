#pragma once

#include "Windows.h"
#include "dbghelp.h"

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

//#pragma comment(lib, "dbghelp.lib")
//#pragma warning(disable: 4996)

typedef struct _DUMP_PARAMETER
{
	HANDLE Thread;
	PEXCEPTION_POINTERS ExPtrs;
} DUMP_PARAMETER, *PDUMP_PARAMETER;

class MiniDump
{
public:
	static DWORD WINAPI WriteDump(LPVOID param)
	{
		PDUMP_PARAMETER dp = reinterpret_cast<PDUMP_PARAMETER>(param);

		auto hDbgHelp = LoadLibraryA("dbghelp");
		if (hDbgHelp == nullptr)
			return EXCEPTION_CONTINUE_SEARCH;

		auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump))GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
		if (pMiniDumpWriteDump == nullptr)
			return EXCEPTION_CONTINUE_SEARCH;

		std::string folder = "dump";
		CreateDirectoryA(folder.c_str(), nullptr);

		auto now = std::chrono::system_clock::now();
		auto now_time_t = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm = {};
		localtime_s(&now_tm, &now_time_t);
		std::ostringstream timefmt;
		timefmt << std::put_time(&now_tm, "%Y%m%d-%H%M%S");

		std::ostringstream f;
		f << folder << "\\" << "dump-" << timefmt.str() << ".dmp";

		std::string filename = f.str();
		auto hFile = CreateFileA(filename.c_str(), GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if (hFile == INVALID_HANDLE_VALUE)
			return EXCEPTION_CONTINUE_SEARCH;

		MINIDUMP_EXCEPTION_INFORMATION mei{};
		mei.ThreadId = GetThreadId(dp->Thread);
		mei.ExceptionPointers = dp->ExPtrs;
		mei.ClientPointers = FALSE;

		auto dumped = pMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile,
			MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
			dp ? &mei : nullptr, nullptr, nullptr);

		CloseHandle(hFile);

		return EXCEPTION_EXECUTE_HANDLER;
	}


	static LONG WINAPI UnHandledExceptionFilter(_EXCEPTION_POINTERS* exPtrs)
	{
		if (IsDebuggerPresent())
			return EXCEPTION_CONTINUE_SEARCH;

		PDUMP_PARAMETER dumpParam = (PDUMP_PARAMETER)malloc(sizeof(DUMP_PARAMETER));
		dumpParam->Thread = GetCurrentThread();
		dumpParam->ExPtrs = exPtrs;

		if (exPtrs->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
		{
			HANDLE hThread = CreateThread(NULL, 102400, WriteDump, dumpParam, 0, NULL);
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		}
		else
		{
			WriteDump(dumpParam);
		}

		return EXCEPTION_EXECUTE_HANDLER;
	};

	static VOID Init()
	{
		SetErrorMode(SEM_FAILCRITICALERRORS);

		SetUnhandledExceptionFilter(UnHandledExceptionFilter);
	};
}; #pragma once
