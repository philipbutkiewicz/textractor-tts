#include "Extension.h"

ISpVoice* spVoice = NULL;
std::list<GameFilter*> gameFilters;


BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		::CoInitialize(NULL);
		if (!InitializeVoice())
		{
			MessageBoxW(NULL, L"Failed to initialize the TTS engine!", L"textractor-tts", MB_OK);
			return FALSE;
		}

		break;
	case DLL_PROCESS_DETACH:
		UninitializeVoice();
		::CoUninitialize();
		break;
	}
	return TRUE;
}

bool Initialize()
{
	if (!InitializeVoice())
	{
		return FALSE;
	}

	InitializeGameFilters();

	return TRUE;
}

bool InitializeVoice()
{
	if (spVoice != NULL)
	{
		return FALSE;
	}

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&spVoice);
	if (!SUCCEEDED(hr))
	{
		MessageBoxW(NULL, L"COM object failed to initialize!", L"textractor-tts", MB_OK);
		return FALSE;
	}

	ISpObjectToken* pVoiceToken = NULL;
	hr = SpFindBestToken(SPCAT_VOICES, L"Language=411", NULL, &pVoiceToken);
	if (SUCCEEDED(hr))
	{
		spVoice->SetVoice(pVoiceToken);
		spVoice->SetVolume(255);
		pVoiceToken->Release();
	}
	else
	{
		MessageBoxW(NULL, L"Failed to set Japanese voice engine!", L"textractor-tts", MB_OK);
		return FALSE;
	}

	return TRUE;
}

void InitializeGameFilters()
{
	GameFilterRewritePlus* gameFilterRewritePlus = new GameFilterRewritePlus();
	gameFilters.push_back(gameFilterRewritePlus);
}

void UninitializeVoice()
{
	spVoice->Release();
	spVoice = NULL;
}

bool ProcessSentence(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	for (GameFilter* gameFilter : gameFilters)
	{
		gameFilter->UpdateFilter(sentence, sentenceInfo);
	}

	if (sentenceInfo["current select"])
	{
		if (spVoice == NULL)
		{
			InitializeVoice();
		}

		bool shouldSpeak = TRUE;
		for (GameFilter* gameFilter : gameFilters)
		{
			if (!gameFilter->GetFilterResult(sentence, sentenceInfo))
			{
				shouldSpeak = FALSE;
			}
		}

		if (shouldSpeak)
		{
			spVoice->Speak(sentence.c_str(), 0, NULL);
		}
	}

	return TRUE;
}