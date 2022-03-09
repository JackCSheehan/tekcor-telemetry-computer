#include "SDCardManager.h"

SDCardManager sdCardManager;
int time = 0;

void setup() {
    Serial.begin(9600);
    sdCardManager.init();
}

void loop() {
    sdCardManager.write(0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}
