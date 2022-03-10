#ifndef SD_CARD_MANAGER_H
#define SD_CARD_MANAGER_H

#include <string.h>
#include <SPI.h>
#include <SD.h>
#include "constants.h"
#include "GPSManager.h"
#include "BMPManager.h"

// Class to manage SD card
class SDCardManager {
  File telem; // Telemtry file

public:
  SDCardManager(){}
  ~SDCardManager();

  bool init();
  void write(GPSData, BMPData);
  
};

#endif
