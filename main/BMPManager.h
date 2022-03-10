#ifndef BMP_MANAGER_H
#define BMP_MANAGER_H

#include <Adafruit_BMP085.h>
#include <Wire.h>

// Struct to hold pressure and temp data
struct PresTemp {
    double pres;
    double temp;
};

// Class needed to manage BMP pressure and temperature readings
class BMPManager {
    Adafruit_BMP085 bmp;

public:
    BMPManager(){}
    ~BMPManager(){}

    bool init();
    PresTemp readPresTemp();
};

#endif