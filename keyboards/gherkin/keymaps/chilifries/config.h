#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define PREVENT_STUCK_MODIFIERS

#undef RGB_DI_PIN
#undef RGBLED_NUM
#define RGB_DI_PIN F6
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 7
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#endif
