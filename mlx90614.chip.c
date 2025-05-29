#include <stdio.h>
#include "wokwi-api.h"

#define MLX90614_I2C_ADDRESS 0x5A

uint8_t memory[256] = {0};

void chip_init() {
  // Setup some dummy temperature data
  memory[0x07] = 0x70; // low byte
  memory[0x08] = 0x1F; // high byte
}

int i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len) {
  if (addr == MLX90614_I2C_ADDRESS) {
    for (int i = 0; i < len; i++) {
      data[i] = memory[reg + i];
    }
    return len;
  }
  return 0;
}

int i2c_write(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len) {
  if (addr == MLX90614_I2C_ADDRESS) {
    for (int i = 0; i < len; i++) {
      memory[reg + i] = data[i];
    }
    return len;
  }
  return 0;
}
