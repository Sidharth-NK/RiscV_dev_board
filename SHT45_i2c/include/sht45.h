#ifndef SHT45_H
#define SHT45_H

#include <metal/i2c.h>
#include <metal/uart.h>
#include <metal/cpu.h>
#include <stdio.h>
#include <stdint.h>

#define SHT45_SLAVE_ADDR 0x44

extern struct metal_cpu *cpu;
extern struct metal_uart *uart;
extern struct metal_i2c *i2c;

int sht45_read_sensor(int *temperature, int *humidity);

#endif // SHT45_H
