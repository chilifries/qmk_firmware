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
#define _TOUCHCURSOR 3
#define _MOUSECURSOR 4
#define _ADJUST 16

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MY_CMD_BACK,
  MY_CMD_FWD,
  MY_PREV_TAB,
  MY_NEXT_TAB
};

enum macro_keycodes {
  KC_ALT_TAB,
  KC_CMD_TAB,
  KC_CTL_TAB,
  KC_CMD_SLSH,
  KC_AG_FIND,
  KC_AG_AGAIN,
  KC_AG_UNDO,
  KC_AG_CUT,
  KC_AG_COPY,
  KC_AG_PASTE,
  KC_AG_DESK_L,
  KC_AG_DESK_R,
  KC_AG_TAB_C,
  KC_AG_TAB_N,
  KC_AG_TAB_R,
  KC_CS_TAB,
  KC_CMD_BACK,
  KC_CMD_FWD,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
#define SFT_BSP     SFT_T(KC_BSPC)              // Tap for Backspace, hold for Shift
#define HPR_TAB     ALL_T(KC_TAB)               // Tap for Tab, hold for Hyper
#define GUI_SEM     GUI_T(KC_SCLN)              // Tap for Semicolon, hold for GUI
#define ALT_QUO     ALT_T(KC_QUOT)              // Tap for Quote, hold for Alt
// Requires KC_TRNS/_______ for the trigger key in the destination layer
// #define LT_TC       LT(_TOUCHCURSOR, KC_SPC)    // L-ayer T-ap T-ouch C-ursor
#define LT_TC(kc)   LT(_TOUCHCURSOR, kc)        // L-ayer T-ap T-ouch C-ursor
#define LT_MC(kc)   LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor
#define ALT_TAB     M(KC_ALT_TAB)               // Macro for Alt-Tab
// #define CMD_TAB     M(KC_CMD_TAB)               // Macro for Cmd-Tab
#define CMD_TAB     LGUI(KC_TAB)
#define CTL_TAB     M(KC_CTL_TAB)               // Macro for Ctl-Tab
#define CMD_SLSH    M(KC_CMD_SLSH)              // Macro for Cmd-Slash (personal shortcut to toggle iTerm2 visibility)
#define AG_FIND     M(KC_AG_FIND)               // Macros for Cmd-[x] vs Ctrl-[x] based on current AG_NORM or AG_SWAP settings
#define AG_AGAIN    M(KC_AG_AGAIN)
#define AG_UNDO     M(KC_AG_UNDO)
#define AG_CUT      M(KC_AG_CUT)
#define AG_COPY     M(KC_AG_COPY)
#define AG_PASTE    M(KC_AG_PASTE)
#define AG_D_L      M(KC_AG_DESK_L)             // For Virtual Desktop Switching: Left, and
#define AG_D_R      M(KC_AG_DESK_R)             //                                Right
#define AG_T_C      M(KC_AG_TAB_C)              // For Chrome, etc. Tab Close,
#define AG_T_N      M(KC_AG_TAB_N)              //                  Tab New, and
#define AG_T_R      M(KC_AG_TAB_R)              //                  Tab Reopen Closed
#define CS_TAB      M(KC_CS_TAB)                // Macro for Ctl-Shift-Tab

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
  KC_TAB,  KC_Q,    KC_W,    KC_E,        KC_R,    KC_T,          KC_Y,          KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \
  KC_LCTL, KC_A,    KC_S,    LT_MC(KC_D), KC_F,    KC_G,          KC_H,          KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,        KC_V,    KC_B,          KC_N,          KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT , \
  KC_GRV,  KC_LCTL, KC_LALT, KC_LGUI,     LOWER,   LT_TC(KC_SPC), LT_TC(KC_ENT), RAISE,   KC_LGUI, MY_PREV_TAB, MY_NEXT_TAB, MY_CMD_BACK \
),

/* Lower
 * ,------------------------------------------------------------------------------------.
 * | CmTb |   !  |   @  |   #  |   $  |   %  ||   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * |  [   |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |   -  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+--------------+------+------+------+------+------|
 * |  ]   |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 |   _  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  CMD_TAB, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_LBRC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  KC_RBRC, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
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
  KC_0  ,   KC_1,    KC_2,    KC_3,  KC_4,   KC_5,     KC_6,      KC_7,    KC_8,    KC_9,    KC_0,       KC_BSPC, \
  KC_DLR,   KC_4,    KC_5,    KC_6,  KC_DOT, KC_PLUS,  KC_DOT,    KC_4,    KC_5,    KC_6,    KC_ASTR,    KC_PIPE, \
  KC_EQL,   KC_7,    KC_8,    KC_9,  KC_0,   KC_MINS,  KC_DOT,    KC_1,    KC_2,    KC_3,    KC_SLSH,    KC_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, _______,  KC_MNXT, KC_VOLD, KC_VOLU,    KC_MPLY \
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

/* Mouse Layer
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |         |      |ACCL0 |      |      |      |      |WHL_L |  Up  |WHL_R | BTN2 |      |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |ACCL2 | BTN2 |      | BTN1 |ACCL1 |WHL_Up| Left | Down |Right | BTN4 |   BTN5     |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |      | BTN3 |      |WHL_Dn| BTN1 |      |      | BTN3 |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |          |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */

[_MOUSECURSOR] = KEYMAP(
    _______, _______, KC_ACL0, _______, _______, _______, _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN1, _______,
    _______, KC_ACL2, KC_BTN2, _______, KC_BTN1, KC_ACL1, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN4, KC_BTN5,
    _______, _______, _______, _______, KC_BTN3, _______, KC_WH_D, KC_BTN2, _______, _______, KC_BTN3, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
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

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }

    /*
    bool use_cmd = true;    // Use, for example, Cmd-Tab, Cmd-C, Cmd-V, etc.
    // Compare to MAGIC_SWAP_ALT_GUI and MAGIC_UNSWAP_ALT_GUI configs, set in:
    // quantum/quantum.c
    if(keymap_config.swap_lalt_lgui == 1 && keymap_config.swap_ralt_rgui == 1) {
      use_cmd = false;      // ... or, Alt-Tab, Ctrl-C, Ctrl-V, etc.
    }

    switch (id) {
    }
    */
    
    return MACRO_NONE;
}
