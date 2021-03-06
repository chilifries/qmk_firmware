// Below layout is based upon /u/That-Canadian's planck layout
#include "launchpad.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0

#define _FUNC 15

#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define TESTSONG PLAY_SONG(my_song)

float my_song[][2] = SONG(QWERTY_SOUND);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------.
 * |   1  |  2   |  
 * |------+------|
 * |   3  |  4   | 
 * |------+------|
 * |   5  |  6   |
 * |------+------|
 * | FUNC |  8   |
 * `-------------'
 */
[_QWERTY] = LAYOUT( \
    KC_RTOG,      KC_RMOD, \
    KC_3,      KC_4, \
    KC_5,      KC_6, \
    MO(_FUNC), KC_8  \
),

/* Function
 * ,-------------.
 * |   Q  |CALDEL|  
 * |------+------|
 * |   A  |TSKMGR| 
 * |------+------|
 * |   Z  |  X   |
 * |------+------|
 * |      |  C   |
 * `-------------'
 */
[_FUNC] = LAYOUT( \
    KC_Q,    CALTDEL, \
    KC_A,    TSKMGR, \
    KC_Z,    KC_X, \
    _______, KC_C \
)

};

void matrix_init_user(void) {
    
}
