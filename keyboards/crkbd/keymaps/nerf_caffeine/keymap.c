// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "nerf_caffeine.h"

// All layouts show each half from left to right, including the thumb keys.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NC_BASE] = LAYOUT_split_3x5_3(
        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,       KC_Y,    KC_U,     KC_I,        KC_O,       KC_TAB,
        KC_A,     KC_S,     KC_D,     NC_NAV_F, KC_G,       KC_H,    KC_J,     KC_K,        KC_L,       KC_P,
        NC_SFT_Z, NC_ALT_X, NC_GUI_C, NC_CTL_V, KC_B,       KC_N,    NC_CTL_M, NC_GUI_COMM, NC_ALT_DOT, NC_SFT_SLSH,
                          NC_NUM_HOLD, NC_SYM_F4, KC_BSPC, KC_SPC, NC_SYM_F4, NC_RAYCAST
    ),

    [NC_NAV] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, NC_LAST_APP,
        _______, _______, _______, _______, _______,      _______, KC_TAB,  S(KC_TAB), _______, _______,
                               _______, _______, KC_DEL,  _______, _______, _______
    ),

    [NC_SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_AMPR, KC_PERC,         KC_SCLN, KC_LPRN, KC_RPRN, KC_QUES, QK_CAPS_WORD_TOGGLE,
        KC_DQUO, KC_GRV,  KC_UNDS, KC_TILD, KC_ASTR,         KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_COLN,
        KC_QUOT, KC_MINS, KC_PLUS, KC_EQL,  KC_BSLS,         KC_LT,   KC_LBRC, KC_RBRC, KC_GT,   KC_PIPE,
                               _______, _______, _______, _______, _______, _______
    ),

    [NC_NUM] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,      KC_SLSH, KC_7, KC_8, KC_9, KC_ASTR,
        _______, _______, _______, _______, _______,      KC_MINS, KC_4, KC_5, KC_6, KC_PLUS,
        _______, _______, _______, _______, _______,      KC_EQL,  KC_1, KC_2, KC_3, KC_DOT,
                               _______, _______, _______, KC_SPC, KC_0, KC_ENT
    ),

    [NC_RESET] = LAYOUT_split_3x5_3(
        QK_BOOT, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
                               _______, _______, _______,  _______, _______, _______
    ),
};
