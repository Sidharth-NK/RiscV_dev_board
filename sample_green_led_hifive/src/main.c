// this is a working code of blinking the built-in green led of the hifive rev 1 b board
// you can change the color of the led by just changing the GPIO pin number in the code
// 19 - green
// 21- blue
// 22 - red

#include <stdio.h>        
#include <time.h>          // For time-related functions like time() and delay
#include <metal/gpio.h>    // For SiFive Metal GPIO control functions
#include <metal/uart.h>

#define UART_BAUDRATE 115200

struct metal_uart *uart;  // Global UART handle

// Override _write() to redirect printf() output to UART
int _write(int fd, const char *buf, int count) {
    for (int i = 0; i < count; i++) {
        metal_uart_putc(uart, buf[i]);  // Use global uart
    }
    return count;
}

// This is busy wait delay technique which uses the time library. 
void delayForSeconds(unsigned seconds) {
    time_t timeout = time(NULL) + seconds;  // Set timeout to current time + delay
    while (timeout > time(NULL));  // Busy-wait loop
}

int main(void) {
   
    // Initialize UART (MUST be done before printf)
    uart = metal_uart_get_device(0);  
    if (!uart) {
        return -1;  // Failed to get UART device
    }
    metal_uart_init(uart, UART_BAUDRATE);

    // Obtain a handle to the GPIO controller
    struct metal_gpio* gpio_device = metal_gpio_get_device(0);
    
    if (!gpio_device) {
        printf("Unable to obtain GPIO device\n");
        return -1;  // Return error code
    }

    printf("LED is Blinking successfully\n");  // Now printf will work!
    fflush(stdout);                            // fflush will force the printf to go to uart, sometime it might be stuck hence this method helps
    

    // Infinite loop to toggle the LED
    while (1) {

        // Enable GPIO pin 19 (Green LED) as output and turn it ON
        metal_gpio_enable_output(gpio_device, 21);  
        delayForSeconds(1);  // Delay for 1 second
        
        // Disable GPIO pin 19 (Green LED) output and turn it OFF
        metal_gpio_disable_output(gpio_device, 21);  
        delayForSeconds(1);  // Delay for 1 second
    }

    return 0;  
}
