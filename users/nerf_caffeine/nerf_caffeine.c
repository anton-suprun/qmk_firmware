// SPDX-License-Identifier: GPL-2.0-or-later
#include "nerf_caffeine.h"

const uint16_t PROGMEM nc_enter_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM nc_escape_combo[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(nc_enter_combo, KC_ENT),
    COMBO(nc_escape_combo, KC_ESC),
};

const key_override_t nc_previous_word = ko_make_basic(MOD_MASK_ALT, KC_H, LALT(KC_LEFT));
const key_override_t nc_next_word     = ko_make_basic(MOD_MASK_ALT, KC_L, LALT(KC_RIGHT));
const key_override_t nc_underscore    = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_UNDS);
const key_override_t nc_delete_word   = ko_make_basic(MOD_MASK_ALT, KC_SPC, LALT(KC_DEL));

const key_override_t **key_overrides = (const key_override_t *[]){
    &nc_previous_word,
    &nc_next_word,
    &nc_underscore,
    &nc_delete_word,
    NULL,
};

// QMK layers are bits, not reference counts. Intercept the hold action so
// releasing one F4/Symbols thumb cannot cancel the other thumb's hold.
static uint8_t symbols_holds;

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, NC_SYM, NC_NUM, NC_RESET);
}

// Preserve absoluteunit1's same-side typing repairs, including other held mods.
static bool repair_pair(uint8_t modifier, uint8_t first, uint8_t second) {
    if (!(get_mods() & modifier)) {
        return true;
    }

    unregister_mods(modifier);
    tap_code(first);
    tap_code(second);
    add_mods(modifier);
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == NC_SYM_F4 && record->tap.count == 0) {
        if (record->event.pressed) {
            ++symbols_holds;
            layer_on(NC_SYM);
        } else if (symbols_holds > 0 && --symbols_holds == 0) {
            layer_off(NC_SYM);
        }
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case KC_A:
            if (!repair_pair(MOD_BIT(KC_LGUI), KC_C, KC_A)) {
                return false;
            }
            return repair_pair(MOD_BIT(KC_LCTL), KC_V, KC_A);
        case KC_W:
            return repair_pair(MOD_BIT(KC_LGUI), KC_C, KC_W);
        case KC_R:
            return repair_pair(MOD_BIT(KC_LGUI), KC_C, KC_R);
        case KC_S:
            // Keep the original extra guard; do not broaden this exception.
            if (record->tap.count > 0) {
                return repair_pair(MOD_BIT(KC_LGUI), KC_C, KC_S);
            }
            return true;
        case KC_E:
            return repair_pair(MOD_BIT(KC_LCTL), KC_V, KC_E);
        case KC_I:
            return repair_pair(MOD_BIT(KC_RCTL), KC_M, KC_I);
        case KC_O:
            return repair_pair(MOD_BIT(KC_RCTL), KC_M, KC_O);
        default:
            return true;
    }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_UNDS:
            return true;
        default:
            return false;
    }
}
