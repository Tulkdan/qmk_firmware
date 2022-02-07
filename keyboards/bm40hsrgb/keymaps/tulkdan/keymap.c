/* Copyright 2020 tominabox1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifdef RAW_ENABLE
#include "raw_hid.h"
#endif
#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations
enum {
    TD_LSFT_CAPS,
    TD_COPY_PASTE,
};

// Tar Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for left shift, twice for caps lock
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    // Tap once for Copy, twice for Paste
    [TD_COPY_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_COPY, KC_PASTE),
};
#endif

void rgb_matrix_indicators_user(void) {
    // Set the led to be on specified color
    // rgb_matrix_set_color(index, red, green, blue);

    if (IS_LAYER_ON(_ADJUST)) {
        rgb_matrix_set_color(1, 200, 0, 0);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,--------------------------------------------------------------------------------------------.
 * | Esc       |  Q  |     W      |  E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |-----------+-----+------------+-----+------+------+------+------+------+------+------+------|
 * | Tab       |  A  |     S      |  D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |-----------+-----+------------+-----+------+------+------+------+------+------+------+------|
 * | Shift/Caps|  Z  |     X      |  C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  "   |
 * |-----------+-----+------------+-----+------+------+------+------+------+------+------+------|
 * | Ctrl      | GUI | Copy/Paste | Alt |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_mit(
    KC_ESC,           KC_Q,    KC_W,              KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,           KC_A,    KC_S,              KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    TD(TD_LSFT_CAPS), KC_Z,    KC_X,              KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
    KC_LCTL,          KC_LGUI, TD(TD_COPY_PASTE), KC_LALT, LOWER,      KC_SPC,        RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,------------------------------------------------------------------------------------.
 * |  ~  |  &  |  *  |  (  |     |     |     |            |   (   |   )   | Print |     |
 * |-----+-----+-----+-----+-----+-----+-----+------------+-------+-------+-------+-----|
 * | Del |  $  |  %  |  ^  |  _  |     |     |            |   {   |   }   |       |     |
 * |-----+-----+-----+-----+-----+-----+-----+------------+-------+-------+-------+-----|
 * |     |  !  |  @  |  #  |     |     |     |C_S_T(Print)|   [   |   ]   |       |     |
 * |-----+-----+-----+-----+-----+-----+-----+------------+-------+-------+-------+-----|
 * |     |     |  |  |     |     |           |   ADJUST   |  Home | Pg Dn | Pg Up | End |
 * `------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_mit(
    KC_TILD, KC_AMPR, KC_ASTR, KC_LPRN, _______, _______, _______,    _______    , KC_LPRN, KC_RPRN, KC_PSCR, _______,
     KC_DEL, KC_DLR , KC_PERC, KC_CIRC, KC_UNDS, _______, _______,    _______    , KC_LCBR, KC_RCBR, _______, _______,
    _______, KC_EXLM, KC_AT  , KC_HASH, _______, _______, _______, C_S_T(KC_PSCR), KC_LBRC, KC_RBRC, _______, _______,
    _______, _______, KC_PIPE, _______, _______,     _______     ,    _______    , KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,------------------------------------------------------------------------------.
 * |  `  |  7  |  8  |  9  |   *   |     |     |  F1  | F2   |  F3  |  F4  |      |
 * |-----+-----+-----+-----+-------+-----+-----+------+------+------+------+------|
 * | Del |  4  |  5  |  6  |   -   |  =  |     |  F5  | F6   |  F7  |  F8  |      |
 * |-----+-----+-----+-----+-------+-----+-----+------+------+------+------+------|
 * |     |  1  |  2  |  3  |   +   |  \  |     |  F9  | F10  | F11  |  F12 |      |
 * |-----+-----+-----+-----+-------+-----+-----+------+------+------+------+------|
 * |     |     |  0  |     |ADJUST |           |      | Next | Vol- | Vol+ | Play |
 * `------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_mit(
     KC_GRV,   KC_7 , KC_8,   KC_9 , KC_ASTR, _______, _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______,
     KC_DEL,   KC_4 , KC_5,   KC_6 , KC_MINS, KC_EQL , _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,
    _______,   KC_1 , KC_2,   KC_3 , KC_PLUS, KC_NUHS, _______,  KC_F9 , KC_F10 , KC_F11 , KC_F12 , _______,
      RESET, _______, KC_0, _______, _______,     _______     , _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
    rgb_matrix_set_color_all(200, 0, 0);

    raw_hid_send(data, length);
}
#endif
