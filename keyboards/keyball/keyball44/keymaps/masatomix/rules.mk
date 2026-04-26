RGBLIGHT_ENABLE = yes

OLED_ENABLE = yes

VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes

# #833: メディアキー (KC_VOLU/KC_VOLD/KC_MUTE 等) を有効化
EXTRAKEY_ENABLE = yes

# #825: Combo / Tap Dance をファームで直接定義する (vial.h の VIAL_*_DISABLE guard と組合せ)
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes

# #827: USB 接続時の Mass Storage Class (BLEMICROPRO ドライブ) を無効化する。
# セキュアな環境 (社用 PC 等) で USB Storage ブロック policy に引っかかるのを回避。
# DFU mode (bootloader 経由) では別系統で MSC が出るので flash 書込は可能。
OPT_DEFS += -DDISABLE_MSC=1
