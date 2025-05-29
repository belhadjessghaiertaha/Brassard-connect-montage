#include <stdio.h>
#include "wokwi-api.h"

#define MAX30102_I2C_ADDRESS 0x57

uint8_t memory[256] = {0};

void chip_init() {
  // Initialize with dummy data
  memory[0x00] = 0x15; // Example data
}

int i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len) {
  if (addr == MAX30102_I2C_ADDRESS) {
    for (int i = 0; i < len; i++) {
      data[i] = memory[reg + i];
    }
    return len;
  }
  return 0;
}

int i2c_write(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len) {
  if (addr == MAX30102_I2C_ADDRESS) {
    for (int i = 0; i < len; i++) {
      memory[reg + i] = data[i];
    }
    return len;
  }
  return 0;
}
