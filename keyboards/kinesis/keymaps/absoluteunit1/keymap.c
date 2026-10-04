#include QMK_KEYBOARD_H

// LAYERS
enum layer_names {
    _QWERTY,
    _NUMPAD,
    _NAVIGATION,
    _SYMBOLS,
    _LEAGUE,
};

/// COMMON UTILS
#define DICTATION          HYPR(KC_F14)
#define SCREENSHOT_FULL    LCAG(KC_F16)
#define SCREENSHOT_OPTIONS HYPR(KC_F16)
#define LAST_APP           LGUI(KC_TAB)

// TEXT NAVIGATION MACROS
#define NEXT_WORD              LALT(KC_RIGHT)
#define PREV_WORD              LALT(KC_LEFT)
#define DEL_LAST_WORD          LALT(KC_BSPC)

// RAYCAST MACROS
#define C_HIS              RAG(KC_P)
#define WINDOWS            HYPR(KC_F17)
#define SNIPPETS           HYPR(KC_F13)
#define RAYCAST            LGUI(KC_SPC)

// notes
// have 5 slots
// needs:
//      - using mac desktops

// WINDOW MANAGEMENT

// function keys: potentially even assign a function key to a common macos functionality and put it on the layer tap button on the bottom row
// potentially make a button for alt+ on the thumb keys and then add all common combos there or just add a layer for all these common symbol combos
// create a layer for function keys

// LAYER DEFINITIONS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_pretty(
    KC_BRID,             KC_BRIU, KC_F1,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   QK_COMBO_TOGGLE,  TG(_LEAGUE),    KC_MPRV, KC_MNXT, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, TG(_LEAGUE), QK_BOOT,

    QK_LEAD,             KC_1,         KC_2,         KC_3,         KC_4,                  KC_5,         KC_6,   KC_7,         KC_8,            KC_9,           KC_0,            DICTATION,
    QK_CAPS_WORD_TOGGLE, KC_Q,         KC_W,         KC_E,         KC_R,                  KC_T,         KC_Y,   KC_U,         KC_I,            KC_O,           KC_TAB,          SCREENSHOT_FULL,
    KC_DQT,              KC_A,         KC_S,         KC_D,         LT(_NAVIGATION, KC_F), KC_G,         KC_H,   KC_J,         KC_K,            KC_L,           KC_P,            KC_COLN,
    KC_QUOTE,            LSFT_T(KC_Z), LALT_T(KC_X), LGUI_T(KC_C), LCTL_T(KC_V),          KC_B,         KC_N,   RCTL_T(KC_M), RGUI_T(KC_COMM), RALT_T(KC_DOT), RSFT_T(KC_SLSH), KC_PIPE,
    KC_PAST,             KC_MINS,      KC_PPLS,      KC_PEQL,                                                   KC_GRV,       KC_SCLN,         KC_EXLM,        KC_BSLS,

                                                                              WINDOWS, SNIPPETS,        KC_NO, RAYCAST, // put something here
                                                                                          C_HIS,        KC_NO,
                                                          KC_BSPC, LT(_SYMBOLS, KC_F4),   LSFT(KC_SPC),        KC_NO, LT(_NUMPAD, KC_F4), KC_SPC // haven't been using enter nor esc on this row
  ),
  [_NUMPAD] = LAYOUT_pretty(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_BSPC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_SPC,                                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_5,     KC_6,     KC_7,     KC_8,     KC_TRNS,                                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
              KC_PAST,  KC_PMNS,  KC_PPLS,  KC_PEQL,                                                        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                                                                KC_NO, KC_NO,   KC_NO, KC_NO,
                                                                       KC_NO,   KC_TRNS,
                                                           KC_0, KC_9, KC_NO,   KC_NO, KC_TRNS, KC_SPC
  ),
  [_SYMBOLS] = LAYOUT_pretty(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                KC_TRNS, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                                KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                         KC_TRNS,     KC_TRNS,
                                       KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_NAVIGATION] = LAYOUT_pretty(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,           KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,           KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,           KC_LEFT, KC_DOWN,  KC_UP,     KC_RIGHT, LAST_APP, KC_NO,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,           KC_TRNS, KC_TAB,   S(KC_TAB), KC_TRNS,  KC_TRNS,  KC_TRNS,
              KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                              KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,

                                                KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                         KC_TRNS,     KC_TRNS,
                                       KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_LEAGUE] = LAYOUT_pretty(
    KC_BRID,             KC_BRIU, KC_F1,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   QK_COMBO_TOGGLE,  TG(_LEAGUE),    KC_MPRV, KC_MNXT, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, TG(_LEAGUE), QK_BOOT,

    QK_LEAD,             KC_1,         KC_2,         KC_3,         KC_4,                  KC_5,         KC_6,   KC_7,         KC_8,            KC_9,           KC_0,            DICTATION,
    QK_CAPS_WORD_TOGGLE, KC_Q,         KC_W,         KC_E,         KC_R,                  KC_T,         KC_Y,   KC_U,         KC_I,            KC_O,           KC_TAB,          SCREENSHOT_FULL,
    KC_DQT,              KC_A,         KC_S,         KC_D,          KC_F, KC_G,         KC_H,   KC_J,         KC_K,            KC_L,           KC_P,            KC_COLN,
    KC_QUOTE,            LSFT_T(KC_Z), KC_X, KC_C, KC_V,          KC_B,         KC_N,   KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), KC_PIPE,
    KC_PAST,             KC_MINS,      KC_PPLS,      KC_PEQL,                                                   KC_GRV,       KC_SCLN,         KC_EXLM,        KC_BSLS,

                                                                              WINDOWS, SNIPPETS,        KC_NO, RAYCAST, // put something here
                                                                                          C_HIS,        KC_NO,
                                                          KC_BSPC, LALT(KC_BSPC),   KC_NO,        KC_NO, LT(_NUMPAD, KC_F4), KC_SPC // haven't been using enter nor esc on this row
  ),
};

// LEAGUE ideas
// - ctrl+a, ctrl+c in one key
// - ctrl+v in one key
// - change focus character from space to backspace

// Override Definitions
const key_override_t left_word_override     = ko_make_basic(MOD_MASK_ALT, KC_H, PREV_WORD);
const key_override_t right_word_override    = ko_make_basic(MOD_MASK_ALT, KC_L, NEXT_WORD);
const key_override_t del_last_word_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, DEL_LAST_WORD);
const key_override_t shift_space_override   = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_UNDS);
const key_override_t alt_space_override     = ko_make_basic(MOD_MASK_ALT, KC_SPC, KC_PMNS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &left_word_override,
    &right_word_override,
    &del_last_word_override,
    &shift_space_override,
    &alt_space_override,
    NULL
};

// Combo Definitions
const uint16_t PROGMEM enter_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM space_combo[] = {KC_D, LT(_NAVIGATION, KC_F), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(enter_combo, KC_ENT),
    COMBO(esc_combo, KC_ESC),
    COMBO(space_combo, KC_SPC),
};



// Macro Definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case KC_ESC:
        if (record->event.pressed) {
            register_code(KC_ESC);
        } else {
            unregister_code(KC_ESC);
            if (layer_state_is(_NUMPAD)) {
                layer_off(_NUMPAD);
            }
            caps_word_off();
        }
        return false;

    case KC_J:
        if (record->event.pressed) {
            if ((get_mods() & MOD_BIT(KC_LALT)) && !(get_mods() & MOD_BIT(KC_LSFT)) && !(get_mods() & MOD_BIT(KC_LGUI)) && !(get_mods() & MOD_BIT(KC_LCTL))) {
                unregister_mods(MOD_BIT(KC_LALT));
                tap_code(KC_SCLN);
                add_mods(MOD_BIT(KC_LALT));
                return false;
            }
        } else {
            unregister_code(KC_J);
            if (layer_state_is(_NUMPAD)) {
                layer_off(_NUMPAD);
            }
        }
        return true;

    case KC_K:
        if (record->event.pressed) {
            if ((get_mods() & MOD_BIT(KC_LALT)) && !(get_mods() & MOD_BIT(KC_LSFT)) && !(get_mods() & MOD_BIT(KC_LGUI)) && !(get_mods() & MOD_BIT(KC_LCTL))) {
                unregister_mods(MOD_BIT(KC_LALT));
                tap_code16(KC_COLN);
                add_mods(MOD_BIT(KC_LALT));
                return false;
            }
        } else {
            unregister_code(KC_K);
            if (layer_state_is(_NUMPAD)) {
                layer_off(_NUMPAD);
            }
        }
        return true;

    case KC_O:
        if (record->event.pressed) {
            if (get_mods() & MOD_BIT(KC_RCTL)) {
                unregister_mods(MOD_BIT(KC_RCTL));
                tap_code(KC_M);
                tap_code(KC_O);
                add_mods(MOD_BIT(KC_RCTL));
                return false;
            } else if ((get_mods() & MOD_BIT(KC_LALT)) && !(get_mods() & MOD_BIT(KC_LSFT)) && !(get_mods() & MOD_BIT(KC_LGUI)) && !(get_mods() & MOD_BIT(KC_LCTL))) {
                unregister_mods(MOD_BIT(KC_LALT));
                tap_code16(KC_LBRC);
                tap_code16(KC_RBRC);
                tap_code(KC_LEFT);
                add_mods(MOD_BIT(KC_LALT));
                return false;
            }
        }
        return true;

    case KC_I:
        if (record->event.pressed) {
            if (get_mods() & MOD_BIT(KC_RCTL)) {
                unregister_mods(MOD_BIT(KC_RCTL));
                tap_code(KC_M);
                tap_code(KC_I);
                add_mods(MOD_BIT(KC_RCTL));
                return false;
            } else if ((get_mods() & MOD_BIT(KC_LALT)) && !(get_mods() & MOD_BIT(KC_LSFT)) && !(get_mods() & MOD_BIT(KC_LGUI)) && !(get_mods() & MOD_BIT(KC_LCTL))) {
                unregister_mods(MOD_BIT(KC_LALT));
                tap_code16(KC_LCBR);
                tap_code16(KC_RCBR);
                tap_code(KC_LEFT);
                add_mods(MOD_BIT(KC_LALT));
                return false;
            }
        }
        return true;

    case KC_U:
        if (record->event.pressed) {
            if ((get_mods() & MOD_BIT(KC_LALT)) && !(get_mods() & MOD_BIT(KC_LSFT)) && !(get_mods() & MOD_BIT(KC_LGUI)) && !(get_mods() & MOD_BIT(KC_LCTL))) {
                unregister_mods(MOD_BIT(KC_LALT));
                tap_code16(KC_LPRN);
                tap_code16(KC_RPRN);
                tap_code(KC_LEFT);
                add_mods(MOD_BIT(KC_LALT));
                return false;
            }
        }
        return true;

    case KC_GRV:
        if (record->event.pressed) {
            if ((get_mods() & MOD_BIT(KC_LALT)) && !(get_mods() & MOD_BIT(KC_LSFT)) && !(get_mods() & MOD_BIT(KC_LGUI)) && !(get_mods() & MOD_BIT(KC_LCTL))) {
                unregister_mods(MOD_BIT(KC_LALT));
                tap_code(KC_GRV);
                tap_code(KC_GRV);
                tap_code(KC_LEFT);
                add_mods(MOD_BIT(KC_LALT));
                return false;
            }
        }
        return true;

    case KC_DQT:
        if (record->event.pressed) {
            if ((get_mods() & MOD_BIT(KC_RALT)) && !(get_mods() & MOD_BIT(KC_RSFT)) && !(get_mods() & MOD_BIT(KC_RGUI)) && !(get_mods() & MOD_BIT(KC_RCTL))) {
                unregister_mods(MOD_BIT(KC_RALT));
                tap_code16(KC_DQT);
                tap_code16(KC_DQT);
                tap_code(KC_LEFT);
                add_mods(MOD_BIT(KC_RALT));
                return false;
            }
        }
        return true;

    case KC_QUOTE:
        if (record->event.pressed) {
            if ((get_mods() & MOD_BIT(KC_RALT)) && !(get_mods() & MOD_BIT(KC_RSFT)) && !(get_mods() & MOD_BIT(KC_RGUI)) && !(get_mods() & MOD_BIT(KC_RCTL))) {
                unregister_mods(MOD_BIT(KC_RALT));
                tap_code(KC_QUOTE);
                tap_code(KC_QUOTE);
                tap_code(KC_LEFT);
                add_mods(MOD_BIT(KC_RALT));
                return false;
            }
        }
        return true;

        // Handle same side row mod misfires
        // This will do most of the grunt work with the keycodes.
    case KC_S:
        if (record->event.pressed && record->tap.count > 0) {
            if (get_mods() & MOD_BIT(KC_LGUI)) {
                unregister_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_C);
                tap_code(KC_S);
                add_mods(MOD_BIT(KC_LGUI));
                return false;
            }
        }
        return true;

    case KC_E:
        if (record->event.pressed) {
            if (get_mods() & MOD_BIT(KC_LCTL)) {
                unregister_mods(MOD_BIT(KC_LCTL));
                tap_code(KC_V);
                tap_code(KC_E);
                add_mods(MOD_BIT(KC_LCTL));
                return false;
            }
        }
        return true;

    case KC_W:
        if (record->event.pressed) {
            if (get_mods() & MOD_BIT(KC_LGUI)) {
                unregister_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_C);
                tap_code(KC_W);
                add_mods(MOD_BIT(KC_LGUI));
                return false;
            }
        }
        return true;

    case KC_R:
        if (record->event.pressed) {
            if (get_mods() & MOD_BIT(KC_LGUI)) {
                unregister_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_C);
                tap_code(KC_R);
                add_mods(MOD_BIT(KC_LGUI));
                return false;
            }
        }
        return true;

    case KC_A:
        if (record->event.pressed) {
            if (get_mods() & MOD_BIT(KC_LGUI)) {
                unregister_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_C);
                tap_code(KC_A);
                add_mods(MOD_BIT(KC_LGUI));
                return false;
            }
            if (get_mods() & MOD_BIT(KC_LCTL)) {
                unregister_mods(MOD_BIT(KC_LCTL));
                tap_code(KC_V);
                tap_code(KC_A);
                add_mods(MOD_BIT(KC_LCTL));
                return false;
            }

        }
        return true;

  }
  return true;
}

// Configure which keys are "word breaking"

// You can define the caps_word_press_user(uint16_t keycode) callback to configure which keys should be shifted and which keys are considered "word breaking" and stop Caps Word.
//
// The callback is called on every key press while Caps Word is active. When the key should be shifted (that is, a letter key),
// the callback should call add_weak_mods(MOD_BIT(KC_LSFT)) to shift the key. Returning true continues the current "word,"
// while returning false is "word breaking" and deactivates Caps Word. The default callback is
//
 bool caps_word_press_user(uint16_t keycode) {
     switch (keycode) {
         // Keycodes that continue Caps Word, with shift applied.
         case KC_A ... KC_Z:
         case KC_MINS:
             add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
             return true;
         // Keycodes that continue Caps Word, without shifting.
         case KC_1 ... KC_0:
         case KC_BSPC:
         case KC_UNDS:
             return true;
         default:
             return false;  // Deactivate Caps Word.
     }
 }
