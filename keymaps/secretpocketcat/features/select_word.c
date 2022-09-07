// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/select-word

#include "select_word.h"

enum { STATE_NONE, STATE_SELECTED, STATE_WORD, STATE_FIRST_LINE, STATE_LINE };

bool process_select_word_or_line(uint16_t keycode, keyrecord_t* record, uint16_t sel_word_keycode, uint16_t sel_line_keycode) {
    static uint8_t state = STATE_NONE;

    if (keycode == KC_LSFT || keycode == KC_RSFT) {
        return true;
    }

    if (record->event.pressed) {           // On key press.
        if (keycode == sel_word_keycode) { // Select word.
            register_code(KC_LCTL);
            if (state == STATE_NONE) {
                SEND_STRING(SS_TAP(X_RGHT) SS_TAP(X_LEFT));
            }
            register_code(KC_LSFT);
            register_code(KC_RGHT);
            state = STATE_WORD;
            return false;
        } else if (keycode == sel_line_keycode) { // Select line.
            const uint8_t mods = get_mods();

            if (state == STATE_NONE) {
                clear_mods();
#ifndef NO_ACTION_ONESHOT
                clear_oneshot_mods();
#endif // NO_ACTION_ONESHOT
                SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));
                set_mods(mods);
                register_code(KC_LSFT);
                state = STATE_FIRST_LINE;
            } else {
                register_code(KC_LSFT);
                register_code(KC_DOWN);
                state = STATE_LINE;
            }
            return false;
        }
    }

    // `sel_keycode` was released, or another key was pressed.
    switch (state) {
        case STATE_WORD:
            unregister_code(KC_RGHT);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            state = STATE_SELECTED;
            break;

        case STATE_FIRST_LINE:
            state = STATE_SELECTED;
            break;

        case STATE_LINE:
            unregister_code(KC_DOWN);
            unregister_code(KC_LSFT);
            state = STATE_SELECTED;
            break;

        case STATE_SELECTED:
            if (keycode == KC_ESC) {
                tap_code(KC_RGHT);
                state = STATE_NONE;
                return false;
            }
            // Fallthrough.
        default:
            state = STATE_NONE;
    }

    return true;
}