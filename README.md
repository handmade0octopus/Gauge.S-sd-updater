Initial Readme



WRONG!
```
rst:0x1 (POWERON_RESET),boot:0xf (UART_BOOT(UART0))
```

Need to say:

```
rst:0x1 (POWERON_RESET),boot:0x7 (DOWNLOAD_BOOT(UART0/UART1/SDIO_REI_REO_V2))
waiting for download
```