// Headers
#include "sketch.hpp"
#include "sketch_only_statics.hpp"

// Libraries
#include <FastLED.h>

using namespace NSFastLED; 
 
#define DATA_PIN  PIN_SPI_MOSI // PA7
#define CLK_PIN   PIN_SPI_SCK // PA5

int32_t led_type = 0;


//#############################################################################
// Definitions
//-----------------------------------------------------------------------------
NSFastLED::CRGB leds[NUMBER_OF_LEDS_TOTAL];

CLEDController *ledController[36];

static void worker_thread(void* arg) {

    while(true) {

        // For every bank...
        for(int j = 0; j < NUMBER_OF_LED_BANKS; j++) {

            // For every byte in a bank...
            for(int i = 0; i < NUMBER_OF_BYTES_PER_LED_BANK; i += 3) {

                // Index of LED array we're interested in
                uint16_t led_index = (i / 3) + j * NUMBER_OF_LEDS_PER_BANK;

                // Turn the LED on, then pause
                leds[led_index] 
                    = NSFastLED::CRGB( 
                        *(communicable.led_banks[j] + i + 0), 
                        *(communicable.led_banks[j] + i + 1), 
                        *(communicable.led_banks[j] + i + 2)
                    ); 
            }
        }

        // Depending on the type of LED chosen, switch what is used here
        ledController[communicable.led_type]->showLeds();
        
        // Pass off this task
        os_delay(1);
    }
}

void setup() {

    // Init communication
    early_setup();

    // Init controllers
    ledController[0] = &FastLED.addLeds<LPD6803, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[1] = &FastLED.addLeds<LPD8806, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[2] = &FastLED.addLeds<WS2801, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[3] = &FastLED.addLeds<WS2803, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[4] = &FastLED.addLeds<SM16716, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[5] = &FastLED.addLeds<P9813, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[6] = &FastLED.addLeds<APA102, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[7] = &FastLED.addLeds<SK9822, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[8] = &FastLED.addLeds<DOTSTAR, DATA_PIN, CLK_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[9] = &FastLED.addLeds<SM16703, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);

    // 10
    ledController[10] = &FastLED.addLeds<TM1829, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[11] = &FastLED.addLeds<TM1812, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[12] = &FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[13] = &FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[14] = &FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[15] = &FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[16] = &FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[17] = &FastLED.addLeds<UCS1904, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[18] = &FastLED.addLeds<UCS2903, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[19] = &FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);

    // 20
    ledController[20] = &FastLED.addLeds<WS2852, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[21] = &FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[22] = &FastLED.addLeds<GS1903, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[23] = &FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[24] = &FastLED.addLeds<APA106, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[25] = &FastLED.addLeds<PL9823, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[26] = &FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[27] = &FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[28] = &FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[29] = &FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    
    // 30
    ledController[30] = &FastLED.addLeds<GE8822, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[31] = &FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[32] = &FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[33] = &FastLED.addLeds<LPD1886, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);
    ledController[34] = &FastLED.addLeds<LPD1886_8BIT, DATA_PIN, RGB>(leds, NUMBER_OF_LEDS_TOTAL);

    // Launch program!
    create_threads(worker_thread, 3, 3);
};

void loop(){
    // Unused
};
