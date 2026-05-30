// US(ANSI) -> JIS keycode translation (single-keycode helper).
//
// Table from m47ch4n/qmk-translate-ansi-to-jis (MIT License).
//   https://github.com/m47ch4n/qmk-translate-ansi-to-jis
//   Copyright (c) m47ch4n
// Vendored from the wired #1019 work. On BMP (#1025) only a2j_translate() is
// used (TapDance / Layer-Tap のタップ変換用)。直キーは BMP ネイティブ override。

#include QMK_KEYBOARD_H
#include "translate_ansi_to_jis.h"

// ANSI keycode -> JIS keycode. Keyed on the (shift-embedded) ANSI keycode,
// e.g. KC_AT == S(KC_2).
static const uint16_t translate_map[][2] = {
    // clang-format off
    // ANSI    JIS
    {KC_EQL,  S(KC_MINS)},
    {KC_LBRC, KC_RBRC},
    {KC_BSLS, KC_INT3},
    {KC_RBRC, KC_NUHS},
    {KC_QUOT, S(KC_7)},
    {KC_GRV,  S(KC_LBRC)},
    {KC_RPRN, S(KC_9)},
    {KC_AT,   KC_LBRC},
    {KC_CIRC, KC_EQL},
    {KC_AMPR, S(KC_6)},
    {KC_ASTR, S(KC_QUOT)},
    {KC_LPRN, S(KC_8)},
    {KC_PLUS, S(KC_SCLN)},
    {KC_UNDS, S(KC_INT1)},
    {KC_LCBR, S(KC_RBRC)},
    {KC_PIPE, S(KC_INT3)},
    {KC_RCBR, S(KC_NUHS)},
    {KC_COLN, KC_QUOT},
    {KC_DQT,  S(KC_2)},
    {KC_TILD, S(KC_EQL)},
    // clang-format on
};

static const size_t a2j_rows = sizeof(translate_map) / sizeof(translate_map[0]);

static uint16_t a2j_find(uint16_t kc) {
    for (size_t index = 0; index < a2j_rows; index++) {
        if (translate_map[index][0] == kc) return translate_map[index][1];
    }
    return 0;
}

uint16_t a2j_translate(uint16_t kc) {
    uint16_t jis = a2j_find(kc);
    return jis ? jis : kc;
}
