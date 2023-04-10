#pragma once

#include "Textractor.h"
#include "Process.h"

class GameFilter
{
public:
	virtual void UpdateFilter(std::wstring& sentence, SentenceInfo sentenceInfo)
	{
		// Do nothing
	}
	virtual bool GetFilterResult(std::wstring& sentence, SentenceInfo sentenceInfo)
	{
		return TRUE;
	}
	virtual bool CheckProcessId(std::uint32_t pid, std::string targetProcessImageName)
	{
		std::string processImageName = ProcessIDToProcessImageName(pid);
		if (processImageName.find(targetProcessImageName) == std::string::npos) {
			return FALSE;
		}

		return TRUE;
	}
};

