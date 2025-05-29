#include <stdio.h>
#include <string.h>
#include "wokwi-api.h"

typedef struct {
  uart_t uart;
} chip_state_t;

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->uart = uart_create(2, 3); // TXD, RXD
  uart_set_read_handler(chip->uart, handle_uart_read, chip);
}

void handle_uart_read(void *user_data, uint8_t data) {
  chip_state_t *chip = (chip_state_t *)user_data;
  static char buffer[64];
  static int index = 0;

  if (data == '\r' || data == '\n') {
    buffer[index] = '\0';
    if (strcmp(buffer, "AT") == 0) {
      uart_write(chip->uart, "OK\r\n", 4);
    } else if (strcmp(buffer, "AT+CSQ") == 0) {
      uart_write(chip->uart, "+CSQ: 20,0\r\nOK\r\n", 17);
    } else {
      uart_write(chip->uart, "ERROR\r\n", 7);
    }
    index = 0;
  } else if (index < sizeof(buffer) - 1) {
    buffer[index++] = data;
  }
}
