#ifndef _CONFIG_H
#define _CONFIG_H

#include <RadioLib.h>

// How often to send an uplink - consider legal & FUP constraints - see notes
// const uint32_t uplinkIntervalSeconds = 5UL * 60UL;    // minutes x seconds
const uint32_t uplinkIntervalSeconds = 1UL * 60UL;    // minutes x seconds

// JoinEUI - previous versions of LoRaWAN called this AppEUI
// for development purposes you can use all zeros - see wiki for details
#define RADIOLIB_LORAWAN_JOIN_EUI  0x0000000000000000

// The Device EUI & two keys can be generated on the TTN console 
#ifndef RADIOLIB_LORAWAN_DEV_EUI   // Replace with your Device EUI
#define RADIOLIB_LORAWAN_DEV_EUI   0x70B3D57ED006AF06
#endif
#ifndef RADIOLIB_LORAWAN_APP_KEY   // Replace with your App Key
// But the nwkKey is used in LoRaWAN < 1.1.0. In TTN it is wrongly called the appKey. Thus full the appKey from TTN
#define RADIOLIB_LORAWAN_APP_KEY_MSB   0x9D, 0xAB, 0xD0, 0xC7, 0xE0, 0x82, 0xF2, 0x9A, 0xCD, 0xC7, 0x13, 0x8F, 0x17, 0xF8, 0x47, 0x64
#define RADIOLIB_LORAWAN_APP_KEY_LSB   0x64, 0x47, 0xF8, 0x17, 0x8F, 0x13, 0xC7, 0xCD, 0x9A, 0xF2, 0x82, 0xE0, 0xC7, 0xD0, 0xAB, 0x9D
#endif
#ifndef RADIOLIB_LORAWAN_NWK_KEY   // Put your Nwk Key here
// But the nwkKey is used in LoRaWAN < 1.1.0. In TTN it is wrongly called the appKey. Thus full the appKey from TTN
#define RADIOLIB_LORAWAN_NWK_KEY_MSB   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define RADIOLIB_LORAWAN_NWK_KEY_LSB   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//#define RADIOLIB_LORAWAN_NWK_KEY   0x19, 0x93, 0xB1, 0x66, 0x4B, 0xA3, 0xB5, 0x44, 0xD5, 0x0B, 0x2E, 0x3D, 0xDE, 0x45, 0xD3, 0x61
#endif

// TTN NwkKey msb
// 0xFC, 0xDB, 0x27, 0x58, 0xC3, 0xC6, 0xD5, 0xC3, 0xA6, 0x46, 0x56, 0xB2, 0xC5, 0x8E, 0x6A, 0x46

// TTN AppKey msb
// 0x61, 0xD3, 0x45, 0xDE, 0x3D, 0x2E, 0x0B, 0xD5, 0x44, 0xB5, 0xA3, 0x4B, 0x66, 0xB1, 0x93, 0x19


// For the curious, the #ifndef blocks allow for automated testing &/or you can
// put your EUI & keys in to your platformio.ini - see wiki for more tips



// Regional choices: EU868, US915, AU915, AS923, IN865, KR920, CN780, CN500
const LoRaWANBand_t Region = EU868;
const uint8_t subBand = 0;  // For US915, change this to 2, otherwise leave on 0


// ============================================================================
// Below is to support the sketch - only make changes if the notes say so ...

// Auto select MCU <-> radio connections
// If you get an error message when compiling, it may be that the 
// pinmap could not be determined - see the notes for more info

// Adafruit
#if defined(ARDUINO_SAMD_FEATHER_M0)
    #pragma message ("Adafruit Feather M0 with RFM95")
    #pragma message ("Link required on board")
    SX1276 radio = new Module(8, 3, 4, 6);


// LilyGo 
#elif defined(ARDUINO_TTGO_LORA32_V1)
  #pragma message ("TTGO LoRa32 v1 - no Display")
  SX1276 radio = new Module(18, 26, 14, 33);

#elif defined(ARDUINO_TTGO_LORA32_V2)
   #pragma error ("ARDUINO_TTGO_LORA32_V2 awaiting pin map")

#elif defined(ARDUINO_TTGO_LoRa32_v21new) // T3_V1.6.1
  #pragma message ("Using TTGO LoRa32 v2.1 marked T3_V1.6.1 + Display")
  SX1276 radio = new Module(18, 26, 14, 33);

#elif defined(ARDUINO_TBEAM_USE_RADIO_SX1262)
  #pragma error ("ARDUINO_TBEAM_USE_RADIO_SX1262 awaiting pin map")

#elif defined(ARDUINO_TBEAM_USE_RADIO_SX1276)
  #pragma message ("Using TTGO LoRa32 v2.1 marked T3_V1.6.1 + Display")
  SX1276 radio = new Module(18, 26, 23, 33);


// Heltec
#elif defined(ARDUINO_HELTEC_WIFI_LORA_32)
  #pragma error ("ARDUINO_HELTEC_WIFI_LORA_32 awaiting pin map")

#elif defined(ARDUINO_heltec_wifi_kit_32_V2)
  #pragma message ("ARDUINO_heltec_wifi_kit_32_V2 awaiting pin map")
  SX1276 radio = new Module(18, 26, 14, 35);

#elif defined(ARDUINO_heltec_wifi_kit_32_V3)
  #pragma message ("Using Heltec WiFi LoRa32 v3 - Display + USB-C")
  SX1262 radio = new Module(8, 14, 12, 13);

#elif defined(ARDUINO_CUBECELL_BOARD)
  #pragma message ("Using TTGO LoRa32 v2.1 marked T3_V1.6.1 + Display")
  SX1262 radio = new Module(RADIOLIB_BUILTIN_MODULE);

#elif defined(ARDUINO_CUBECELL_BOARD_V2)
  #pragma error ("ARDUINO_CUBECELL_BOARD_V2 awaiting pin map")

#elif defined(EXTERNAL_SX127x_BOARD_ON_ESP32DEV)
  #pragma message ("Using EXTERNAL_SX127x_BOARD_ON_ESP32DEV")

  // SX1262  pin order: Module(NSS/CS, DIO1, RESET, BUSY);
  // SX1262 radio = new Module(8, 14, 12, 13);

  // SX1278 pin order: Module(NSS/CS, DIO0, RESET, DIO1);
  // SX1278 radio = new Module(10, 2, 9, 3);
  SX1276 radio = new Module(/*NSS/CS*/ 5, /*DIO0*/ 2, /*RESET*/ 14, /*DIO1*/ 4);

#else
  #pragma message ("Unknown board - no automagic pinmap available")

  // SX1262  pin order: Module(NSS/CS, DIO1, RESET, BUSY);
  // SX1262 radio = new Module(8, 14, 12, 13);

  // SX1278 pin order: Module(NSS/CS, DIO0, RESET, DIO1);
  // SX1278 radio = new Module(10, 2, 9, 3);
#endif


// Copy over the EUI's & keys in to the something that will not compile if incorrectly formatted
uint64_t joinEUI =   RADIOLIB_LORAWAN_JOIN_EUI;
uint64_t devEUI  =   RADIOLIB_LORAWAN_DEV_EUI;
uint8_t appKey[] = { RADIOLIB_LORAWAN_APP_KEY_MSB };
uint8_t nwkKey[] = { RADIOLIB_LORAWAN_NWK_KEY_MSB };

// Create the LoRaWAN node
LoRaWANNode node(&radio, &Region, subBand);


// Helper function to display any issues
void debug(bool isFail, const __FlashStringHelper* message, int state, bool Freeze) {
  if (isFail) {
    Serial.print(message);
    Serial.print("(");
    Serial.print(state);
    Serial.println(")");
    while (Freeze);
  }
}

// Helper function to display a byte array
void arrayDump(uint8_t *buffer, uint16_t len) {
  for (uint16_t c = 0; c < len; c++) {
    Serial.printf("%02X", buffer[c]);
  }
  Serial.println();
}


#endif
