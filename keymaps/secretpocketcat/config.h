#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define MASTER_LEFT
// #define MASTER_RIGHT

#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
// #define NO_ACTION_TAPPING
// #define NO_MUSIC_MODE

#define COMBO_COUNT 1

// Unicode
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX, UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_MACOS
#define UNICODE_CYCLE_PERSIST false

// Mouse
#define MK_COMBINED
// #define MK_KINETIC_SPEED 5

// Oneshot
#undef NO_ACTION_ONESHOT
#define ONESHOT_TIMEOUT 3000

// Console - save flash
#define USER_PRINT

// HID
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61
