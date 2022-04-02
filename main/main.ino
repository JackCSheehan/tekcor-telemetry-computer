#include <Adafruit_BMP085.h>
#include <SD.h>

static const float SEA_LEVEL_PRES = 101625.52;
static const char SD_PIN = 10;
static const char DELIM = ',';

// Hardware library objects
Adafruit_BMP085 bmp;

// Telemtry output file
File telem;

// Struct to hold pressure, temp, and altitude data
struct BMPData {
    float pres;
    float temp;
    float alt;
};

// Reads data from the BMP and returns it as a BMPData struct
BMPData readBMPData() {
    BMPData presTemp = {
       bmp.readPressure(),
        bmp.readTemperature(),
        bmp.readAltitude(SEA_LEVEL_PRES),
    };
    return presTemp;
}

// Writes data from BMPData struct to the telemtry file
void writeData(BMPData bmpData) {
    telem.print(millis() / 1000.0, 2); telem.print(DELIM);
    telem.print(bmpData.temp, 2); telem.print(DELIM);
    telem.print(bmpData.alt, 2); telem.print(DELIM);
    telem.print(bmpData.pres, 2); telem.println(DELIM);
    telem.flush();
}

// Prints values in given BMPData and GPSData structs
void debug(BMPData& bmpData) {
    Serial.print("ALT:");
    Serial.println(bmpData.alt);

    Serial.print("PRES:");
    Serial.println(bmpData.pres);

    Serial.print("TEMP:");
    Serial.println(bmpData.temp);
}

void setup() {
    Serial.begin(115200);

    // Initialize all external devices
    if (!SD.begin(SD_PIN)) {
        Serial.println("ERROR: Failed to initialize SD card");
        while(1);
    }

    // If telemtry file already exists, computer was reset after flight. Enter wait loop
    if (SD.exists("t.csv")) {
      Serial.println("Entering reset hold");
      while(1);
    }

    if (!bmp.begin()) {
        Serial.println("ERROR: Failed to initialize BMP");
        while(1);
    }

    // Create telemtry file and write CSV header
    telem = SD.open("t.csv", (O_WRITE | O_CREAT));

    if (telem) {
        // Time, temperature, altitude, pressure
        telem.println("t,c,a,p");
    } else {
        Serial.println("ERROR: Failed to open telemtry file");
        while(1);
    }
}

void loop() {
    BMPData bmpData = readBMPData();
    debug(bmpData);
    writeData(bmpData);
}
