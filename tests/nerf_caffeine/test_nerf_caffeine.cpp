// SPDX-License-Identifier: GPL-2.0-or-later
#include "test_common.hpp"
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

extern "C" {
#include "../../users/nerf_caffeine/nerf_caffeine.h"
}

using testing::_;
using testing::AnyNumber;

class NerfCaffeine : public TestFixture {
   protected:
    using Press = std::pair<uint8_t, uint8_t>; // Host modifier mask and keycode.
    std::vector<Press> presses;
    report_keyboard_t previous = {};

    // Small test matrix exercising the real userspace through QMK's event loop.
    const uint16_t base[2][10] = {
        {NC_SYM_F4, NC_SYM_F4, NC_NUM_HOLD, KC_SPC, NC_RAYCAST, KC_K, KC_L, KC_S, KC_D, KC_Q},
        {NC_GUI_C, NC_CTL_V, NC_CTL_M, KC_A, KC_E, KC_I, KC_O, KC_LALT, KC_LSFT, QK_CAPS_WORD_TOGGLE},
    };

    KeymapKey key(uint8_t col, uint8_t row = 0) {
        return KeymapKey(NC_BASE, col, row, base[row][col]);
    }

    void SetUp() override {
        caps_word_off();
        key_override_on();
        for (uint8_t layer = NC_BASE; layer <= NC_RESET; ++layer) {
            for (uint8_t row = 0; row < 2; ++row) {
                for (uint8_t col = 0; col < 10; ++col) {
                    uint16_t code = layer == NC_BASE ? base[row][col] : KC_TRNS;
                    if (layer == NC_NUM && row == 0) {
                        if (col == 1) code = KC_0;
                        if (col == 4) code = KC_ENT;
                        if (col == 5) code = KC_5;
                        if (col == 6) code = KC_6;
                    }
                    if (layer == NC_SYM && row == 0) {
                        if (col == 5) code = KC_RCBR;
                        if (col == 6) code = KC_DLR;
                        if (col == 7) code = KC_GRV;
                        if (col == 8) code = KC_UNDS;
                    }
                    add_key(KeymapKey(layer, col, row, code));
                }
            }
        }
    }

    void watch(TestDriver &driver) {
        EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber()).WillRepeatedly([this](report_keyboard_t &report) {
            for (uint8_t code : report.keys) {
                if (code && std::find(std::begin(previous.keys), std::end(previous.keys), code) == std::end(previous.keys)) {
                    presses.emplace_back(report.mods, code);
                }
            }
            previous = report;
        });
    }

    void hold(KeymapKey k) {
        k.press();
        // Allow for the matrix scan and QMK's nonzero event timestamp rounding.
        idle_for(TAPPING_TERM + 10);
    }

    void release(KeymapKey k) {
        k.release();
        idle_for(TAPPING_TERM + 1);
    }
};

TEST_F(NerfCaffeine, BothThumbsTapF4) {
    TestDriver driver;
    watch(driver);
    tap_key(key(0));
    tap_key(key(1));
    EXPECT_EQ(presses, (std::vector<Press>{{0, KC_F4}, {0, KC_F4}}));
    EXPECT_FALSE(layer_state_is(NC_SYM));
}

TEST_F(NerfCaffeine, SymbolsSurvivesEitherThumbReleaseOrder) {
    TestDriver driver;
    watch(driver);
    for (uint8_t first : {0, 1}) {
        hold(key(0));
        EXPECT_TRUE(layer_state_is(NC_SYM));
        hold(key(1));
        EXPECT_TRUE(layer_state_is(NC_SYM));
        release(key(first));
        EXPECT_TRUE(layer_state_is(NC_SYM));
        release(key(1 - first));
        EXPECT_FALSE(layer_state_is(NC_SYM));
    }
    EXPECT_TRUE(presses.empty());
}

TEST_F(NerfCaffeine, NumbersThumbsAndResetLayer) {
    TestDriver driver;
    watch(driver);
    hold(key(2));
    tap_key(key(3)); // Space stays Space.
    hold(key(1));   // Right middle thumb is plain 0, even when held.
    EXPECT_FALSE(layer_state_is(NC_SYM));
    release(key(1));
    tap_key(key(4)); // Raycast position becomes Enter.
    EXPECT_EQ(presses, (std::vector<Press>{{0, KC_SPC}, {0, KC_0}, {0, KC_ENT}}));
    hold(key(0));
    EXPECT_TRUE(layer_state_is(NC_RESET));
    release(key(2));
    EXPECT_FALSE(layer_state_is(NC_RESET));
    EXPECT_TRUE(layer_state_is(NC_SYM));
    release(key(0));
    EXPECT_FALSE(layer_state_is(NC_SYM));
}

TEST_F(NerfCaffeine, CombosUseBasePositionsOnEveryTypingLayer) {
    TestDriver driver;
    watch(driver);
    for (uint8_t layer : {NC_BASE, NC_NAV, NC_SYM, NC_NUM}) {
        SCOPED_TRACE(layer);
        layer_move(layer);
        presses.clear();
        tap_combo({key(5), key(6)});
        tap_combo({key(7), key(8)});
        idle_for(COMBO_TERM + 1);
        EXPECT_EQ(presses, (std::vector<Press>{{0, KC_ENT}, {0, KC_ESC}}));
        EXPECT_TRUE(layer_state_is(layer)); // Escape must not cancel Numbers.
    }
    layer_clear();
}

TEST_F(NerfCaffeine, SpaceOverridesSendUnderscoreAndForwardWordDelete) {
    TestDriver driver;
    watch(driver);
    hold(key(8, 1)); // Shift.
    tap_key(key(3));
    release(key(8, 1));
    hold(key(7, 1)); // Option.
    tap_key(key(3));
    release(key(7, 1));
    EXPECT_EQ(presses, (std::vector<Press>{{MOD_BIT(KC_LSFT), KC_MINS}, {MOD_BIT(KC_LALT), KC_DEL}}));
}

TEST_F(NerfCaffeine, SameSideAccidentalHoldsRecoverLetterPairs) {
    TestDriver driver;
    watch(driver);
    hold(key(0, 1)); // C becomes left Command.
    tap_key(key(3, 1)); // A -> ca.
    release(key(0, 1));
    hold(key(1, 1)); // V becomes left Control.
    tap_key(key(4, 1)); // E -> ve.
    release(key(1, 1));
    hold(key(2, 1)); // M becomes right Control.
    tap_key(key(5, 1)); // I -> mi.
    release(key(2, 1));
    EXPECT_EQ(presses, (std::vector<Press>{{0, KC_C}, {0, KC_A}, {0, KC_V}, {0, KC_E}, {0, KC_M}, {0, KC_I}}));
    EXPECT_EQ(get_mods(), 0);
}

TEST_F(NerfCaffeine, CapsWordEndsNormallyOnEscape) {
    TestDriver driver;
    watch(driver);
    tap_key(key(9, 1));
    EXPECT_TRUE(is_caps_word_on());
    tap_key(key(3, 1));
    tap_combo({key(7), key(8)});
    idle_for(COMBO_TERM + 1);
    EXPECT_FALSE(is_caps_word_on());
    EXPECT_EQ(presses, (std::vector<Press>{{MOD_BIT(KC_LSFT), KC_A}, {0, KC_ESC}}));
}
