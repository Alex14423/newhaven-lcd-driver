# newhaven-lcd-driver
This code includes functions programmed in MPLABX IDE for the [PIC32MZ2048EFH100](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MZ-Embedded-Connectivity-with-Floating-Point-Unit-Family-Data-Sheet-DS60001320H.pdf) microcontroller to write formatted strings and control the cursor on the Newhaven LCD [NHD-C0216CiZ-FSW-FBW-3V3](https://newhavendisplay.com/content/specs/NHD-C0216CiZ-FSW-FBW-3V3.pdf) with built in ST7032i chip.

## Schematic

Schematic shows the necessary hardware added to the LCD. (Items not shown are 3.3V supply and PIC32MZ microcontroller.)

![LCDSchematic](https://github.com/user-attachments/assets/447474af-e240-4e84-a071-022271d4fa35)

### Pinout

The pins on the microcontroller for LCD_SCK and LCD_SDA must be Open Drain configurable, since this is an I2C interface.

Q1 was used to turn on the LCD backlight using a GPIO pin.

The value for R4 was chosen to set backlight LED current to the nominal 20mA.

## The Code

The main.c demonstrates the LCD Driver functions. It is programmed to create a countdown counter. It demonstrates the lcdGoTo() function by repeatedly going to a spot on screen, and overwriting the number of seconds to "launch."
