#include "BMPManager.h"

// Initializes the BMP. Returns false if there is an error
bool BMPManager::init() {
    return bmp.begin();
}

// Reads pres, temp returns as BMPData struct
BMPData BMPManager::readData() {
    BMPData presTemp = {
        bmp.readPressure(),
        bmp.readTemperature()
    };
    return presTemp;
}