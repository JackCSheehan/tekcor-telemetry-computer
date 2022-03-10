#ifndef SD_CARD_MANAGER_H
#define SD_CARD_MANAGER_H

#define SD_PIN 12

#include <string.h>
#include <SPI.h>
#include <SD.h>

// Class to manage SD card
class SDCardManager {
  File telem; // Telemtry file

public:
  SDCardManager(){}
  ~SDCardManager();

  bool init();
  void write(int, double, double, double, double, double, double, double);
  
};

#endif
