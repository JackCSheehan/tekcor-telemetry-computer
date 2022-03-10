#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
    static const int BAUD = 9600;

    // Pins for error LEDs
    static const int SD_ERROR_PIN = 0;
    static const int GPS_ERROR_PIN = 0;
    static const int BMP_ERROR_PIN = 0;

    // Serial pins
    static const int TXD_PIN = 6;
    static const int RXD_PIN = 5;

    // Values indicating errors in GPS reading
    static const int POS_ERR = 361;
    static const int TIME_ERR = -1;
};

#endif