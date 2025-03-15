#include <stdio.h>
#include <metal/gpio.h>
#include <metal/cpu.h>

#define NUM_LEDS 8 // Number of LEDs in the array
int LED_PINS[NUM_LEDS] = {18, 19, 20, 21, 22, 23, 0, 1};  // GPIO pins where LEDs are connected

struct metal_gpio *gpio;
struct metal_cpu *cpu;

// Simple delay function
void delay(int count) {
    for (volatile int i = 0; i < count; i++) {
        for (volatile int j = 0; j < 1000; j++) {
            __asm__("nop");  // Prevent compiler optimization
        }
    }
}

// Initialize all LEDs as output
void init_leds() {
    cpu = metal_cpu_get(0);
    if (!cpu) {
        printf("Failed to get CPU!\n");
        return;
    }

    gpio = metal_gpio_get_device(0);
    if (!gpio) {
        printf("Failed to get GPIO device!\n");
        return;
    }

    // Enable output mode for all LED pins
    for (int i = 0; i < NUM_LEDS; i++) {
        metal_gpio_enable_output(gpio, LED_PINS[i]);
    }
}

int main() {
    init_leds();  // Initialize LED GPIOs

    while (1) {
        // Turn on each LED one by one
        for (int i = 0; i < NUM_LEDS; i++) {
            metal_gpio_set_pin(gpio, LED_PINS[i], 1);  // Turn ON LED
            delay(100);  // Wait 100ms
            metal_gpio_set_pin(gpio, LED_PINS[i], 0);  // Turn OFF LED
        }

        // Blink all LEDs at once
        for (int i = 0; i < NUM_LEDS; i++) {
            metal_gpio_set_pin(gpio, LED_PINS[i], 1);  // Turn ON all LEDs
        }
        delay(500);  // Keep all ON for 500ms

        for (int i = 0; i < NUM_LEDS; i++) {
            metal_gpio_set_pin(gpio, LED_PINS[i], 0);  // Turn OFF all LEDs
        }
        delay(500);  // Keep all OFF for 500ms
    }

    return 0;
}
