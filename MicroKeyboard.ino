// --------------------------------------------------------------------------------
// Arduino Micro Keyboard Emulator

// Keyboard emulation with Arduino Micro.

// Version: 1.4.1
// Last Modified: 25 Nov 2022
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

// ================================================================================
// ===================================  Setup  ====================================
// ================================================================================

// ===== Library Inclusion =====
// ===== Including and Setting Up Keyboard Library =====
#include "Keyboard.h"

// ===== Data Structures =====
// --- CAUTION: Do not make changes this section. ---
struct KeyPair
{
  uint8_t pinID;
  char key;
};

// ================================================================================
// =============================  Configuration  =============================
// ================================================================================

// ===== Hardware Configuration =====
// Select input mode by changeing mode value.
#define MODE 1
// Modes:
// - 0: Arduino onboard digital IO pins.
// - 1: External hardware. Currently only the 74HC165 is supported and tested.
//      54HC165 may also be compatible, but has not been tested.

// ===== Pin and Keys Definitions =====
// Create up to 64 key binds by extending the KEYS Arrays.
// For more details on using Keyboard Modifier keys, please see
//   SpecialCharacterInstructions.md.
#if MODE == 0
  //Change these definitions when using onboard DIO.
  const KeyPair KEYS[] = 
  {
    {2, 'w'},
    {3, 'a'},
    {4, 's'},
    {5, 'd'},
    {6, KEY_LEFT_SHIFT}
  };
#elif MODE == 1
  //Change these definitions when using external hardware.
  const char HARDWAREKEYS[] =
  {
    'w', 'a', 's', 'd',
    KEY_LEFT_SHIFT
  };
  
  //Change these definitions to match the wiring design.
  const byte LOADPIN = 2;
  const byte CLOCKPIN = 3;
  const byte DATAPIN = 4;
  const byte CLOCKENABLEPIN = 10;
#endif

// ===== Controller Timing =====
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

// ================================================================================
// ==============================      FIRMWARE      ==============================
// ================================================================================
// --- WARNING ---
// Changes below this line are not advised.

// ===== Debug Mode =====
//#define DEBUG

// ===== Working Data =====
#if MODE == 0
  byte buttonCount = 0;
#elif MODE == 1
  byte hardwareButtonCount = 0;
#endif

uint64_t activeKeys = 0;
uint64_t lastActive = 0;
uint32_t lastTime = 0;

void setup()
{ 
  #if MODE == 0
    //Calculate number of buttons.
    buttonCount = sizeof(KEYS)/sizeof(KEYS[0]);
    
    //Set pinModes.
    for(int i = 0; i < buttonCount; i++)
    {
      pinMode(KEYS[i].pinID, INPUT_PULLUP);
    }
  #elif MODE == 1  
    //Calculate number of buttons.
    hardwareButtonCount = sizeof(HARDWAREKEYS)/sizeof(HARDWAREKEYS[0]);
    
    //Set pinModes.
    pinMode(LOADPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, INPUT);
    pinMode(CLOCKENABLEPIN, OUTPUT);
  #endif
  
  #ifdef DEBUG
    Serial.begin(9600);
    delay(3000);
    Serial.println("Printing debug infomration.");
  #endif

  Keyboard.begin();
}

void loop()
{
  if(millis() > lastTime + PERIOD)
  {
    ReadButtons();
    ReleaseKeys();
    PressKeys();

    lastActive = activeKeys;
    lastTime = millis();
  }
}

#if MODE == 0
  void PressKeys()
  {
    for(int i = 0; i < buttonCount; i++)
    {
      //if(key was not previously pressed && key is currently pressed) 
      if(!(lastActive & (1 << i)) && activeKeys & (1 << i))
      {
        Keyboard.press(KEYS[i].key);
        
        #ifdef DEBUG
          Serial.print("Press Key: ");
          Serial.println(KEYS[i].key);
        #endif
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
        activeKeys |= 1 << i;
      }
      //if(pin is high -> key not pressed) set bit low
      //do not change other high bits
      else
      {
        activeKeys &= ~(1 << i);
      }
    }
    
    #ifdef DEBUG
      long lowKeys = activeKeys;
      long highKeys = activeKeys >> 32;
      
      Serial.print("Active Keys: ");
      for(int i = 31; i >= 0; i--)
      {
        Serial.print(bitRead(highKeys, i));
      }
      for(int i = 31; i >= 0; i--)
      {
        Serial.print(bitRead(lowKeys, i));
      }
      Serial.println();
    #endif
  }

  void ReleaseKeys()
  {
    for(int i = 0; i < buttonCount; i++)
    {
      //if(key was previously pressed && key is not currently pressed)
      if((lastActive & (1 << i)) && !(activeKeys & (1 << i)))
      {
        Keyboard.release(KEYS[i].key);
        
        #ifdef DEBUG
          Serial.print("Release Key: ");
          Serial.println(KEYS[i].key);
        #endif
      }
    }
  }
  
#elif MODE == 1
  void PressKeys()
  {
    for(int i = 0; i < hardwareButtonCount; i++)
    {
      //if(key was not previously pressed && key is currently pressed) 
      if(!(lastActive & (1 << i)) && activeKeys & (1 << i))
      {
        Keyboard.press(HARDWAREKEYS[i]);
        
        #ifdef DEBUG
          Serial.print("Press Key: ");
          Serial.println(HARDWAREKEYS[i]);
        #endif
      }
    }
  }
  
  void ReadButtons()
  {
    byte numberRegisters = hardwareButtonCount / 8 + 1;
    activeKeys = 0;
    
    for(int i = 0; i < numberRegisters; i++)
    {
      activeKeys << i * 8;
      activeKeys |= ReadByte();
    }
    
    #ifdef DEBUG
      long lowKeys = activeKeys;
      long highKeys = activeKeys >> 32;
      
      Serial.print("Active Keys: ");
      for(int i = 31; i >= 0; i--)
      {
        Serial.print(bitRead(highKeys, i));
      }
      for(int i = 31; i >= 0; i--)
      {
        Serial.print(bitRead(lowKeys, i));
      }
      Serial.println();
    #endif
  }
  
  byte ReadByte()
  {
    //Load button presses into the shift register.
    digitalWrite(LOADPIN, LOW);
    delayMicroseconds(5);
    digitalWrite(LOADPIN, HIGH);
    delayMicroseconds(5);
    
    //Read data from 165 shift register.
    digitalWrite(CLOCKPIN, HIGH);
    digitalWrite(CLOCKENABLEPIN, LOW);
    byte incoming = shiftIn(DATAPIN, CLOCKPIN, MSBFIRST);
    digitalWrite(CLOCKENABLEPIN, HIGH);
    
    #ifdef DEBUG
      Serial.print("Incoming Byte: ");
      for(int i = 7; i >= 0; i--)
      {
        Serial.print(bitRead(incoming, i));
      }
      Serial.println();
    #endif
    
    return incoming;
  }
  
  void ReleaseKeys()
  {
    for(int i = 0; i < hardwareButtonCount; i++)
    {
      //if(key was previously pressed && key is not currently pressed)
      if((lastActive & (1 << i)) && !(activeKeys & (1 << i)))
      {
        Keyboard.release(HARDWAREKEYS[i]);
        
        #ifdef DEBUG
          Serial.print("Release Key: ");
          Serial.println(HARDWAREKEYS[i]);
        #endif
      }
    }
  }
#else
  #error "Invalid mode entered."
#endif