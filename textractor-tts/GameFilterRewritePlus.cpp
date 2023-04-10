#include "GameFilterRewritePlus.h"

bool isMainCharacter = FALSE;

void GameFilterRewritePlus::UpdateFilter(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	if (!GameFilter::CheckProcessId(sentenceInfo["pid"], REWRITE_PLUS_PROCESS_NAME)) return;

	if (sentence.find(L"瑚太朗") != std::wstring::npos && !HasQuotes(sentence))
	{
		isMainCharacter = TRUE;
	}
}

bool GameFilterRewritePlus::GetFilterResult(std::wstring& sentence, SentenceInfo sentenceInfo) {
	if (!GameFilter::CheckProcessId(sentenceInfo["pid"], REWRITE_PLUS_PROCESS_NAME)) return TRUE;

	bool result = HasQuotes(sentence) || isMainCharacter;
	isMainCharacter = FALSE;

	return result;
}

bool GameFilterRewritePlus::HasQuotes(std::wstring& sentence) {
	return sentence.find(L"「") == std::wstring::npos && sentence.find(L"」") == std::wstring::npos;
}