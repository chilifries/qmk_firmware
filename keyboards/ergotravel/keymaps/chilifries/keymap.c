#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MOVEMENT 3
#define _ADJUST 16
#define CMD_TAB     LGUI(KC_TAB)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MOVEMENT,
  ADJUST,
  MY_CMD_BACK,
  MY_CMD_FWD,
  MY_PREV_TAB,
  MY_NEXT_TAB
};

// #define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_X3 LT(_MOVEMENT, KC_SPC)
#define KC_X5 LT(_MOVEMENT, KC_ENT)

enum macro_keycodes {
  KC_CMD_TAB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_SPC,           KC_SPC,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_SPC,           KC_SPC,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,           KC_SPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_GRV,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_X3,                              KC_X5,   RAISE,   KC_LGUI, MY_PREV_TAB, MY_NEXT_TAB, MY_CMD_BACK 
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     CMD_TAB, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_SPC,           KC_SPC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LBRC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_SPC,           KC_SPC,  KC_F6,   KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_RBRC, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_SPC,           KC_SPC,  KC_F12,  KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                            _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_RAISE] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_0  ,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_SPC,           KC_SPC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_DLR,   KC_4,    KC_5,    KC_6,  KC_DOT, KC_PLUS,  KC_SPC,            KC_SPC,  KC_DOT,    KC_4,    KC_5,    KC_6,    KC_ASTR,    KC_PIPE, 
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_EQL,   KC_7,    KC_8,    KC_9,  KC_0,   KC_MINS,  KC_SPC,            KC_SPC,  KC_DOT,    KC_1,    KC_2,    KC_3,    KC_SLSH,    KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                            _______, _______,  KC_MNXT, KC_VOLD, KC_VOLU,    KC_MPLY
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_MOVEMENT] = LAYOUT(
  CMD_TAB, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_SPC, KC_SPC, KC_CIRC, KC_HOME, KC_UP,   KC_END,  KC_RPRN, KC_BSPC, 
  KC_LBRC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_SPC, KC_SPC, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_RCBR, KC_PIPE, 
  KC_RBRC, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_SPC, KC_SPC, KC_PGDN, KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, 
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY 
  ),


  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_ESC,  RESET,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_C,             KC_D,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_A,             KC_SPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_LGUI, KC_LALT, ADJUST,           LOWER,   KC_SPC,           KC_SPC,  RAISE,            KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        set_single_persistent_default_layer(_QWERTY);
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
    case MY_CMD_BACK:
      if (record->event.pressed) {
	SEND_STRING(SS_LGUI("["));
      }
      return false;
      break;
    case MY_CMD_FWD:
      if (record->event.pressed) {
	SEND_STRING(SS_LGUI("]"));
      }
      return false;
      break;
    case MY_PREV_TAB:
      if (record->event.pressed) {
	SEND_STRING(SS_LCTRL(SS_LSFT("\t")));
      }
      return false;
      break;
    case MY_NEXT_TAB:
      if (record->event.pressed) {
	SEND_STRING(SS_LCTRL("\t"));
      }
      return false;
      break;
  }
  return true;
}
