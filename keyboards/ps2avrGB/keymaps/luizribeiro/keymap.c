#include "ps2avrGB.h"
#include "rgblight.h"
#include "action_layer.h"
#include "quantum.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KC_KEYMAP( \
        ESC, FN3, FN4, FN5, FN6, NO,  NO,  MPRV,MPLY,MNXT,MUTE,VOLD,VOLU,FN7, HOME,END, \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     DEL, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     FN1, \
        FN2, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,           PGUP,\
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,          UP,  PGDN,\
        FN0, LALT,LGUI,          SPC,                     RGUI,RALT,RCTL,LEFT,DOWN,RGHT \
    ),
    KC_KEYMAP( \
        NO,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  NO,  NO,  \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  MPRV,MPLY,MNXT,MUTE,VOLD,VOLU,DEL,      NO,  \
        NO,  NO,  NO,  NO,  NO,  NO,  NO,  PGUP,NO,  NO,  NO,  NO,  NO,  NO,       TRNS,\
        FN1, NO,  NO,  PGDN,NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  NO,            NO,  \
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  TRNS,          NO,  NO,  \
        TRNS,TRNS,TRNS,          NO,                      TRNS,TRNS,TRNS,NO,  NO,  NO   \
    ),
    KC_KEYMAP( \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
        NO,  NO,  NO,  NO,  END, NO,  NO,  NO,  NO,  NO,  HOME,NO,  NO,  NO,       NO,  \
        NO,  BTN1,MS_U,BTN2,NO,  NO,  NO,  PGUP,FN1, NO,  NO,  NO,  NO,  NO,       TRNS,\
        TRNS,MS_L,MS_D,MS_R,NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  NO,            TRNS,\
        TRNS,NO,  DEL, NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  TRNS,          TRNS,TRNS,\
        TRNS,TRNS,TRNS,          NO,                      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS \
    ),
};

uint8_t current_level = 8;

enum macro_id {
    MAC_EXPOSE,
    MAC_LAUNCHPAD,
    MAC_PRINT_SCREEN,
    RGB_LEVEL_DOWN,
    RGB_LEVEL_UP,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    keyevent_t event = record->event;

    switch (id) {
        case MAC_EXPOSE:
            return (event.pressed
                    ? MACRO(D(LCTL), T(UP), U(LCTL), END)
                    : MACRO(END));
        case MAC_LAUNCHPAD:
            return (event.pressed
                    ? MACRO(D(LSHIFT), D(LCTL), T(L), U(LCTL), U(LSHIFT), END)
                    : MACRO(END));
        case MAC_PRINT_SCREEN:
            return (event.pressed
                    ? MACRO(D(LGUI), D(LSHIFT), T(4), U(LSHIFT), U(LGUI), END)
                    : MACRO(END));
        case RGB_LEVEL_DOWN:
            if (event.pressed && current_level > 0) {
                current_level--;
            }
            break;
        case RGB_LEVEL_UP:
            if (event.pressed && current_level < 15) {
                current_level++;
            }
            break;
    }

    return MACRO_NONE;
}

const uint16_t fn_actions[] PROGMEM = {
    [0] = ACTION_LAYER_ONESHOT(1),
    [1] = ACTION_LAYER_TOGGLE(2),
    [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [3] = ACTION_MACRO(RGB_LEVEL_DOWN),
    [4] = ACTION_MACRO(RGB_LEVEL_UP),
    [5] = ACTION_MACRO(MAC_EXPOSE),
    [6] = ACTION_MACRO(MAC_LAUNCHPAD),
    [7] = ACTION_MACRO(MAC_PRINT_SCREEN),
};

void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b);

uint8_t dim(uint8_t color, uint8_t opacity) {
    return ((uint16_t) color * opacity / 0xFF) & 0xFF;
}

void user_setrgb(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t alpha = current_level * 0x11;
    rgblight_setrgb(dim(r, alpha), dim(g, alpha), dim(b, alpha));
}

void matrix_scan_user(void) {
    if (IS_LAYER_ON(2)) {
        user_setrgb(0x00, 0xFF, 0xFF);
    } else if (IS_LAYER_ON(1)) {
        user_setrgb(0xFF, 0x66, 0x00);
    } else {
        user_setrgb(0xFF, 0x00, 0x00);
    }
}
