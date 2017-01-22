// this converts from my ps2avrGB keymap to gh60 satan, so I can reuse the
// keymap from my larger board to my smaller one
#undef KEYMAP
#define KEYMAP( \
    K05, K25, K35, K45, K55, K06, KA6, KA7, K07, KB5, KC5, KD5, KE5, KD1, KE1, KE2, \
    K04, K14, K24, K34, K44, K54, K16, KB6, KB7, K17, KA4, KB4, KC4, KE4,      KD0, \
    K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, KC3, KD3,      K67, \
    K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, KB2, KD2,           KE0, \
    K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, KB1,           K86, K77, \
    K00, K10, K20,           K56,                     K57, KB0, KC0, K66, K76, K96  \
) KEYMAP_ANSI( \
    KC_##K04, KC_##K14, KC_##K24, KC_##K34, KC_##K44, KC_##K54, KC_##K16, KC_##KB6, KC_##KB7, KC_##K17, KC_##KA4, KC_##KB4, KC_##KC4, KC_##KE4, \
    KC_##K03, KC_##K13, KC_##K23, KC_##K33, KC_##K43, KC_##K53, KC_##K26, KC_##KC6, KC_##KC7, KC_##K27, KC_##KA3, KC_##KB3, KC_##KC3, KC_##KD3, \
    KC_##K02, KC_##K12, KC_##K22, KC_##K32, KC_##K42, KC_##K52, KC_##K36, KC_##KD6, KC_##KD7, KC_##K37, KC_##KA2, KC_##KB2, KC_##KD2,      \
    KC_##K01, KC_##K11, KC_##K21, KC_##K31, KC_##K41, KC_##K51, KC_##K46, KC_##KE6, KC_##KE7, KC_##K47, KC_##KA1, KC_##KB1,           \
    KC_##K00, KC_##K10, KC_##K20,           KC_##K56,                     KC_##K67, KC_##K57, KC_##KB0, KC_##KC0  \
)
