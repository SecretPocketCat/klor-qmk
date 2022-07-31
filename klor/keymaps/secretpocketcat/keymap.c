#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "klor.h"

enum klor_layers
{
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes
{
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  ADJUST,
  OS_SWAP,
};

// Mods
// Left
#define GUI_A MT(MOD_LGUI, KC_A)
#define ALT_R MT(MOD_LALT, KC_R)
#define CTL_S MT(MOD_LCTL, KC_S)
#define SHT_T MT(MOD_LSFT, KC_T)

// Right
#define SHT_N MT(MOD_RSFT, KC_N)
#define CTL_E MT(MOD_LCTL, KC_E)
#define ALT_I MT(MOD_LALT, KC_I)
#define GUI_O MT(MOD_LGUI, KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_polydactyl(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_DEL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, LOWER, KC_SPC, KC_LALT, KC_LGUI, KC_ENT, RAISE, KC_BSPC),

    [_COLEMAK] = LAYOUT_polydactyl(
        KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN,
        KC_TAB, GUI_A, ALT_R, CTL_S, SHT_T, KC_D, KC_H, SHT_N, CTL_E, ALT_I, GUI_O, KC_QUOT,
        KC_Q, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LSFT, KC_MPLY, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
        KC_DEL, LOWER, KC_SPC, KC_ESC, KC_LGUI, KC_ENT, RAISE, KC_BSPC),

    [_LOWER] = LAYOUT_polydactyl(
        KC_CAPS, KC_NLCK, KC_UP, KC_EQL, KC_LCBR, KC_RCBR, KC_P7, KC_P8, KC_P9, KC_PPLS,
        KC_ESC, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_RBRC, KC_P4, KC_P5, KC_P6, KC_MINS, KC_DQT,
        XXXXXXX, KC_END, KC_PGUP, C(KC_S), KC_PGDN, KC_LPRN, KC_MUTE, KC_MPLY, KC_RPRN, KC_P1, KC_P2, KC_P3, KC_PAST, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P0),

    [_RAISE] = LAYOUT_polydactyl(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, RALT(KC_3), KC_BSLS,
        KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NUBS, KC_PSCR,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS,
        _______, _______, _______, _______, _______, _______, _______, _______),

    [_ADJUST] = LAYOUT_polydactyl(
        AU_TOG, HPT_TOG, RGB_HUI, RGB_MOD, XXXXXXX, XXXXXXX, KC_F7, KC_F8, KC_F9, KC_F14,
        QK_BOOT, DEBUG, QWERTY, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, KC_F4, KC_F5, KC_F6, KC_F12, KC_F13,
        XXXXXXX, OS_SWAP, COLEMAK, RGB_VAI, XXXXXXX, XXXXXXX, KC_MUTE, KC_MPLY, XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F10, KC_F11,
        _______, _______, _______, _______, _______, _______, _______, _______)};

void keyboard_post_init_user(void)
{
}

#ifdef OLED_ENABLE

char layer_state_str[24];
char o_text[24] = "";
int dmacro_num = 0;

// OLED graphics
void render_os_lock_status(void)
{
  static const char PROGMEM sep_v[] = {0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0};
  static const char PROGMEM sep_h1[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
  static const char PROGMEM sep_h2[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
  static const char PROGMEM face_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xE1, 0};
  static const char PROGMEM face_2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xE1, 0};
  static const char PROGMEM os_m_1[] = {0x95, 0x96, 0};
  static const char PROGMEM os_m_2[] = {0xB5, 0xB6, 0};
  static const char PROGMEM os_w_1[] = {0x97, 0x98, 0};
  static const char PROGMEM os_w_2[] = {0xB7, 0xB8, 0};
  static const char PROGMEM s_lock[] = {0x8F, 0x90, 0};
  static const char PROGMEM n_lock[] = {0x91, 0x92, 0};
  static const char PROGMEM c_lock[] = {0x93, 0x94, 0};
  static const char PROGMEM b_lock[] = {0xE1, 0xE1, 0};

  // os mode status ────────────────────────────────────────┐

  oled_write_ln_P(sep_v, false);

  if (keymap_config.swap_lctl_lgui)
  {
    oled_write_P(os_m_1, false); // ──── MAC
  }
  else
  {
    oled_write_P(os_w_1, false); // ──── WIN
  }

  oled_write_P(sep_h1, false);
  oled_write_P(face_1, false);

  if (keymap_config.swap_lctl_lgui)
  {
    oled_write_P(os_m_2, false); // ──── MAC
  }
  else
  {
    oled_write_P(os_w_2, false); // ──── WIN
  }

  oled_write_P(sep_h1, false);
  oled_write_P(face_2, false);
  oled_write_ln_P(sep_v, false);

  // lock key layer status ─────────────────────────────────┐

  led_t led_usb_state = host_keyboard_led_state();

  if (led_usb_state.num_lock)
  {
    oled_write_P(n_lock, false); // ──── NUMLOCK
  }
  else
  {
    oled_write_P(b_lock, false);
  }
  if (led_usb_state.caps_lock)
  {
    oled_write_P(c_lock, false); // ─── CAPSLOCK
  }
  else
  {
    oled_write_P(b_lock, false);
  }
  if (led_usb_state.scroll_lock)
  { // ─ SCROLLLOCK
    oled_write_P(s_lock, false);
  }
  else
  {
    oled_write_P(b_lock, false);
  }

  // hardware feature status ──────────────────────────────┐

  oled_write_P(sep_h2, false);
}

// layer status ──────────────────────────────────────────┐

int layerstate = 0;

layer_state_t layer_state_set_kb(layer_state_t state)
{
  switch (get_highest_layer(layer_state | default_layer_state))
  {
  case 0:
    strcpy(layer_state_str, "BASE COLEMAK");
    break;
  case 1:
    strcpy(layer_state_str, "BASE QWERTY");
    break;
  case 2:
    strcpy(layer_state_str, "LOWER");
    break;
  case 3:
    strcpy(layer_state_str, "RAISE");
    break;
  case 4:
    strcpy(layer_state_str, "ADJUST");
    break;
  default:
    strcpy(layer_state_str, "XXXXXX");
  }
  if (dmacro_num < 1)
  {
    strcpy(o_text, layer_state_str);
  }
  // return state;
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// OLED rotation
oled_rotation_t oled_init_kb(oled_rotation_t rotation)
{
  return OLED_ROTATION_180;
}

// Write to OLED
bool oled_task_kb(void)
{
  if (!oled_task_user())
  {
    return false;
  }
  if (is_keyboard_master())
  { // ────────────────────────── PRIMARY SIDE

    // layer status ──────────────────────────────────────────────────┐
    oled_write_ln(o_text, false);
    render_os_lock_status();
  }
  else
  {
    // Slave side
    // todo: ???
    // oled_write_raw_P(klor_face, sizeof(klor_face));
  }
  return false;
}
#endif // OLED_ENABLE

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case SHT_T:
    return TAPPING_TERM - 150;
  case SHT_N:
    return TAPPING_TERM - 150;
  default:
    return TAPPING_TERM;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {

  case OS_SWAP:
    if (record->event.pressed)
    {
      if (!keymap_config.swap_lctl_lgui)
      {
        keymap_config.swap_lctl_lgui = true; // ─── MAC
      }
      else
      {
        keymap_config.swap_lctl_lgui = false; // ─── WIN
      }

      eeconfig_update_keymap(keymap_config.raw);
      clear_keyboard(); // ──── clear to prevent stuck keys
      return false;
    }

  // Layer
  case COLEMAK:
    if (record->event.pressed)
    {
      set_single_persistent_default_layer(_COLEMAK);
    }
    return false;
  case QWERTY:
    if (record->event.pressed)
    {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
  case LOWER:
    if (record->event.pressed)
    {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    else
    {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
  case RAISE:
    if (record->event.pressed)
    {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    else
    {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
  case ADJUST:
    if (record->event.pressed)
    {
      layer_on(_ADJUST);
    }
    else
    {
      layer_off(_ADJUST);
    }
    return false;
  }

  return true;
}

#ifdef ENCODER_ENABLE

// ┌───────────────────────────────────────────────────────────┐
// │ e n c o d e r  L                                          │
// └───────────────────────────────────────────────────────────┘

bool encoder_update_user(uint8_t index, bool clockwise)
{
  if (index == 0)
  {

    if (IS_LAYER_ON(_RAISE))
    {
      if (clockwise)
      {
        tap_code(KC_WH_R);
      }
      else
      {
        tap_code(KC_WH_L);
      }
    }
    else
    {
      if (clockwise)
      {
        tap_code(KC_VOLU);
      }
      else
      {
        tap_code(KC_VOLD);
      }
    }

    // ┌───────────────────────────────────────────────────────────┐
    // │ e n c o d e r  R                                          │
    // └───────────────────────────────────────────────────────────┘
  }
  else if (index == 1)
  {
    if (IS_LAYER_ON(_LOWER))
    {
      if (clockwise)
      {
        tap_code(KC_MNXT);
      }
      else
      {
        tap_code(KC_MPRV);
      }
    }
    else if (IS_LAYER_ON(_RAISE))
    {
      if (clockwise)
      {
        tap_code(KC_WH_D);
      }
      else
      {
        tap_code(KC_WH_U);
      }
    }
    else
    {
      if (clockwise)
      {
        tap_code(KC_VOLU);
      }
      else
      {
        tap_code(KC_VOLD);
      }
    }
  }
  return true;
}

#endif // ENCODER_ENABLE
