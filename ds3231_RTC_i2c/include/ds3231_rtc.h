#ifndef DS3231_RTC_H
#define DS3231_RTC_H

#include <metal/i2c.h>
#include <metal/cpu.h>
#include <metal/uart.h>
#include <stdio.h>

// DS3231 I2C address
#define RTC_SLAVE_ADDR 0x68

// DS3231 registers
#define DS3231_REG_SECONDS   0x00
#define DS3231_REG_MINUTES   0x01
#define DS3231_REG_HOURS     0x02
#define DS3231_REG_DAY       0x03
#define DS3231_REG_DATE      0x04
#define DS3231_REG_MONTH     0x05
#define DS3231_REG_YEAR      0x06

// RTC Time and Date to Set (6th March 2025, 17:19:00)
#define INIT_SECONDS   0x00
#define INIT_MINUTES   0x19
#define INIT_HOURS     0x17  // 24-hour format
#define INIT_DAY       0x04  // Thursday (1 = Sunday, 7 = Saturday)
#define INIT_DATE      0x06
#define INIT_MONTH     0x03  // March
#define INIT_YEAR      0x25  // 2025 (last two digits)

extern struct metal_cpu *cpu;
extern struct metal_i2c *i2c;
extern struct metal_uart *uart;

void set_rtc_time();
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);
void delay_us_hifive(int us);

#endif // DS3231_RTC_H
