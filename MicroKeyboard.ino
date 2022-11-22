// --------------------------------------------------------------------------------
// Arduino Micro Keyboard Emulator

// Keyboard emulation with Arduino Micro.

// Version: 1.1.0
// Last Modified: 28 Mar 2022
// Created: 27 Mar 2022
// Author: Melvaker

// https://www.github.com/Melvaker/MicroKeyboard

// Please Note:
// - The number of inputs are limited by the number of digital inputs of your
//   selected board.
// - Updates are planned to allow for hardware expansion.
// - This firmware currenly supports up to 64 keyboard keys.
// - This firmware features 6 key rollover due to library limits.
// --------------------------------------------------------------------------------

// ================================================================================
// =============================  Settings and Stuff  =============================
// ================================================================================

// ===== Including and Setting Up Keyboard Library =====
#include "Keyboard.h"

// ===== Pin and Keys Definitions =====
// Create up to 64 key binds by extending the PINS and KEYS Arrays. 
// --- CAUTION ---
// If there are different number of defined pins and keys the arduino will
//   enter a locked state to prevent unexpected or undesirable behavior. 
// For more details on using Keyboard Modifier keys, please see
//   SpecialCharacterInstructions.md.

const byte PINS[] = {2, 3, 4, 5, 6};
const char KEYS[] = {'w', 'a', 's', 'd', ' '};

// ===== MISC Settings =====
// Controller delay regulates how fast the microcontroller sends updates to the
//   computer.
// Adjust this value to get the desired controller responsiveness.
const int controllerDelay = 50;
// Common Values:
// - 50 ms = 20 updates per second
// - 40 ms = 25 updates per second
// - 30 ms ~ 33 updates per second
// - 20 ms = 50 updates per second
// - 16 ms ~ 62 updates per second

// --- CAUTION ---
// Changes below this line are not advised.
// ================================================================================
// ==============================      FIRMWARE      ==============================
// ================================================================================

// ===== Working Data =====
byte buttonCount = 0;
uint64_t activePins = 0;
uint64_t lastActive = 0;

void setup()
{
  //Verify Pin and Key counts match.
  buttonCount = sizeof(PINS)/sizeof(PINS[0]);

  if(sizeof(KEYS)/sizeof(KEYS[0]) != buttonCount)
  {
    SafetyLock();
  }
  
  for(int i = 0; i < buttonCount; i++)
  {
    pinMode(PINS[i], INPUT_PULLUP);
  }

  Keyboard.begin();
}

void loop()
{
  ReadButtons();
  ReleaseKeys();
  PressKeys();

  lastActive = activePins;

  delay(controllerDelay);
}

void PressKeys()
{
  for(int i = 0; i < buttonCount; i++)
  {
    if(activePins & (1 << i))
    {
      Keyboard.press(KEYS[i]);
    }
  }
}

void ReadButtons()
{
  for(int i = 0; i < buttonCount; i++)
  {
    if(!digitalRead(PINS[i]))
    {
      activePins |= 1 << i;
    }
    else
    {
      activePins &= ~(1 << i);
    }
  }
}

void ReleaseKeys()
{
  for(int i = 0; i < buttonCount; i++)
  {
    if(!(activePins & (1 << i)))
    {
      Keyboard.release(KEYS[i]);
    }
  }
}

void SafetyLock()
{
  while(true) { delay(500); }
}
