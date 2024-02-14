#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "klor.h"
#include "raw_hid.h"
#include "virtser.h"
#include "features/layer_lock.h"
#include "os_detection.h"

enum klor_layers {
    _COLEMAK,
    _QWERTY,
    _NAV,
    _NUM,
    _SYM,
    _FUN,
    _UNI,
    _WIN,
};

enum custom_keycodes {
    COLEMAK = SAFE_RANGE,
    QWERTY,
    _MT_QUESTIONMARK,
    LAYER_LOCK,
    SELECT_LINE,
};

// Left Alt because right would be AltGr
#define MT_ALT_QUESTIONMARK LALT_T(_MT_QUESTIONMARK)

enum unicode_names {
    A_ACUTE,
    A_ACUTE_UPPER,
    E_ACUTE,
    E_ACUTE_UPPER,
    E_CARON,
    E_CARON_UPPER,
    I_ACUTE,
    I_ACUTE_UPPER,
    O_ACUTE,
    O_ACUTE_UPPER,
    U_ACUTE,
    U_ACUTE_UPPER,
    U_RING,
    U_RING_UPPER,
    Y_ACUTE,
    Y_ACUTE_UPPER,
    C_CARON,
    C_CARON_UPPER,
    D_CARON,
    D_CARON_UPPER,
    N_CARON,
    N_CARON_UPPER,
    R_CARON,
    R_CARON_UPPER,
    S_CARON,
    S_CARON_UPPER,
    T_CARON,
    T_CARON_UPPER,
    Z_CARON,
    Z_CARON_UPPER,
    CURR_USD,
    CURR_EUR,
    EMJ_SMILE,
    EMJ_TEARS_OF_JOY,
    EMJ_GRIN,
    EMJ_GRIN_SWEAT,
    EMJ_SAD,
    EMJ_TEARS,
    EMJ_SMILING_HEARTS,
    EMJ_BLOW_KISS,
    EMJ_NAUSEA,
    EMJ_VOMIT,
    EMJ_THUMBS_UP,
    EMJ_SUS,
    SYM_DEGREE,
};

const uint32_t PROGMEM unicode_map[] = {
    // cs
    [A_ACUTE]       = 0x00E1,
    [A_ACUTE_UPPER] = 0x00C1,
    [E_ACUTE]       = 0x00E9,
    [E_ACUTE_UPPER] = 0x00C9,
    [E_CARON]       = 0x011B,
    [E_CARON_UPPER] = 0x011A,
    [I_ACUTE]       = 0x00ED,
    [I_ACUTE_UPPER] = 0x00CD,
    [O_ACUTE]       = 0x00F3,
    [O_ACUTE_UPPER] = 0x00D3,
    [U_ACUTE]       = 0x00FA,
    [U_ACUTE_UPPER] = 0x00DA,
    [U_RING]        = 0x016F,
    [U_RING_UPPER]  = 0x016E,
    [Y_ACUTE]       = 0x00FD,
    [Y_ACUTE_UPPER] = 0x00DD,
    [C_CARON]       = 0x010D,
    [C_CARON_UPPER] = 0x010C,
    [D_CARON]       = 0x010F,
    [D_CARON_UPPER] = 0x010E,
    [N_CARON]       = 0x0148,
    [N_CARON_UPPER] = 0x0147,
    [R_CARON]       = 0x0159,
    [R_CARON_UPPER] = 0x0158,
    [S_CARON]       = 0x0161,
    [S_CARON_UPPER] = 0x0160,
    [T_CARON]       = 0x0165,
    [T_CARON_UPPER] = 0x0164,
    [Z_CARON]       = 0x017E,
    [Z_CARON_UPPER] = 0x017D,
    // Currency
    [CURR_USD] = 0x0024,
    [CURR_EUR] = 0x20AC,
    // Emoji
    [EMJ_SMILE]          = 0x1F642,
    [EMJ_TEARS_OF_JOY]   = 0x1F602,
    [EMJ_GRIN]           = 0x1F601,
    [EMJ_GRIN_SWEAT]     = 0x1F605,
    [EMJ_SAD]            = 0x1F641,
    [EMJ_TEARS]          = 0x1F62D,
    [EMJ_SMILING_HEARTS] = 0x1F970,
    [EMJ_BLOW_KISS]      = 0x1F618,
    [EMJ_NAUSEA]         = 0x1F922,
    [EMJ_VOMIT]          = 0x1F92E,
    [EMJ_THUMBS_UP]      = 0x1F44D,
    [EMJ_SUS]            = 0x1F928,
    // Symbols
    [SYM_DEGREE] = 0x0B0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_polydactyl(
        // top L
        KC_J, KC_W, KC_F, KC_P, KC_G,
        // top R
        KC_C, KC_L, KC_U, KC_Y, KC_B,
        // mid L
        KC_Z, KC_A, KC_R, KC_S, KC_T, KC_D,
        // mid R
        KC_H, KC_N, KC_E, KC_I, KC_O, KC_K,
        // bottom L
        XXXXXXX, KC_LALT, MT(MOD_LCTL, KC_COMMA), SC_LSPO, KC_V, XXXXXXX, XXXXXXX,
        // bottom R
        XXXXXXX, XXXXXXX, KC_M, SC_RSPC, MT(MOD_LCTL, KC_DOT), MT_ALT_QUESTIONMARK, XXXXXXX,
        // thumb L
        LT(_WIN, KC_ESC), LT(_NAV, KC_SPC), LT(_UNI, KC_TAB), XXXXXXX,
        // thumb R
        XXXXXXX, LT(_FUN, KC_ENT), LT(_NUM, KC_BSPC), LT(_SYM, KC_DELETE)),

    // todo: gaming/qwerty layout
    [_QWERTY] = LAYOUT_polydactyl(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_DEL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, LT(_WIN, KC_ESC), LT(_NAV, KC_SPC), LT(_UNI, KC_TAB), XXXXXXX, XXXXXXX, LT(_FUN, KC_ENT), LT(_NUM, KC_BSPC), LT(_SYM, KC_DEL)),

    [_NAV] = LAYOUT_polydactyl(
        // top L
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // top R
        KC_APP, KC_HOME, KC_PAGE_DOWN, KC_PAGE_UP, KC_END,
        // mid L
        LAYER_LOCK, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Y),
        // mid R
        XXXXXXX /* TODO: */, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, QK_CAPS_WORD_TOGGLE,
        // bottom L
        XXXXXXX, OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), OSM(MOD_LGUI), XXXXXXX, XXXXXXX,
        // bottom R - TODO: TILING WIN MANAGMENT? MOUSE ARROWS?
        XXXXXXX, XXXXXXX, LGUI(KC_KP_5), LGUI(KC_KP_6), LGUI(KC_KP_7), KC_CAPS_LOCK, XXXXXXX,
        // thumb L
        XXXXXXX, MO(_NAV), XXXXXXX, XXXXXXX,
        // thumb R
        XXXXXXX, LSFT(KC_ENTER), RCTL(KC_BSPC), RCTL(KC_DELETE)),

    [_NUM] = LAYOUT_polydactyl(
        // top L
        KC_LEFT_ANGLE_BRACKET, KC_7, KC_8, KC_9, KC_RIGHT_ANGLE_BRACKET,
        // top R
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // mid L
        XXXXXXX, KC_0, KC_1, KC_2, KC_3, KC_EXCLAIM,
        // mid R
        XXXXXXX, KC_PLUS, KC_SLASH, KC_ASTERISK, KC_MINUS, LAYER_LOCK,
        // bottom L
        XXXXXXX, KC_LALT, MT(MOD_LCTL, KC_4), KC_5, KC_6, XXXXXXX, XXXXXXX,
        // bottom R
        XXXXXXX, XXXXXXX, KC_RGUI, KC_RSFT, KC_RCTL, KC_LALT, XXXXXXX,
        // thumb L
        KC_COMMA, KC_EQUAL, KC_DOT, XXXXXXX,
        // thumb R
        XXXXXXX, XXXXXXX, MO(_NUM), XXXXXXX),

    [_SYM] = LAYOUT_polydactyl(
        // top L
        KC_PERC, KC_CIRCUMFLEX /* ^ */, KC_HASH, XP(CURR_USD, CURR_EUR) /* $/€ */, KC_TILDE,
        // top R
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // mid L
        KC_BACKSLASH, KC_Q, KC_X, KC_LEFT_CURLY_BRACE, KC_LEFT_BRACKET, KC_PIPE,
        // mid R
        XXXXXXX, KC_COLON, KC_AMPERSAND /* & */, KC_UNDERSCORE, KC_SEMICOLON, LAYER_LOCK,
        // bottom L
        XXXXXXX, X(SYM_DEGREE), KC_AT, KC_RIGHT_CURLY_BRACE, KC_RIGHT_BRACKET, XXXXXXX, XXXXXXX,
        // bottom R
        XXXXXXX, XXXXXXX, KC_RGUI, KC_RSFT, KC_RCTL, KC_LALT, XXXXXXX,
        // thumb L
        KC_QUOTE, KC_DOUBLE_QUOTE, KC_GRAVE /* ` */, XXXXXXX,
        // thumb R
        XXXXXXX, XXXXXXX, XXXXXXX, MO(_SYM)),

    // todo: replace the mouse keys with smt useful - maybe media?
    [_FUN] = LAYOUT_polydactyl(
        // top L
        KC_F10, KC_F7, KC_F8, KC_F9, XXXXXXX,
        // top R
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // mid L
        KC_PRINT_SCREEN, KC_F11, KC_F1, KC_F2, KC_F3, KC_MS_WH_DOWN,
        // mid R
        XXXXXXX, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, LAYER_LOCK,
        // bottom L
        XXXXXXX, KC_F12, KC_F4, KC_F5, KC_F6, XXXXXXX, XXXXXXX,
        // bottom R
        XXXXXXX, XXXXXXX, KC_RGUI, KC_RSFT, KC_RCTL, KC_LALT, XXXXXXX,
        // thumb L
        KC_MS_ACCEL1, KC_MS_BTN1, KC_MS_BTN2, XXXXXXX,
        // thumb R
        XXXXXXX, MO(_FUN), XXXXXXX, XXXXXXX),

    // todo: replace smt. with the :p emoji
    [_UNI] = LAYOUT_polydactyl(
        // top L
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // top R
        XP(U_ACUTE, U_ACUTE_UPPER), XP(U_RING, U_RING_UPPER), XP(D_CARON, D_CARON_UPPER), XP(N_CARON, N_CARON_UPPER), XP(T_CARON, T_CARON_UPPER),
        // mid L
        LAYER_LOCK, XP(A_ACUTE, A_ACUTE_UPPER), XP(R_CARON, R_CARON_UPPER), XP(S_CARON, S_CARON_UPPER), XP(Z_CARON, Z_CARON_UPPER), XXXXXXX,
        // mid R
        XP(C_CARON, C_CARON_UPPER), XP(E_CARON, E_CARON_UPPER), XP(E_ACUTE, E_ACUTE_UPPER), XP(I_ACUTE, I_ACUTE_UPPER), XP(Y_ACUTE, Y_ACUTE_UPPER), XP(O_ACUTE, O_ACUTE_UPPER),
        // bottom L
        XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, KC_LGUI, XXXXXXX, XXXXXXX,
        // bottom R
        XXXXXXX, XXXXXXX, XP(EMJ_SMILING_HEARTS, EMJ_BLOW_KISS), KC_RSFT, XP(EMJ_VOMIT, EMJ_NAUSEA), XP(EMJ_THUMBS_UP, EMJ_SUS), XXXXXXX,
        // thumb L
        XXXXXXX, XXXXXXX, MO(_UNI), XXXXXXX,
        // thumb R
        XXXXXXX, XP(EMJ_SAD, EMJ_TEARS), XP(EMJ_GRIN, EMJ_GRIN_SWEAT), XP(EMJ_SMILE, EMJ_TEARS_OF_JOY)),

    [_WIN] = LAYOUT_polydactyl(
        // top L
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // top R
        XXXXXXX, LGUI(KC_F13), LGUI(KC_F14), LGUI(KC_F15), LGUI(KC_F16),
        // mid L
        XXXXXXX, LGUI(KC_KP_1), LGUI(KC_KP_2), LGUI(KC_KP_3), LGUI(KC_KP_4), XXXXXXX,
        // mid R
        // todo: use alt-tab actually
        LGUI(KC_F17), LALT(KC_TAB) /* ALT + TAB */, LGUI(KC_F18), LGUI(KC_F19), LSA(KC_TAB) /* ALT + Shift + TAB */, LGUI(KC_F20),
        // bottom L
        XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, KC_LGUI, XXXXXXX, XXXXXXX,
        // bottom R
        XXXXXXX, XXXXXXX, LGUI(KC_F21), LGUI(KC_F22), LGUI(KC_F23), LGUI(KC_F24), XXXXXXX,
        // thumb L
        MO(_WIN), XXXXXXX, XXXXXXX, XXXXXXX,
        // thumb R
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};

uint8_t mod_state;
uint8_t oneshot_mod_state;

void clear_all_mods(void) {
    clear_mods();
    clear_oneshot_mods();
}

bool process_shifted_sequence(char sequence[]) {
    clear_all_mods();
    send_string(sequence);
    return true;
}

void restore_non_shift_mods(void) {
    set_mods(mod_state);
    set_oneshot_mods(oneshot_mod_state);
    del_oneshot_mods(MOD_MASK_SHIFT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LAYER_LOCK)) {
        return false;
    }

    mod_state         = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    if (record->event.pressed) {
        // switch (keycode) {
        //     // Layer
        //     case COLEMAK:
        //         set_single_persistent_default_layer(_COLEMAK);
        //         return false;
        //     case QWERTY:
        //         set_single_persistent_default_layer(_QWERTY);
        //         return false;
        // }

        // tap overrides
        if (record->tap.count > 0) {
            // do not continue with default tap action
            // if the MT was pressed or released, but not held
            switch (keycode) {
                case MT_ALT_QUESTIONMARK:
                    tap_code16(KC_QUESTION);
                    return false;
                    // case LT_BKCSP_WORD:
                    //     SEND_STRING(SS_RCTL(SS_TAP(X_BACKSPACE)));
                    //     return false;
            }
        }

        if ((mod_state & MOD_MASK_SHIFT) || (oneshot_mod_state & MOD_MASK_SHIFT)) {
            bool processed = false;
            bool nl        = false;

            switch (keycode) {
                case SC_LSPO:
                case SC_RSPC:
                    clear_all_mods();
                    SEND_STRING("();");
                    restore_non_shift_mods();
                    return false;
                case KC_LEFT_CURLY_BRACE:
                    processed = process_shifted_sequence("{}");
                    break;
                case KC_RIGHT_CURLY_BRACE:
                    processed = nl = process_shifted_sequence("{}");
                    break;
                case KC_LEFT_BRACKET:
                    processed = process_shifted_sequence("[]");
                    break;
                case KC_RIGHT_BRACKET:
                    processed = nl = process_shifted_sequence("[]");
                    break;
                case KC_LEFT_ANGLE_BRACKET:
                    processed = process_shifted_sequence("<>");
                    break;
                case KC_QUOTE:
                    processed = process_shifted_sequence("''");
                    break;
                case KC_DOUBLE_QUOTE:
                    processed = process_shifted_sequence("\"\"");
                    break;
                case KC_GRAVE:
                    processed = process_shifted_sequence("``");
                    break;
            }

            if (processed) {
                tap_code(KC_LEFT);

                if (nl) {
                    tap_code(KC_ENTER);
                }

                restore_non_shift_mods();

                return false;
            }
        }
    }

    return true;
}

// layer status ──────────────────────────────────────────┐
layer_state_t layer_state_set_user(layer_state_t state) {
    int16_t layer = get_highest_layer(state);
    uprintf("layer_%d\n", layer);

    register_code(KC_LCTL);
    tap_code(KC_F13 + layer);
    unregister_code(KC_LCTL);

    // use OS detection (a guess based on some USB wizadry) to set unicode input mode
    // this might not work during startup hence running it on layer switch
    // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_os_detection.md
    // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_unicode.md
    int host = detected_host_os();

    if (host == 1) {
        set_unicode_input_mode(UNICODE_MODE_LINUX);
    } else {
        set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
    }

    uprintf("host=%d\n", host);

    return state;
}

// todo: update oled with caps word
void caps_word_set_user(bool active) {
    // caps_word = active;
    uprintf("capsword_%d\n", active);
    if (active) {
        tap_code16(C(KC_F21));
    } else {
        tap_code16(S(KC_F21));
    }
    // todo: disable capslock if capsword is active
}

void oneshot_mods_changed_user(uint8_t mods) {
    static bool oneshot_shift = false;
    bool        shift         = mods & MOD_MASK_SHIFT;
    if (shift != oneshot_shift) {
        if (shift) {
            tap_code16(C(KC_F22));
        } else {
            tap_code16(S(KC_F22));
        }
        println("Oneshot SHIFT");
    }
}

bool is_timed_out_tap_key(uint16_t keycode, keyrecord_t *record) {
    // thumb keys
    if (record->event.key.row == 3 || record->event.key.row == 7) {
        return true;
    }

    return false;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return is_timed_out_tap_key(keycode, record);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (is_timed_out_tap_key(keycode, record)) {
        return TAPPING_TERM * 2;
    }

    return TAPPING_TERM;
}
