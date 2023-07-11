# Gauge.S SD card updater

For ESP32 Gauge.S automotive dev board.

Easy sketch to start developing from + gives us easy SD card updater so we can always go back to our main FW.


# How to flash?

Download Visual Studio Code and install extension Platform.IO

![Gauge.S PCB](https://github.com/handmade0octopus/Gauge.S-sd-updater/blob/master/pics/board.jpg?=raw=true)

0. Connect device to source of power. Remember to never plug or unplug screen while board is powered. 
1. Connect [FTDI programmer header](https://www.ebay.co.uk/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR12.TRC2.A0.H0.X540i.TRS0&_nkw=ftdi+programmer&_sacat=0) to the board **(1)**.  **REMEMBER TO BEND OUT VOLTAGE PIN AND NEVER LET IT TOUCH THE BOARD!**
2. Use Monitor function in VSC Platformio (Arrow on the bottom), you may need to edit COM port number in `platformio.ini` file.
3. Bridge **(2)** pins together.
4. Press and hold both **(3)** and **(4)**.
5. Release **(3)** and then slowly **(2)** and **(4)**.
6. You should one of messages below, if its the wrong one, repeat from point *3*.

WRONG!
```
rst:0x1 (POWERON_RESET),boot:0xf (UART_BOOT(UART0))
```

Need to say:

```
rst:0x1 (POWERON_RESET),boot:0x7 (DOWNLOAD_BOOT(UART0/UART1/SDIO_REI_REO_V2))
waiting for download
```

7. Close monitor and click *Upload & Monitor* button After flashing reset device using RST button. Device should now start showing messages on Serial screen.