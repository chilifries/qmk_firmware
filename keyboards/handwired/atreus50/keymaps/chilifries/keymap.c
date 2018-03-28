#include "atreus50.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MOVEMENT 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MOVEMENT,
  BACKLIT,
  KC_CMD_BACK,
  KC_CMD_FWD,
  KC_PREV_TAB,
  KC_NEXT_TAB
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_X0 MT(MOD_LCTL, KC_ESC)  // Hold for Left Ctrl, Tap for ESC
#define KC_X1 LOWER
#define KC_X2 RAISE
#define KC_X3 MO(_MOVEMENT)
#define KC_X4 MT(MOD_RSFT, KC_ENT)  // Hold for Left Shift, Tap for Enter
#define KC_RST RESET
#define KC_CMTB LGUI(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = COMPACT_KEYMAP(
  //,----+----+----+----+----+----.         ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,           Y  , U  , I  , O  , P  ,BSLS,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,           H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,           N  , M  ,COMM,DOT ,SLSH, X4 ,
  //|----+----+----+----+----+----|----+----|----+----+----+----+----+----|
     GRV ,LCTL,LALT,LGUI, X1 ,SPC ,SPC ,ENT ,ENT ,X2  ,RGUI,PREV_TAB,NEXT_TAB,CMD_BACK
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),

  [_LOWER] = COMPACT_KEYMAP(
  //,----+----+----+----+----+----.         ,----+----+----+----+----+----.
     CMTB,EXLM, AT ,HASH,DLR ,PERC,          CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
     LBRC, F1 , F2 , F3 , F4 , F5 ,           F6 ,MINS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
     RBRC, F7 , F8 , F9 , F10, F11,           F12,UNDS, EQL,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----|----+----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,MNXT,VOLD,VOLU,MPLY
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),

  [_RAISE] = COMPACT_KEYMAP(
  //,----+----+----+----+----+----.         ,----+----+----+----+----+----.
      0  , 1  , 2  , 3  , 4  , 5  ,           6  , 7  , 8  , 9  , 0  ,DEL ,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
      DLR, 4  , 5  , 6  , DOT,PLUS,          DOT , 4  , 5  , 6  ,ASTR,PIPE,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
      EQL, 7  , 8  , 9  , 0  ,MINS,          DOT , 1  , 2  , 3  ,SLSH,BSLS,
  //|----+----+----+----+----+----|----+----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,MNXT,VOLD,VOLU,MPLY
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),

  [_MOVEMENT] = COMPACT_KEYMAP(
  //,----+----+----+----+----+----.         ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,          CIRC,AMPR, UP ,LPRN,RPRN,DEL ,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
     DEL , F1 , F2 , F3 , F4 , F5 ,           F6 ,LEFT,DOWN,RGHT,RCBR,PIPE,
  //|----+----+----+----+----+----|         |----+----+----+----+----+----|
         , F7 , F8 , F9 ,F10 ,F11 ,          F12 ,END ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|----+----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,    ,PGDN,PGUP,MNXT,VOLD,VOLU,MPLY
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),

/* Adjust (Lower + Raise)
 * |------+------+------+------+------+------.             ,------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |             |      |      |      |      |      |  Del |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |      |Audoff|Aud on|AGnorm|             |AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |Voice-|Voice+|Musoff|Mus on|      |             |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_ADJUST] = KEYMAP( \
    _______, _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,                 RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL, \
    _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                 AG_SWAP, QWERTY,  _______, _______, _______, _______, \
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,                   MI_OFF,  _______, _______, _______, _______, _______, \
    RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )

};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_qwerty);
            #endif
            persistent_default_layer_set(1UL<<_QWERTY);
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
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
          return false;
          break;
        case KC_CMD_BACK:
          if (record->event.pressed) {
            SEND_STRING(SS_LGUI("["));
          }
          return false;
          break;
        case KC_CMD_FWD:
          if (record->event.pressed) {
            SEND_STRING(SS_LGUI("]"));
          }
          return false;
          break;
        case KC_PREV_TAB:
          if (record->event.pressed) {
            SEND_STRING(SS_LCTRL(SS_LSFT("\t")));
          }
          return false;
          break;
        case KC_NEXT_TAB:
          if (record->event.pressed) {
            SEND_STRING(SS_LCTRL("\t"));
          }
          return false;
          break;
      }
    return true;
};

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif
