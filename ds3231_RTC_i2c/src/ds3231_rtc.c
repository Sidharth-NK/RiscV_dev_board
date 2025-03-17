#include "ds3231_rtc.h"

extern struct metal_i2c *i2c;

// Convert BCD to Decimal
uint8_t bcd_to_decimal(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// Convert Decimal to BCD
uint8_t decimal_to_bcd(uint8_t decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}

// Delay function for HiFive1 Rev B
void delay_us_hifive(uint32_t us) {
    uint64_t start = metal_cpu_get_mtime(metal_cpu_get(0));
    uint64_t end = start + (us * 32768 / 1000000);  // Convert us to clock cycles (HiFive1: 32.768 kHz)
    while (metal_cpu_get_mtime(metal_cpu_get(0)) < end);
}
