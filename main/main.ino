#include <Adafruit_BMP085.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int BAUD = 9600;
static const char SD_PIN = 12;
static const char DELIM = ',';

// Serial pins
static const char TXD_PIN = 6;
static const char RXD_PIN = 5;

// Values indicating errors in GPS reading
static const int POS_ERR = 361;
static const char TIME_ERR = -1;

// Hardware library objects
Adafruit_BMP085 bmp;
TinyGPSPlus gps;
SoftwareSerial ss(RXD_PIN, TXD_PIN);

// Telemtry output file
File telem;

// Struct to hold pressure and temp data
struct BMPData {
    float pres;
    float temp;
};

// Struct to contain position data received from GPS at a particular time
struct GPSData {
    // Position
    double lat;
    double lon;
    double alt;

    // Time
    char hour;
    char min;
    char sec;
    char cent;

    // Velocity
    double vel;
};

// Reads data from the BMP and returns it as a BMPData struct
BMPData readBMPData() {
    BMPData presTemp = {
        bmp.readPressure(),
        bmp.readTemperature()
    };
    return presTemp;
}

// Writes data from GPSData and BMPData structs to the telemtry file
void writeData(BMPData bmpData, GPSData gpsData) {
    telem.print("0,");
    telem.print(bmpData.temp); telem.print(DELIM);
    telem.print(gpsData.alt); telem.print(DELIM);
    telem.print(bmpData.pres); telem.print(DELIM);
    telem.print(gpsData.vel); telem.print(DELIM);
    telem.print(gpsData.lat); telem.print(DELIM);
    telem.print(gpsData.lat); telem.print(DELIM);
}

// Reads data from GPS and returns as GPSData struct
GPSData readGPSData() {
    // Initialize to error values initially
    GPSData pos = {POS_ERR, POS_ERR, TIME_ERR, TIME_ERR, TIME_ERR, TIME_ERR, TIME_ERR};

    // Read if available
    if (ss.available() > 0) {
        if (gps.encode(ss.read())) {
            // Read location
            if (gps.location.isValid()) {
                pos.lat = gps.location.lat();
                pos.lon = gps.location.lng();
            }

            // Read altitude
            if (gps.altitude.isValid()) {
                pos.alt = gps.altitude.meters();
            }

            // Read velocity
            if (gps.speed.isValid()) {
                pos.vel = gps.speed.mps();
            }

            // Read time
            if (gps.time.isValid()) {
                pos.hour = gps.time.hour();
                pos.min = gps.time.minute();
                pos.sec = gps.time.second();
                pos.cent = gps.time.centisecond();
            }
        }
    }

    return pos;
}

// Prints values in given BMPData and GPSData structs
void debug(GPSData gpsData, BMPData bmpData) {
    Serial.print("LAT:");
    Serial.println(gpsData.lat);

    Serial.print("LON:");
    Serial.println(gpsData.lon);

    Serial.print("ALT:");
    Serial.println(gpsData.alt);

    Serial.print("PRES:");
    Serial.println(bmpData.pres);

    Serial.print("TEMP:");
    Serial.println(bmpData.temp);
}

void setup() {
    Serial.begin(115200);
    ss.begin(9600);

    // Initialize all external devices
    if (!SD.begin(SD_PIN)) {
        Serial.println('S');
        while(1);
    }

    // Wait for GPS to initialize
    delay(5000);

    // If GPS hasn't processed enough data after 5 seconds, trigger an error
    if (gps.charsProcessed() < 10) {
        Serial.println('G');
        while(1);
    }

    if (!bmp.begin()) {
        Serial.println('B');
        while(1);
    }

    // Create telemtry file and write CSV header
    telem = SD.open("t.csv", FILE_WRITE);

    if (telem) {
        // Time, temperature, altitude, pressure, velocity, latitude, longitude
        telem.println("t,tm,a,p,v,la,lo");
    } else {
        Serial.println('F');
        while(1);
    }
}

void loop() {
    BMPData bmpData = readBMPData();
    GPSData gpsData = readGPSData();
    debug(gpsData, bmpData);
    writeData(bmpData, gpsData);
}
