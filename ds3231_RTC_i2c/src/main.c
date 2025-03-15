#include "ds3231_rtc.h"

struct metal_cpu *cpu;
struct metal_i2c *i2c;
struct metal_uart *uart;

int _write(int fd, const char *buf, int count) {
    if (!uart) return -1;
    for (int i = 0; i < count; i++) {
        metal_uart_putc(uart, buf[i]);
    }
    return count;
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    cpu = metal_cpu_get(0);
    
    i2c = metal_i2c_get_device(0);
    if (!i2c) {
        printf("Failed to get I2C device\r\n");
        return 1;
    }

    uart = metal_uart_get_device(0);
    if (!uart) {
        printf("Failed to initialize UART\r\n");
        return 1;
    }

    metal_i2c_init(i2c, 100000, METAL_I2C_MASTER);

    set_rtc_time();

    while (1) {
        uint8_t tx[1] = {DS3231_REG_SECONDS};
        if (metal_i2c_transfer(i2c, RTC_SLAVE_ADDR, tx, 1, NULL, 0) != 0) {
            printf("I2C write failed!\r\n");
            return 1;
        }

        uint8_t rx[7];  
        if (metal_i2c_transfer(i2c, RTC_SLAVE_ADDR, NULL, 0, rx, 7) != 0) {
            printf("I2C read failed!\r\n");
            return 1;
        }

        uint8_t seconds = bcd_to_decimal(rx[0]);
        uint8_t minutes = bcd_to_decimal(rx[1]);
        uint8_t hours = bcd_to_decimal(rx[2]);
        // uint8_t day = bcd_to_decimal(rx[3]); Not used hence commented out
        uint8_t date = bcd_to_decimal(rx[4]);
        uint8_t raw_month = rx[5];
        uint8_t month = bcd_to_decimal(raw_month & 0x1F);
        uint8_t century = (raw_month >> 7) & 1;
        uint16_t year = 2000 + bcd_to_decimal(rx[6]) + (century * 100);

        printf("%02d:%02d:%02d %02d/%02d/%04d\r\n", hours, minutes, seconds, date, month, year);
        fflush(stdout);

        delay_us_hifive(1000000);
    }

    return 0;
}
