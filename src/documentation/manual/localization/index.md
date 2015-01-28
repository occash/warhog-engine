# Localization

Warhog engine is designed so it can be adapted to different languages and regional differences without changes in code.
The editor has built-in localization support.

## Producing translations

The editor will automatically produce the translation project for you. 
It contains symbol database, sounds, videos and fonts.
This project can be easily opened with localization app.

### Scripts
Use `tr` function in your script to make strings available for localization.
Example
```
local dialogs = {
	tr('say_hello'),
	tr('trade'),
	...
}
```

### GUI
The Warhog GUI system is aware of language changes. It will automatically retranslate all visual elements.
The text property of TextRenderer will also be retranslated.

### Audio and Video
Check the `localized` property to make audio/video available for localization.

	Note: the text in pre-rendered videos cannot be localized.

### Fonts
Font will be imported for localization.

## Enable translation
You can enable translation in project settings.

## Relevant scripting API
| API    | Description                      |
| ------ | -------------------------------- |
| tr()   | Returns translation for the key. |
| Locale | Locale specific functions        |