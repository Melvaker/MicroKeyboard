// --------------------------------------------------------------------------------
// Arduino Micro Keyboard Emulator
// The repository can be found at https://www.github.com/Melvaker/MicroKeyboard
//
// Please Note:
// - The number of inputs are limited by the number of digital inputs of your
//   selected board.
// - This firmware currenly supports up to 64 keyboard keys.
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
