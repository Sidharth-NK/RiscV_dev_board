#include "ds3231_rtc.h"

void set_rtc_time() {
    uint8_t data[8] = {
        DS3231_REG_SECONDS,
        decimal_to_bcd(INIT_SECONDS),
        decimal_to_bcd(INIT_MINUTES),
        decimal_to_bcd(INIT_HOURS),
        decimal_to_bcd(INIT_DAY),
        decimal_to_bcd(INIT_DATE),
        decimal_to_bcd(INIT_MONTH),
        decimal_to_bcd(INIT_YEAR),
    };

    if (metal_i2c_transfer(i2c, RTC_SLAVE_ADDR, data, 8, NULL, 0) != 0) {
        printf("Failed to set time\r\n");
    } else {
        printf("Time and Date set successfully\r\n");
    }
}

uint8_t bcd_to_decimal(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t decimal_to_bcd(uint8_t decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}

void delay_us_hifive(int us) {
    long int target = metal_cpu_get_timer(cpu) + us * metal_cpu_get_timebase(cpu) / 1000000;
    while (metal_cpu_get_timer(cpu) < target);
}
