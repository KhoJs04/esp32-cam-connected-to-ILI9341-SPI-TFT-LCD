#include <esp_camera.h>
#include <Arduino_GFX_Library.h>
#include <TJpg_Decoder.h>

// Pin Definitions
const byte TFT_SCK = 14;
const byte TFT_MOSI = 13;
const byte TFT_MISO = 12;
const byte TFT_CS = 15;
const byte TFT_DC = 2;

// Create TFT object
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 tft = Arduino_ILI9341(&bus);

void setup() {
    Serial.begin(115200);

    // Initialize the camera
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = 5;
    config.pin_d1 = 18;
    config.pin_d2 = 19;
    config.pin_d3 = 21;
    config.pin_d4 = 36;
    config.pin_d5 = 39;
    config.pin_d6 = 34;
    config.pin_d7 = 35;
    config.pin_xclk = 0;
    config.pin_pclk = 22;
    config.pin_vsync = 25;
    config.pin_href = 23;
    config.pin_sccb_sda = 26;
    config.pin_sccb_scl = 27;
    config.pin_pwdn = 32;
    config.pin_reset = -1;
    config.pin_xclk = 0;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // Select frame size
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 10;
    config.fb_count = 1;

    // Initialize camera
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
    Serial.println("Camera initialized successfully.");

    // Initialize the TFT
    tft.begin();
    tft.setRotation(3); // Set the rotation according to your requirement

    // Initialize JPEG decoder
    TJpgDec.setJpgScale(1); // Set scale (1:1)
    TJpgDec.setCallback(send_to_tft); // Set callback function for drawing
}

void loop() {
    take_picture();
    delay(50); // Delay between captures (adjust as needed)
}

void take_picture() {
    Serial.println("Taking a picture...");
    camera_fb_t * fb = esp_camera_fb_get(); // Get a frame buffer

    if (!fb) {
        Serial.println("Failed to capture image!");
        return;
    }

    uint16_t width = 0, height = 0;
    // Determine the size of the JPEG image
    TJpgDec.getJpgSize(&width, &height, fb->buf, fb->len);
    Serial.print("Width = ");
    Serial.print(width);
    Serial.print(", Height = ");
    Serial.println(height);

    // Decode and draw the image
    TJpgDec.drawJpg(0, 0, fb->buf, fb->len);

    // Return the frame buffer
    esp_camera_fb_return(fb);
}

bool send_to_tft(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t* bitmap) {
    if (y >= tft.height()) return false; // Check if the y-coordinate is within bounds

    // Draw the image on the TFT
    tft.draw16bitRGBBitmap(x, y, bitmap, width, height);
    return true;
}