#include <stdio.h>
#include <iostream>
#include <string>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


using namespace std;

#define DATA 2

#define FREQ (2400)

uint8_t off[]{0xFF, 0x0A, 0x8A, 0x2A, 0x88, 0xAA, 0x45, 0x55, 0x55, 0x55, 0x15, 0x55, 0x4A, 0xA8, 0xAA, 0xA8, 0xA2,
              0x22, 0x20, 0x40, 0x00};

int main() {
    stdio_init_all();
    gpio_init(DATA);
    gpio_set_dir(DATA, GPIO_OUT);

    absolute_time_t start = get_absolute_time();

    cout << "Going to transmit " << size(off) << " bytes at " << FREQ << "kHz" << endl;
    uint32_t limit = size(off) * 8;

    for (uint32_t tick = 0; tick < limit; tick++) {
        busy_wait_until(delayed_by_us(start, (uint64_t) (tick * 1e6 / FREQ) + 1000));
        gpio_put(DATA, (off[tick / 8] >> (7 - (tick % 8))) & 1);
    }
}
