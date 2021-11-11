#include "display.h"

// this task = t_display
namespace Display
{

    void testdrawchar(void)
    {
        display.clearDisplay();

        display.setTextSize(1);              // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text
        display.setCursor(0, 0);             // Start at top-left corner
        display.cp437(true);                 // Use full 256 char 'Code Page 437' font

        // Not all the characters will fit on the display. This is normal.
        // Library will draw what it can and the rest will be clipped.
        for (int16_t i = 0; i < 256; i++)
        {
            if (i == '\n')
                display.write(' ');
            else
                display.write(i);
        }

        display.display();
        delay(2000);
    }

    void testdrawstyles(void)
    {
        display.clearDisplay();

        display.setTextSize(1);              // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text
        display.setCursor(0, 0);             // Start at top-left corner
        display.println(F("Hello, world!"));

        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
        display.println(3.141592);

        display.setTextSize(2); // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.print(F("0x"));
        display.println(0xDEADBEEF, HEX);

        display.display();
        delay(2000);
    }

    void test_display()
    {

        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
        {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ; // Don't proceed, loop forever
        }

        // Show initial display buffer contents on the screen --
        // the library initializes this with an Adafruit splash screen.
        display.display();
        delay(500); // Pause for 2 seconds

        testdrawchar(); // Draw characters of the default font

        testdrawstyles(); // Draw 'stylized' characters
    }
};
