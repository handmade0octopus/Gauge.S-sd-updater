#include <Arduino.h>
#include <Update.h>
#include "config.h"

#if PCB_VER >= 50
HWCDC Serial;
#endif

#define UPDATE_FILE "/update.bin"   // Default file on SD card to update from

// Update function
void updateFirmware() {	
	File updateFile = SD_USE.open(UPDATE_FILE);
	if(!updateFile || updateFile.isDirectory()) {
		return;
	}
	size_t updateSize = updateFile.size();

	Serial.println("Firmware update started. Please wait, may take several minutes!");

	if(Update.begin(updateSize)) {
		if(Update.writeStream(updateFile) == updateSize) {
			if(Update.end() && Update.isFinished()) {
				updateFile.close();
				SD_USE.remove(UPDATE_FILE);
				Serial.println("Update sucessful");
				delay(3000);
				ESP.restart();
			} else {
				Serial.println("Wrong file--");
				SD_USE.remove(UPDATE_FILE);
			}
		}
	}
}


void setup() {
	Serial.begin(115200);

	// Setup SD card
	bool sdReady = false;
	#if PCB_VER >= 40
		 #if PCB_VER >= 50
			SD_USE.setPins(SD_SCK, SD_MISO, SD_MOSI, -1, -1, -1);
			sdReady = SD_USE.begin("/sdcard", true, false, SDMMC_FREQ_HIGHSPEED, 10);
			delay(2000);
		 #else
			sdReady = SD_USE.begin("/sdcard", true, false, SDMMC_FREQ_HIGHSPEED, 5);
		 #endif
	#else
		SDSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
		sdReady = SD_USE.begin(SD_CS, SDSPI, 80000000, "/sd", 7);
	#endif

	// Update firmware if file found
	if(sdReady) updateFirmware();
	else Serial.println("SD ERROR!");

	Serial.println("UPDATE ERROR!");

	delay(20000);
	ESP.restart();
}

void loop() {
	delay(5000);
}

