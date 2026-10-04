// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"

// Priority increases with layer number. Base must stay at zero for combos.
enum nerf_caffeine_layers {
    NC_BASE,
    NC_NAV,
    NC_SYM,
    NC_NUM,
    NC_RESET,
};

#define NC_NAV_F LT(NC_NAV, KC_F)
#define NC_SYM_F4 LT(NC_SYM, KC_F4)
#define NC_NUM_HOLD MO(NC_NUM)
#define NC_RAYCAST LGUI(KC_SPC)
#define NC_LAST_APP LGUI(KC_TAB)

#define NC_SFT_Z LSFT_T(KC_Z)
#define NC_ALT_X LALT_T(KC_X)
#define NC_GUI_C LGUI_T(KC_C)
#define NC_CTL_V LCTL_T(KC_V)
#define NC_CTL_M RCTL_T(KC_M)
#define NC_GUI_COMM RGUI_T(KC_COMM)
#define NC_ALT_DOT RALT_T(KC_DOT)
#define NC_SFT_SLSH RSFT_T(KC_SLSH)
