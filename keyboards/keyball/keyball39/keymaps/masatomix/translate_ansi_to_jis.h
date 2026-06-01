// US(ANSI) -> JIS keycode translation (single-keycode helper).
//
// Table from m47ch4n/qmk-translate-ansi-to-jis (MIT License), vendored from
// the wired #1019 work (keyball_masatomix). On BMP (#1025) the *direct* keys
// are translated by the BMP-native US-on-JIS override (process_record_bmp が
// S(KC_n) を分解して key_override を発火させる)。process_record を通らない
// TapDance / Layer-Tap のタップだけ a2j_translate() で JIS へ変換する。
#pragma once

#include "quantum.h"

// Translate a (possibly shift-embedded) ANSI keycode to its JIS equivalent.
// Returns the JIS keycode if the table has a mapping, else returns kc unchanged.
uint16_t a2j_translate(uint16_t kc);
