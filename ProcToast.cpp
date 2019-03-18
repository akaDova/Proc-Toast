#include "pch.h"
#include <iostream>
#include <Windows.h>


int main(int argc, char **args)
{
	std::string cmdLine = "";
	for (int i = 1; i < argc; i++) {
		std::cout << args[i] << std::endl;
		cmdLine += args[i];
		cmdLine += " ";
	}
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	LPSTR cmdLine_p = const_cast<char *>(cmdLine.c_str());
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	printf_s("cmdLine_p: %s\n", cmdLine_p);
	if (!CreateProcessA(NULL,   // No module name (use command line)
		cmdLine_p,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf_s("CreateProcess failed (%d).\n", GetLastError());
		return 1;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	MessageBoxA(NULL, cmdLine.c_str(), ("command line"), MB_OK);

	

	return 0;
}

