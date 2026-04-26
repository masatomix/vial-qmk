/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
*/

// Phase 1 minimal BMP keymap for Keyball44 masatomix.
// - Home Row Mods (GACS) 維持
// - 5 レイヤー構成（BASE/NAV/FKEYS/MOUSE/SYM）
// - Mod-Morph (Shift+BSPC → Del) 維持
// - BLE 管理キー (AD_WO_L / ADV_ID0-2 / SEL_USB / SEL_BLE) を L_FKEYS に配置
// - Combo/Tap Dance/per-key TAPPING_TERM は Vial UI で設定（vial-qmk は VIAL 必須のため）

#include QMK_KEYBOARD_H
#include "quantum/qmk_settings.h"

// Layer number definitions
#define L_BASE      0
#define L_NAV       1
#define L_FKEYS     2
#define L_MOUSE     3
#define L_SYM       4

// #825: Combo (J+K → Esc, D+F → Tab) を Pro Micro 版から復活
const uint16_t PROGMEM jk_combo[] = {RSFT_T(KC_J), RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM df_combo[] = {LCTL_T(KC_D), LSFT_T(KC_F), COMBO_END};
combo_t key_combos[] = {
    COMBO(jk_combo, KC_ESC),
    COMBO(df_combo, KC_TAB),
};

// #825: Tap Dance を Pro Micro 版から復活
enum {
    TD_SS1 = 0,  // 1tap=Mac Cmd+Shift+4 / 2tap=Win Alt+PrtSc
    TD_SS2,      // 1tap=Mac Cmd+Shift+5 / 2tap=Win PrtSc
    TD_PRN,      // 1tap=( / 2tap=)
    TD_CBR,      // 1tap={ / 2tap=}
    TD_BRC,      // 1tap=[ / 2tap=]
    TD_QUO,      // 1tap=' / 2tap="
};

void td_ss1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(SGUI(KC_4));        // Mac: Cmd+Shift+4
    } else if (state->count == 2) {
        tap_code16(LALT(KC_PSCR));     // Win: Alt+PrintScreen
    }
}

void td_ss2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(SGUI(KC_5));        // Mac: Cmd+Shift+5
    } else if (state->count == 2) {
        tap_code16(KC_PSCR);           // Win: PrintScreen
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SS1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ss1_finished, NULL),
    [TD_SS2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ss2_finished, NULL),
    [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(S(KC_9), S(KC_0)),         // ( )
    [TD_CBR] = ACTION_TAP_DANCE_DOUBLE(S(KC_LBRC), S(KC_RBRC)),   // { }
    [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),         // [ ]
    [TD_QUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, S(KC_QUOT)),      // ' "
};

// #825 Phase B: per-key TAPPING_TERM (Pro Micro 版から移植)
// #736 GUI 300ms / #780 Shift 170ms / 他 250ms (config.h TAPPING_TERM)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case RGUI_T(KC_SCLN):
            return 300;
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
            return 170;
        default:
            return TAPPING_TERM;
    }
}

// #825 Phase B: per-key PERMISSIVE_HOLD (#744 F/J Shift のみ true)
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
            return true;
        default:
            return false;
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0: Base QWERTY (Mac/Win 共通)
  [L_BASE] = LAYOUT_universal(
    KC_NO  , KC_Q        , KC_W        , KC_E        , KC_R        , KC_T           ,                       KC_Y    , KC_U        , KC_I        , KC_O        , KC_P           , KC_NO ,
    KC_NO  , LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), LT(L_MOUSE,KC_G),                       KC_H    , RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_NO ,
    KC_NO  , KC_Z        , KC_X        , KC_C        , KC_V        , KC_B           ,                       KC_N    , KC_M        , KC_COMM     , KC_DOT      , LT(L_MOUSE,KC_SLSH), KC_NO,
              KC_LSFT    , KC_LNG1     , MO(L_SYM)   , LT(L_NAV,KC_SPC), LT(L_FKEYS,KC_LNG2),      KC_BSPC , LT(L_NAV,KC_ENT), _______, _______, LT(L_SYM,KC_GRAVE)
  ),

  // Layer 1: Navigation
  [L_NAV] = LAYOUT_universal(
    _______, LCTL(KC_UP)   , LCTL(KC_DOWN)  , KC_PGUP       , KC_UP          , KC_F11      ,                         _______, _______         , _______     , KC_PGUP , KC_UP  , _______,
    _______, LGUI_T(KC_VOLD), LALT_T(KC_VOLU), LCTL_T(KC_DEL), LSFT_T(KC_RGHT), LALT(KC_ESC),                         KC_LEFT, RSFT_T(KC_DOWN) , RCTL_T(KC_UP), RALT_T(KC_RGHT), _______, _______,
    _______, KC_BTN4       , KC_BTN5        , KC_PGDN       , KC_DOWN        , KC_LEFT     ,                         KC_DOWN, _______         , _______     , KC_PGDN , _______, _______,
              _______     , _______        , _______       , _______        , _______     ,                         KC_DEL , _______         , _______     , _______ , _______
  ),

  // Layer 2: F-keys (BLE 管理キー含む)
  [L_FKEYS] = LAYOUT_universal(
    _______, KC_F11 , KC_F12 , _______, _______, _______,                         _______ , TD(TD_SS1), TD(TD_SS2), _______ , _______ , _______,
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______,
    _______, AD_WO_L, ADV_ID0, ADV_ID1, ADV_ID2, SEL_BLE,                         CPI_D100, CPI_I100, SCRL_DVD, SCRL_DVI, KBC_SAVE, _______,
              _______, _______, _______, _______, SEL_USB,                         _______ , _______ , _______ , _______ , KBC_RST
  ),

  // Layer 3: Mouse
  [L_MOUSE] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
    _______, KC_BTN4, KC_BTN5, _______, _______, _______,                         _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
              _______, _______, _______, KC_BTN1, _______,                         _______, _______, _______, _______, _______
  ),

  // Layer 4: Symbols/Numbers
  [L_SYM] = LAYOUT_universal(
    _______, S(KC_1)     , S(KC_2)     , S(KC_3)     , S(KC_4)     , S(KC_5),                         S(KC_6), S(KC_7)     , S(KC_8)     , S(KC_9)     , S(KC_0)     , _______,
    _______, LGUI_T(KC_1), LALT_T(KC_2), LCTL_T(KC_3), LSFT_T(KC_4), KC_5   ,                         KC_6   , RSFT_T(KC_7), RCTL_T(KC_8), RALT_T(KC_9), RGUI_T(KC_0), _______,
    _______, KC_BSLS     , TD(TD_QUO)  , TD(TD_PRN)  , TD(TD_CBR)  , TD(TD_BRC),                      KC_EQL , KC_MINS     , _______     , _______     , _______     , _______,
              _______    , _______     , _______     , _______     , _______,                         _______, _______    , _______     , _______     , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Mod-Morph: Shift+Backspace → Delete (K44 は維持、K39 は #809 で撤廃)
        case KC_BSPC: {
            static bool del_registered = false;
            if (record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    del_registered = true;
                    set_mods(mods);
                    return false;
                }
            } else {
                if (del_registered) {
                    unregister_code(KC_DEL);
                    del_registered = false;
                    return false;
                }
            }
            return true;
        }
        default:
            break;
    }
    return true;
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
}

// #828: BMP 版はデフォルトで QMK 純正と逆方向のスクロールになるため、
// keyball_on_apply_motion_to_mouse_scroll を override して符号反転する。
// keyball.c:190 の weak 実装に対する強い override。
// keyball.c の static helper (divmod16/clip2int8) は外部から見えないので複製。
static int16_t k_divmod16(int16_t *v, int16_t div) {
    int16_t r = *v / div;
    *v -= r * div;
    return r;
}
static inline int8_t k_clip2int8(int16_t v) {
    return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v;
}

void keyball_on_apply_motion_to_mouse_scroll(keyball_motion_t *m, report_mouse_t *r, bool is_left) {
    int16_t div = 1 << (keyball_get_scroll_div() - 1);
    int16_t x = k_divmod16(&m->x, div);
    int16_t y = k_divmod16(&m->y, div);

    // 純正と同じ向きへ反転 (元実装は r->h = -clip2int8(y), r->v = clip2int8(x))
    r->h = k_clip2int8(y);
    r->v = -k_clip2int8(x);
    if (is_left) {
        r->h = -r->h;
        r->v = -r->v;
    }

    // Scroll snapping (KEYBALL_SCROLLSNAP_ENABLE == 2 経路、上流と同等)
#if KEYBALL_SCROLLSNAP_ENABLE == 2
    switch (keyball_get_scrollsnap_mode()) {
        case KEYBALL_SCROLLSNAP_MODE_VERTICAL:
            r->h = 0;
            break;
        case KEYBALL_SCROLLSNAP_MODE_HORIZONTAL:
            r->v = 0;
            break;
        default:
            break;
    }
#endif
}
