#pragma once

#include "GameFilter.h"

#define REWRITE_PLUS_PROCESS_NAME "SiglusEngine.exe"

class GameFilterRewritePlus :
    public GameFilter
{
    void UpdateFilter(std::wstring& sentence, SentenceInfo sentenceInfo) override;
    bool GetFilterResult(std::wstring& sentence, SentenceInfo sentenceInfo) override;
    bool HasQuotes(std::wstring& sentence);
};

