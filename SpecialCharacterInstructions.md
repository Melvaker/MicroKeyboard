# Using Special Characters
For more information, see the [Arduino Documentation](https://www.arduino.cc/en/Reference/KeyboardModifiers).
For more information on the ASCII character set, see [asciitable.com](asciitable.com).

# Instructions
To use the a modifier key in the controller, follow one of two methods below.

Method 1: Enter the modifier key in the array without any single or double quotation marks.
Ex: `const char KEYS[] = {KEY_ESC};`

Method 2: The value from the ASCII table may also be used without any quotation marks.
Ex: `const char KEYS[] = {177};`

## Modifier Keys
- KEY_LEFT_CTRL
- KEY_LEFT_SHIFT
- KEY_LEFT_ALT
- KEY_LEFT_GUI
- KEY_RIGHT_CTRL
- KEY_RIGHT_SHIFT
- KEY_RIGHT_ALT
- KEY_RIGHT_GUI

## Special Keys
- KEY_TAB
- KEY_CAPS_LOCK
- KEY_BACKSPACE
- KEY_RETURN
- KEY_MENU

## Navigation Cluster
- KEY_INSERT
- KEY_DELETE
- KEY_HOME
- KEY_END
- KEY_PAGE_UP
- KEY_PAGE_DOWN
- KEY_UP_ARROW
- KEY_DOWN_ARROW
- KEY_LEFT_ARROW
- KEY_RIGHT_ARROW

## Numeric Keypad
- KEY_NUM_LOCK
- KEY_KP_SLASH
- KEY_KP_ASTERISK
- KEY_KP_MINUS
- KEY_KP_PLUS
- KEY_KP_ENTER
- KEY_KP_1
- KEY_KP_2
- KEY_KP_3
- KEY_KP_4
- KEY_KP_5
- KEY_KP_6
- KEY_KP_7
- KEY_KP_8
- KEY_KP_9
- KEY_KP_0
- KEY_KP_DOT

## Escape and Function Keys
- KEY_ESC
- KEY_F1
- KEY_F2
- KEY_F3
- KEY_F4
- KEY_F5
- KEY_F6
- KEY_F7
- KEY_F8
- KEY_F9
- KEY_F10
- KEY_F11
- KEY_F12
- KEY_F13
- KEY_F14
- KEY_F15
- KEY_F16
- KEY_F17
- KEY_F18
- KEY_F19
- KEY_F20
- KEY_F21
- KEY_F22
- KEY_F23
- KEY_F24

## Function Control Keys
- KEY_PRINT_SCREEN
- KEY_SCROLL_LCOK
- KEY_PAUSE