/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ps2avrGB.h"

#include <avr/pgmspace.h>

#include "action_layer.h"
#include "i2c.h"
#include "quantum.h"

#define NUM_BACKLIGHT_LEDS 16
#define BACKLIGHT_LEVELS 15

const uint32_t layer_colors[] PROGMEM = {
    [0] = 0xFF0000,
    [1] = 0xFF6600,
    [2] = 0x00FFFF,
};

size_t current_color_idx;
uint8_t current_level;

uint8_t dim(uint8_t color, uint8_t opacity) {
    return ((uint16_t) color * opacity / 0xFF) & 0xFF;
}

void backlight_set_color(uint8_t alpha, uint32_t color) {
    uint8_t r = dim((color >> 16) & 0xFF, alpha);
    uint8_t g = dim((color >> 8) & 0xFF, alpha);
    uint8_t b = dim(color & 0xFF, alpha);

    uint8_t data[3 * NUM_BACKLIGHT_LEDS];
    for (uint8_t i = 0; i < NUM_BACKLIGHT_LEDS; i++) {
        data[3 * i] = g;
        data[3 * i + 1] = r;
        data[3 * i + 2] = b;
    }

    i2c_init();
    i2c_send(0xB0, data, 48);
}

void backlight_set(uint8_t level) {
    current_level = level;
    backlight_set_color(
        current_level * 0x11,
        pgm_read_dword(layer_colors + current_color_idx)
    );
}

void matrix_scan_user(void) {
    current_color_idx = 0;

    for (size_t i = 0; i < sizeof(layer_colors) / sizeof(uint32_t); i++) {
        if (IS_LAYER_ON(i)) {
            current_color_idx = i;
        }
    }

    backlight_set(current_level);
}
