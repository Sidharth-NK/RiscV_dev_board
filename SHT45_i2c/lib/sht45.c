#include "sht45.h"

int sht45_read_sensor(int *temperature, int *humidity) {
    uint8_t command = 0xFD;  // High precision measurement
    uint8_t buffer[6] = {0};

    if (metal_i2c_write(i2c, SHT45_SLAVE_ADDR, 1, &command, METAL_I2C_STOP_ENABLE) != 0) {
        printf("Failed to send measurement command!\n");
        return -1;
    }

    delay_us_hifive(100000); // Wait for measurement (~10ms)

    if (metal_i2c_read(i2c, SHT45_SLAVE_ADDR, 6, buffer, METAL_I2C_STOP_ENABLE) != 0) {
        printf("Failed to read data from SHT45!\n");
        return -1;
    }

    uint16_t raw_temp = (buffer[0] << 8) | buffer[1];
    uint16_t raw_hum = (buffer[3] << 8) | buffer[4];

    *temperature = (int)(-45 + (175 * ((float)raw_temp / 65535.0)));
    *humidity = (int)(100 * ((float)raw_hum / 65535.0));

    return 0;
}
