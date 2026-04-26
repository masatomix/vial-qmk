/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
*/

// Keyball39 BMP masatomix keymap.
// - K44 BMP keymap と同等の構成、キー配置は K39 (post-#809) を踏襲
// - Home Row Mods (GACS) 維持
// - 5 レイヤー構成 (BASE/NAV/FKEYS/MOUSE/SYM)
// - 親指行: L30=LSFT / L31=TAB / L32=LNG1 (#809 適用済)
// - Mod-Morph (Shift+BS→Del) 無し (#809 で撤廃)
// - BLE 管理キー (AD_WO_L / ADV_ID0-2 / SEL_USB / SEL_BLE) を L_FKEYS に配置
// - Combo / Tap Dance / per-key TAPPING_TERM は VIAL 衝突回避で削除（#825 で別途対応）
// - QS.tapping |= 2 で HOLD_ON_OTHER_KEY_PRESS 無効化（K44 と同じ）

#include QMK_KEYBOARD_H
#include "quantum/qmk_settings.h"
#include "bmp_settings.h"
#include "print.h"
#include "dynamic_keymap.h"
#include "eeprom_bmp.h"

// Layer number definitions
#define L_BASE      0
#define L_NAV       1
#define L_FKEYS     2
#define L_MOUSE     3
#define L_SYM       4

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Keyball39 LAYOUT_universal:
  //   Row 0-2: 5+5 (外側列なし)
  //   Row 3:   6+6 (親指行、L30/R30 含む)

  // Layer 0: Base QWERTY (Mac/Win 共通)
  [L_BASE] = LAYOUT_universal(
    KC_Q       , KC_W     , KC_E     , KC_R      , KC_T ,                       KC_Y     , KC_U     , KC_I     , KC_O     , KC_P            ,
    LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), LT(L_MOUSE,KC_G) ,  KC_H     , RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN) ,
    KC_Z       , KC_X     , KC_C     , KC_V      , KC_B ,                       KC_N     , KC_M     , KC_COMM  , KC_DOT   , LT(L_MOUSE,KC_SLSH),
    KC_LSFT    , KC_TAB   ,KC_LNG1  , MO(L_SYM) ,LT(L_NAV,KC_SPC),LT(L_FKEYS,KC_LNG2),      KC_BSPC,LT(L_NAV,KC_ENT), _______  ,  _______ , _______           , LT(L_SYM,KC_GRAVE)
  ),

  // Layer 1: Navigation
  [L_NAV] = LAYOUT_universal(
    LCTL(KC_UP ), LCTL(KC_DOWN), KC_PGUP  , KC_UP   , KC_F11  ,                        _______ , _______  , _______   , KC_PGUP  , KC_UP     ,
    LGUI_T(KC_VOLD), LALT_T(KC_VOLU), LCTL_T(KC_DEL), LSFT_T(KC_RGHT), LALT(KC_ESC), KC_LEFT, RSFT_T(KC_DOWN), RCTL_T(KC_UP), RALT_T(KC_RGHT), _______,
    KC_BTN4     , KC_BTN5      , KC_PGDN  , KC_DOWN , KC_LEFT ,                        KC_DOWN , _______  , _______   , KC_PGDN  , _______   ,
    _______     , _______      , _______  , _______ , _______ , _______,                        KC_DEL  , _______  , _______   , _______  , _______, _______
  ),

  // Layer 2: F-keys (BLE 管理キー含む、K44 BMP と同位置)
  // L02 (E 位置) に DISABLE_KEY_OS_OVERRIDE を仮配置: BMP デフォルト EEPROM の
  // BMP_US_KEY_JP_OS_OVERRIDE が S(KC_2) を JP_AT(KC_LBRC) に翻訳して macOS ANSI 解釈で
  // [ が出る現象の解除用。L_FKEYS に入って 1 回押せば EEPROM=DISABLE で永続化される。
  [L_FKEYS] = LAYOUT_universal(
    KC_F11   , KC_F12   , DISABLE_KEY_OS_OVERRIDE, _______, _______,                   _______  , _______  , _______  , _______  , _______          ,
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                             KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10  ,
    AD_WO_L  , ADV_ID0  , ADV_ID1  , ADV_ID2  , SEL_BLE  ,                             CPI_D100 , CPI_I100 , SCRL_DVD , SCRL_DVI , KBC_SAVE,
    _______  , _______  , _______  , _______  , _______  , SEL_USB,                            _______  , _______  , _______  , _______  , _______, KBC_RST
  ),

  // Layer 3: Mouse
  [L_MOUSE] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______  , _______  , _______ ,
    _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______  , _______  , _______ ,
    KC_BTN4  , KC_BTN5  , _______  , _______  , _______  ,                             _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  ,
    _______  , _______  , _______  , _______  , KC_BTN1  , _______,                             _______  , _______  , _______  , _______  , _______, _______
  ),

  // Layer 4: Symbols/Numbers
  [L_SYM] = LAYOUT_universal(
    S(KC_1)  , S(KC_2)  , S(KC_3)   , S(KC_4) , S(KC_5) ,                   S(KC_6)  , S(KC_7)   , S(KC_8) , S(KC_9)  , S(KC_0)  ,
    LGUI_T(KC_1), LALT_T(KC_2), LCTL_T(KC_3), LSFT_T(KC_4), KC_5,          KC_6     , RSFT_T(KC_7), RCTL_T(KC_8), RALT_T(KC_9), RGUI_T(KC_0) ,
    KC_BSLS  , KC_QUOT  , S(KC_9)  , S(KC_LBRC), KC_LBRC ,                            KC_EQL   , KC_MINS   , _______ , _______  , _______  ,
    _______  , _______  , _______  ,  _______  , _______ , _______,                             _______  , _______   , _______ , _______  , _______, _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is Symbols
    keyball_set_scroll_mode(get_highest_layer(state) == L_SYM);

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case L_NAV:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }
#endif

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

void keyboard_post_init_user(void) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_enable(true);
#endif
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_FREE);

    // vial-qmk は build_vial.mk で HOLD_ON_OTHER_KEY_PRESS_PER_KEY を強制定義し、
    // qmk_settings の get_hold_on_other_key_press は !(QS.tapping & 2) を返す。
    // QS.tapping の default は 0 のため HOLD_ON_OTHER_KEY_PRESS=TRUE 状態 →
    // Mod-Tap キーを押しながら別キーに触れた瞬間に Mod 確定する超アグレッシブ挙動。
    // bit 1 (IGNORE_MOD_TAP_INTERRUPT) を立てて無効化する。
    QS.tapping |= 2;

    // 注: ここで bmp_set_key_os_override を呼んでも、続く protocol_post_init →
    // bmp_settings_init で EEPROM 値が再読込され override が再登録される。
    // 代わりに housekeeping_task_user で 1 回だけ disable する (下記)。
}

// Keyball の housekeeping_task_kb (keyball.c:589) は _user を呼んでくれないので
// matrix_scan_user で代用 (こちらは keyball.c:795 で呼ばれる)。
void matrix_scan_user(void) {
    static bool initialized = false;
    if (!initialized) {
        println("[k39-fix] matrix_scan_user: erase default + reset dynamic_keymap");
        // BMP の dynamic_keymap_reset は最初に eeprom_bmp_load_default を試して
        // 成功したら C ソースからの再書込をスキップする。default snapshot が
        // EEPROM に保存されてるとそれが永続的に再ロードされ続けるので、先に
        // erase_default で snapshot を消去してから reset を呼ぶ。
        eeprom_bmp_erase_default();
        dynamic_keymap_reset();
        // process_record_bmp.c の QK_MODS 分割を bypass する patch を当ててあるので
        // S(KC_2) は素の QMK 経路を通り override 適用されない。
        // bmp_set_key_os_override も念のため EEPROM=DISABLE で書込（次回 boot 用）。
        bmp_set_key_os_override(BMP_KEY_OS_OVERRIDE_DISABLE);
        println("[k39-fix] done");
        initialized = true;
    }
}
