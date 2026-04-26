/*
This is the c configuration file for the keymap

Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#endif

#define TAP_CODE_DELAY 5

// ---- Home Row Mods (GACS) 関連設定 ----
#define TAPPING_TERM 250
#define QUICK_TAP_TERM 120

#define KEYBALL_CPI_DEFAULT 700       // マウス速度 (default: 700)
#define KEYBALL_SCROLL_DIV_DEFAULT 6  // スクロール速度 (default: 6)

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3    // L_MOUSE (3) に統一
#define AUTO_MOUSE_TIME 400

#define KEYBALL_SCROLLSNAP_ENABLE 2

// #825: Combo / Tap Dance を keymap.c 側で hardcoded 定義するため、
// vial.h の vial-managed Combo/TD を無効化する (vial.h を patch 済)。
// 副作用: Vial GUI の Combo / Tap Dance タブが効かなくなる (許容)。
#define VIAL_COMBO_DISABLE
#define VIAL_TAP_DANCE_DISABLE
