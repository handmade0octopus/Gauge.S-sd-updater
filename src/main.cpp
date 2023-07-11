#include <Arduino.h>
#include <Update.h>

#define PCB_VER 40                  // versions older than v4.0 (40) use SPI for SD card
#define UPDATE_FILE "/update.bin"   // Default file on SD card to update from

#if PCB_VER < 40
	#include <SD.h>
	#define SD_USE SD

	#define SD_CS 15
	#define SD_CS 15
	#define SD_SCK 14
	#define SD_MISO 27
	#define SD_MOSI 13
	SPIClass SDSPI(HSPI);

#elif PCB_VER >= 40
	#include <SD_MMC.h>
	#define SD_USE SD_MMC

	#define ENC_D			27
	#define ENC_E			13

#endif

// Update function
void updateFirmware() {	
	File updateFile = SD_USE.open(UPDATE_FILE);
	if (updateFile == NULL || updateFile.isDirectory()) {
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
		sdReady = SD_USE.begin("/sdcard", true);
	#else
		SDSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
		sdReady = SD_USE.begin(SD_CS, SDSPI, 80000000, "/sd", 7);
	#endif

  // Update firmware if file found
  if(sdReady) updateFirmware();
  else Serial.println("SD ERROR!");

  Serial.println("UPDATE ERROR!");

  delay(5000);
  ESP.restart();
}

void loop() {
}

