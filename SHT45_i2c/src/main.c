#include "sht45.h"

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    cpu = metal_cpu_get(0);

    i2c = metal_i2c_get_device(0);
    if (!i2c) {
        printf("Failed to get I2C device\n");
        return 1;
    }

    uart = metal_uart_get_device(0);
    if (!uart) {
        printf("Failed to initialize UART\n");
        return 1;
    }

    metal_i2c_init(i2c, 100000, METAL_I2C_MASTER);

    printf("Starting SHT45 sensor read...\n");

    int temperature, humidity;
    if (sht45_read_sensor(&temperature, &humidity) == 0) {
        printf("Temperature: %d C\n", temperature);
        printf("Humidity: %d %%\n", humidity);
    } else {
        printf("Sensor read failed!\n");
    }

    return 0;
}
