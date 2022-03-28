# Using Special Characters
For more information, see the [Arduino Documentation](https://www.arduino.cc/en/Reference/KeyboardModifiers).
For more information on the ASCII character set, see [asciitable.com](asciitable.com).

# Instructions
To use the escape key in the controller, follow the instructions below. 

Enter the modifier key in the array without any single or double quotation marks.
Ex: `const char KEYS[] = {'w', KEY_ESC};`

The value from the ASCII table may also be used without any quotation marks.
Ex: `const char KEYS[] = {'w', 177};`

# Modifier Keys
- KEY_LEFT_CTRL
- KEY_LEFT_SHIFT
- KEY_LEFT_ALT
- KEY_LEFT_GUI
- KEY_RIGHT_CTRL
- KEY_RIGHT_SHIFT
- KEY_RIGHT_ALT
- KEY_RIGHT_GUI
- KEY_UP_ARROW
- KEY_DOWN_ARROW
- KEY_LEFT_ARROW
- KEY_RIGHT_ARROW
- KEY_BACKSPACE
- KEY_TAB
- KEY_RETURN
- KEY_ESC
- KEY_INSERT
- KEY_DELETE
- KEY_PAGE_UP
- KEY_PAGE_DOWN
- KEY_HOME
- KEY_END
- KEY_CAPS_LOCK
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