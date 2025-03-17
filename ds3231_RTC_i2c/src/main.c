#include "ds3231_rtc.h"

struct metal_cpu *cpu;
struct metal_i2c *i2c;
struct metal_uart *uart;

// Custom _write() function for printf redirection
int _write(int fd, const char *buf, int count) {
    if (!uart) return -1;
    for (int i = 0; i < count; i++) {
        metal_uart_putc(uart, buf[i]);
    }
    return count;
}

// Function to initialize peripherals
void init_peripherals() {
    // Disable stdout buffering to ensure immediate printf output
    setvbuf(stdout, NULL, _IONBF, 0);

    // Get CPU handle
    cpu = metal_cpu_get(0);

    // Get I2C device
    i2c = metal_i2c_get_device(0);
    if (!i2c) {
        printf("Failed to get I2C device\r\n");
        while (1);
    }

    // Get UART device
    uart = metal_uart_get_device(0);
    if (!uart) {
        printf("Failed to initialize UART\r\n");
        while (1);
    }

    // Initialize I2C at 100 kHz in master mode
    metal_i2c_init(i2c, 100000, METAL_I2C_MASTER);
}

// Function to read RTC time
void ds3231_get_time() {
    uint8_t tx[1] = {DS3231_REG_SECONDS};  // Start from Seconds register
    uint8_t rx[3];  // Buffer for hours, minutes, and seconds

    // Write register pointer
    if (metal_i2c_transfer(i2c, RTC_SLAVE_ADDR, tx, 1, NULL, 0) != 0) {
        printf("I2C write failed!\r\n");
        return;
    }

    // Read Seconds, Minutes, and Hours
    if (metal_i2c_transfer(i2c, RTC_SLAVE_ADDR, NULL, 0, rx, 3) != 0) {
        printf("I2C read failed!\r\n");
        return;
    }

    // Convert BCD to decimal
    uint8_t seconds = bcd_to_decimal(rx[0]);
    uint8_t minutes = bcd_to_decimal(rx[1]);
    uint8_t hours = bcd_to_decimal(rx[2] & 0x3F);  // Mask for 24-hour format

    printf("Time: %02d:%02d:%02d\r\n", hours, minutes, seconds);
}

// Function to read RTC date
void ds3231_get_date() {
    uint8_t tx[1] = {DS3231_REG_DATE};  // Start from Date register
    uint8_t rx[3];  // Buffer for date, month, and year

    // Write register pointer
    if (metal_i2c_transfer(i2c, RTC_SLAVE_ADDR, tx, 1, NULL, 0) != 0) {
        printf("I2C write failed!\r\n");
        return;
    }

    // Read Date, Month, and Year
    if (metal_i2c_transfer(i2c, RTC_SLAVE_ADDR, NULL, 0, rx, 3) != 0) {
        printf("I2C read failed!\r\n");
        return;
    }

    // Convert BCD to decimal
    uint8_t date = bcd_to_decimal(rx[0]);   
    uint8_t raw_month = rx[1];              
    uint8_t month = bcd_to_decimal(raw_month & 0x1F);  // Mask century bit
    uint8_t year_last2 = bcd_to_decimal(rx[2]); 
    
    uint16_t year = 2000 + year_last2;  // Adjust for 2000+

    printf("Date: %02d/%02d/%04d\r\n", date, month, year);
}

int main() {
    init_peripherals();

    // Infinite loop to continuously read RTC time and date
    while (1) {
        ds3231_get_time();
        ds3231_get_date();
    
        delay_us_hifive(1000000);  // Wait 1 second
    }

    return 0;
}
