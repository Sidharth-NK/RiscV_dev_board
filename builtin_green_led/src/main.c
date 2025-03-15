// this is a working code of blinking the built-in green led of the hifive rev 1 b board
// you can change the color of the led by just changing the GPIO pin number in the code
// 19 - green
// 21- blue
// 22 - red

// HiFive1 Rev B - Blink Built-in LED using PlatformIO & Freedom Metal
#include <stdio.h>
#include <time.h>          
#include <metal/gpio.h>    
#include <metal/uart.h>
#include "led_control.h"  // Include header file for LED functions

#define UART_BAUDRATE 115200
#define LED_PIN 19  // Change to 21 (Blue) or 22 (Red) for different colors

struct metal_uart *uart;
struct metal_gpio *gpio_device;

// Redirect printf() output to UART
int _write(int fd, const char *buf, int count) {
    for (int i = 0; i < count; i++) {
        metal_uart_putc(uart, buf[i]);
    }
    return count;
}

// Function to initialize UART & GPIO
void setup() {
    uart = metal_uart_get_device(0);
    if (!uart) {
        printf("Error: UART device not found!\n");
        return;
    }
    metal_uart_init(uart, UART_BAUDRATE);

    gpio_device = metal_gpio_get_device(0);
    if (!gpio_device) {
        printf("Error: GPIO device not found!\n");
        return;
    }
    metal_gpio_enable_output(gpio_device, LED_PIN);
    printf("LED Blinking Started on GPIO %d\n", LED_PIN);
}

// Function to blink LED with delay
void blink_led() {
    metal_gpio_set_pin(gpio_device, LED_PIN, 1); // Turn ON
    delayForSeconds(1);
    metal_gpio_set_pin(gpio_device, LED_PIN, 0); // Turn OFF
    delayForSeconds(1);
}

int main(void) {
    setup();  // Initialize UART and GPIO

    while (1) {
        blink_led();  // Blink LED continuously
    }

    return 0;
}
