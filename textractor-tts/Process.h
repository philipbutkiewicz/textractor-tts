#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <Psapi.h>

std::string ProcessIDToProcessImageName(std::uint32_t pid);