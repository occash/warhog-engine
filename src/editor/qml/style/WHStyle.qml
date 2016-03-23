pragma Singleton
import QtQuick 2.3

WHTheme {
    property WHTheme darkTheme: WHDarkTheme {}
    property WHTheme lightTheme: WHLightTheme {}

    property WHTheme palette: darkTheme

    base: palette.base
    alternateBase: palette.alternateBase
    text: palette.text
    highlight: palette.highlight
    highlightedText: palette.highlightedText
    button: palette.button
    buttonText: palette.buttonText
    mid: palette.mid
    dark: palette.dark
}

