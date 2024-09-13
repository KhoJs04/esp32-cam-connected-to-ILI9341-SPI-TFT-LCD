# ESP32-CAM with ILI9341 TFT LCD

This guide demonstrates how to connect the **ESP32-CAM** to an **ILI9341 TFT LCD** display module. The ILI9341 is a 2.8-inch TFT LCD that can be used to display a variety of information including text, images, and graphical content in real-time.

### Components:
- ESP32-CAM
- ILI9341 TFT LCD (2.8-inch)

### Wiring Diagram:
Below is the pinout connection between the ESP32-CAM and ILI9341 TFT LCD.

| ILI9341 Pin | ESP32-CAM Pin  |
|-------------|----------------|
| VCC         | 3.3V           |
| GND         | GND            |
| CS          | GPIO15         |
| RESET       | 3.3V           |
| DC          | GPIO2          |
| SDI (MOSI)  | GPIO13         |
| SCK         | GPIO14         |
| LED         | 3.3V           |
| SDO (MISO)  | GPIO12         |

### Image:
## Pinout for ESP32-CAM

![ESP32-CAM Pinout](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2020/03/ESP32-CAM-pinout-new.png?w=1000&quality=100&strip=all&ssl=1)

## Pinout for ILI9341 TFT LCD

![ILI9341 TFT LCD Pinout](https://mytectutor.com/wp-content/uploads/2019/11/backside-components-768x396.png)
