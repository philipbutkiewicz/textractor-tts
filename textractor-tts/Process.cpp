#pragma once

#include "Process.h"

std::string ProcessIDToProcessImageName(std::uint32_t pid)
{

    std::string result = "UNKNOWN";

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess != NULL) {
        char buf[MAX_PATH];
        GetProcessImageFileNameA(hProcess, buf, MAX_PATH);
        result = std::string(buf);
        CloseHandle(hProcess);
    }

    return result;
}