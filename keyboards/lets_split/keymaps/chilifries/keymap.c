#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,------------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  ||   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * | Ctrl |   A  |   R  |   S  |   T  |   D  ||   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * | Shft |   Z  |   X  |   C  |   V  |   B  ||   K  |   M  |   ,  |   .  |   /  | Shft |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |  ~   | Ctrl | Alt  | GUI  | Lowr | Spc  || Entr | Rais | Left | Down |  Up  | Rght |
 * `------------------------------------------------------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,        KC_P,    KC_G,          KC_J,          KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  CTL_ESC, KC_A,    KC_R,    LT_MC(KC_S), KC_T,    KC_D,          KC_H,          KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,        KC_V,    KC_B,          KC_K,          KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_GRV,  KC_LCTL, KC_LALT, KC_LGUI,     LOWER,   LT_TC(KC_SPC), LT_TC(KC_ENT), RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
//  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI,     LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,------------------------------------------------------------------------------------.
 * | CmTb |   !  |   @  |   #  |   $  |   %  ||   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * |  [   |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * |  ]   |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 |   _  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_LBRC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  KC_RBRC, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,------------------------------------------------------------------------------------.
 * |   0  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * |   $  |   4  |   5  |   6  |   .  |   +  ||   .  |   4  |   5  |   6  |   *  |   |  |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * |   =  |   7  |   8  |   9  |   0  |   -  ||   .  |   1  |   2  |   3  |   /  |   \  |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Next | Vol- | Vol+ | Play |
 * `------------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_0   ,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
  KC_DLR  ,   KC_4,    KC_5,    KC_6,  KC_DOT, KC_PLUS,  KC_DOT,    KC_4,    KC_5,    KC_6, KC_ASTR,    KC_PIPE, \
  KC_EQL   ,   KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_DOT,    KC_1,    KC_2,    KC_3, KC_SLSH,    KC_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |Colemk|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, COLEMAK, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* TouchCursor layer (http://martin-stone.github.io/touchcursor/) plus personal customizations
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * | CtlTab  |CmdTab|AltTab| Find |Shift |Again |Insert| Home |  Up  | End  | Bksp |      |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          | Alt  |Space |Tab_C |      |      | PgUp | Left | Down |Right |Desk_L|  Desk_R    |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           | Undo | Cut  | Copy |Paste |  `   | PgDn | Del  |Tab_N |Tab_R |iTerm2|           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |          |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 *
 * The KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, KC_FIND, and KC_AGAIN keycodes don't
 * seem to work on Mac. Presumably they'll work under Windows.
 */

[_TOUCHCURSOR] = KEYMAP( \
    CTL_TAB, CMD_TAB, ALT_TAB, AG_FIND, KC_LSFT,  AG_AGAIN, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_BSPC,  _______, \
    _______, KC_LALT, KC_SPC,  AG_T_C,  AG_FIND,  AG_AGAIN, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______,  _______, \
    _______, AG_UNDO, AG_CUT,  AG_COPY, AG_PASTE, KC_GRV,   KC_PGDN, KC_DEL,  AG_T_N,  AG_T_R,  CMD_SLSH, _______, \
    _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______,  _______  \
),

};

#ifdef AUDIO_ENABLE
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
