// --------------------------------------------------------------------------------
// Arduino Micro Keyboard Emulator
// This sketch file has only been tested with the Arduino Micro.
//
// Please Note:
// - The number of inputs are limited by the number of digital inputs of your
//   selected board.
// - This firmware currenly only supports up to 32 keyboard keys.
// --------------------------------------------------------------------------------

// ================================================================================
// =============================  Settings and Stuff  =============================
// ================================================================================

// ===== Including and Setting Up Keyboard Library =====
#include "Keyboard.h"

// ===== Pin and Keys Definitions =====
// Create up to 32 key binds by extending the PINS and KEYS Arrays. 
// --- CAUTION ---
// If there are different number of defined pins and keys the arduino will
//   enter a locked state until reset. 

const byte PINS[] = {2, 3, 4, 5, 6};
const char KEYS[] = {'w', 'a', 's', 'd', ' '};

// ===== MISC Settings =====
// Controller delay regulates how fast the microcontroller sends updates to the
//   computer.
const int controllerDelay = 50;

// ================================================================================
// ==============================      FIRMWARE      ==============================
// ================================================================================

// ===== Working Data =====
byte buttonCount = 0;
unsigned long activePins = 0;
unsigned long lastActive = 0;

void setup()
{
  //Verify Pin and Key counts match.
  buttonCount = sizeof(PINS)/sizeof(PINS[0]);

  if(sizeof(KEYS)/sizeof(KEYS[0]) != buttonCount)
  {
    SafetyLock();
  }

  //Verifying each button has a 
  
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
