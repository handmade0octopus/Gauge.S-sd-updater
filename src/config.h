#ifndef CONFIG_H
#define CONFIG_H

// Edit in platformio.ini
#ifndef	PCB_VER
#define PCB_VER 40                  // versions older than v4.0 (40) use SPI for SD card
#endif

// Sd card handle - PCB v3.8 and below use old style SPI SD card interface
#if PCB_VER < 40
	#include <SD.h>
	#define SD_USE SD

	#define SD_CS           15
	#define SD_CS           15
	#define SD_SCK          14
	#define SD_MISO         27
	#define SD_MOSI         13
	SPIClass SDSPI(HSPI);

#else
	#include <SD_MMC.h>
	#define SD_USE SD_MMC
#endif


// Pin definitions
#if PCB_VER <= 40
 #if PCB_VER == 36
	#define I2C_SCL 		33
	#define I2C_SDA 		22

	#define ENC_B 			25
 #else
	#define I2C_SCL 	    25
	#define I2C_SDA 	    22

	#define ENC_B 		    33
 #endif

	#define ENC_A 		    19
	#define ENC_C 		     0

    #define OLED_MOSI 	    23
    #define OLED_CLK 	    18
    #define OLED_DC		    21
    #define OLED_CS		    32
    #define OLED_RESET 	    26
    #define LED_C		    12

    #define ANALOG_1 	    35
    #define ANALOG_2 	    34
    #define ANALOG_3 	    39
    #define ANALOG_4 	    36
    #define ANALOG_5 	    33

    #define CAN_TX		     5
    #define CAN_RX		     4

    #define SERIAL_KLINE_TX	17
	#define SERIAL_KLINE_RX	16
#else
	#define I2C_SCL 	    42
	#define I2C_SDA 	    41

	#define ENC_A 		    12
	#define ENC_B 		    11
	#define ENC_C 		     0
	#define ENC_E 		     3

	#define USB_DN		    19
	#define USB_DP		    20

	#define SD_SCK 		    39
	#define SD_MISO		    40
	#define SD_MOSI		    38

    #define OLED_MOSI 	    48
	#define OLED_CLK 	    47
	#define OLED_DC		    21
	#define OLED_CS		    14
	#define OLED_RESET 	    13
	#define LED_C		    10

	#define ANALOG_0 	     9 // Input voltage
	#define ANALOG_1 	     4
	#define ANALOG_2 	     5
	#define ANALOG_3 	     6
	#define ANALOG_4 	     7
	#define ANALOG_5 	     1
	#define ANALOG_6 	     2
	#define ANALOG_7 	     8

	#define CAN_TX		    18
	#define CAN_RX		    17

    #define LOG_TX		    37
	#define LOG_RX		    36
#endif  

#endif // CONFIG_H