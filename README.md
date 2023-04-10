# textractor-tts

A Text-To-Speech plugin for [Textractor](https://github.com/Artikash/Textractor).


## Limitations
1. Will only work with Microsoft Ayumi TTS voice already installed on the system.
2. The extension is not configurable, it will blindly read any text from a currently selected hook unless a filter for a specific game is implemented.

## Available filters
These games have a proper filter built for them and the plugin will only read unvoiced text when a filter is available.
- Rewrite+

## Contributing

If you'd like to contribute, simply submit a pull request. Here is a list of things that I'd like to be eventually done:

- Configuration UI (select voice, enable/disable filters)
- Support for TTS engines other than MS SAPI 5.3
- Filters for more games