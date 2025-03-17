#ifndef DS3231_RTC_H
#define DS3231_RTC_H

#include <stdio.h>
#include <stdint.h>
#include <metal/cpu.h>
#include <metal/i2c.h>
#include <metal/uart.h>
#include <metal/interrupt.h>

#define RTC_SLAVE_ADDR  0x68  // DS3231 I2C Address

// DS3231 Register Addresses
#define DS3231_REG_SECONDS   0x00
#define DS3231_REG_MINUTES   0x01
#define DS3231_REG_HOURS     0x02
#define DS3231_REG_DAY       0x03
#define DS3231_REG_DATE      0x04
#define DS3231_REG_MONTH     0x05
#define DS3231_REG_YEAR      0x06

// Function Prototypes
void ds3231_set_time();
void ds3231_get_date();
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);
void delay_us_hifive(uint32_t us);

#endif
