/* There was a issue with the execution of printf function, 
earlier it was not working because the prinf function was redirected 
automatically to stdout, hence it wont be printed in serial monitor.
So to make it print on the serial monitor we use _write function to 
redirect printf to uart*/

// this is a working code of uart comunication setup

#include <stdio.h>
#include <metal/uart.h>
#define UART_BAUDRATE 115200

struct metal_uart *uart;  // Declare globally so _write() can access it

// Override _write() to redirect printf() output to UART
int _write(int fd, const char *buf, int count) {
    for (int i = 0; i < count; i++) {
        metal_uart_putc(uart, buf[i]);
    }
    return count;
}
int main() {
    uart = metal_uart_get_device(0);  // Get UART0 (FE310 UART)
    if (!uart) {
        return -1;  // Failed to get UART device
    }
    metal_uart_init(uart, UART_BAUDRATE);  // Initialize UART
    printf("Printf function works!\n");  //  print via UART
    while (1) {
        printf("Looping message...\n");  
        metal_uart_putc(uart, 'H');
        metal_uart_putc(uart, 'e');
        metal_uart_putc(uart, 'l');
        metal_uart_putc(uart, 'l');
        metal_uart_putc(uart, 'o');
        metal_uart_putc(uart, '\n');
        for (volatile int i = 0; i < 1000000; i++);  // Delay
    }
    return 0;
}
