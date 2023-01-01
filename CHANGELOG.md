# Version 1.5.0 - 01 Jan 2023
## Features
- Added dual input method mode.

## Bug Fixes
- Firmware now reads multiple shift registers correctly.

# Version 1.4.1 - 25 Nov 2022
## Features
- Added togglable debug mode.

# Version 1.4.0 - 24 Nov 2022
## Features
- Added Arduino onboard pin only.
- Added support for external hardware.
- Added external harware only mode.

# Version 1.3.1 - 22 Nov 2022
## Documentation
- Extended special key value table.

# Version 1.3.0 - 22 Nov 2022
## Optimizations
- Removed blocking delay function.
- Added time elapsed check for UPS limiting.

# Version 1.2.0 - 21 Nov 2022
## Features
- Reduced dual arrays to single array of KeyPair structure for ease of setup and maintenance.

## Optimizations
- Updated PressKey function to incorporate lastActive to reduce extraneous key presses sent to the computer.
- Updated ReleaseKey function to incorporate lastActive to reduce extraneous key presses sent to the computer.

# Version 1.1.1 - 21 Nov 2022
## Documentation
- Added additional special keys to SpecialCharacterInstructions.
- Updated code comments.

# Version 1.1.0 - 28 Mar 2022
## Features
- Now supports up to 64 keyboard keys.

## Documentation
- Updated documentation.
  - Updated code comments.
  - Updated README.
  - Added SpecialCharactersInstructions.

# Version 1.0.0 - 27 Mar 2022
## Features
- Emulates up to 32 keyboard keys.