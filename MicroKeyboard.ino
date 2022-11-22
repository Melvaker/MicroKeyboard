// --------------------------------------------------------------------------------
// Arduino Micro Keyboard Emulator

// Keyboard emulation with Arduino Micro.

// Version: 1.3.0
// Last Modified: 22 Nov 2022
// Created: 27 Mar 2022
// Author: Melvaker

// https://www.github.com/Melvaker/MicroKeyboard

// Please Note:
// - The number of inputs are limited by the number of digital inputs of your
//   selected board.
// - Updates are planned to allow for hardware expansion.
// - This firmware currenly supports up to 64 keyboard keys.
// - This firmware features 6 key rollover due to Keyboard library design.
// --------------------------------------------------------------------------------

// ===== Data Structures =====
// --- CAUTION: Do not make changes this section. ---
struct KeyPair
{
  uint8_t pinID;
  char key;
};

// ================================================================================
// =============================  Settings and Stuff  =============================
// ================================================================================

// ===== Including and Setting Up Keyboard Library =====
#include "Keyboard.h"

// ===== Pin and Keys Definitions =====
// Create up to 64 key binds by extending the KEYS Arrays.
// For more details on using Keyboard Modifier keys, please see
//   SpecialCharacterInstructions.md.

const KeyPair KEYS[] = 
{
  {2, 'w'},
  {3, 'a'},
  {4, 's'},
  {5, 'd'},
  {6, KEY_LEFT_SHIFT}
};

// ===== MISC Settings =====
// PERIOD regulates how fast the microcontroller sends updates to the
//   computer.
// Adjust this value to get the desired controller responsiveness.
const int PERIOD = 50;
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
uint32_t lastTime = 0;

void setup()
{ 
  //Calculate number of buttons.
  buttonCount = sizeof(KEYS)/sizeof(KEYS[0]);
  
  for(int i = 0; i < buttonCount; i++)
  {
    pinMode(KEYS[i].pinID, INPUT_PULLUP);
  }

  Keyboard.begin();
}

void loop()
{
  if(millis() > lastTime + PERIOD)
  {
    ReadButtons();
    ReleaseKeys();
    PressKeys();

    lastActive = activePins;
    lastTime = millis();
  }
}

void PressKeys()
{
  for(int i = 0; i < buttonCount; i++)
  {
    //if(key was not previously pressed && key is currently pressed) 
    if(!(lastActive & (1 << i)) && activePins & (1 << i))
    {
      Keyboard.press(KEYS[i].key);
    }
  }
}

void ReadButtons()
{
  for(int i = 0; i < buttonCount; i++)
  {
    //if(pin is low -> key is pressed) set bit high
    if(!digitalRead(KEYS[i].pinID))
    {
      activePins |= 1 << i;
    }
    //if(pin is high -> key not pressed) set bit low
    //do not change other high bits
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
    //if(key was previously pressed && key is not currently pressed)
    if((lastActive & (1 << i)) && !(activePins & (1 << i)))
    {
      Keyboard.release(KEYS[i].key);
    }
  }
}