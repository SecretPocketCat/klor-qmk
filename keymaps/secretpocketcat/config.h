#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define MASTER_LEFT
// #define MASTER_RIGHT

//#define TAPPING_TERM 170
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
//#define NO_ACTION_TAPPING
//#define NO_MUSIC_MODE

#define COMBO_COUNT 1

//

// Unicode
#define UNICODE_SELECTED_MODES UC_WINC

// Mouse
#define MK_COMBINED
// #define MK_KINETIC_SPEED 5

// Layer lock
#define LAYER_LOCK_IDLE_TIMEOUT 30000 // Turn off after 30 seconds.

// Oneshot
#undef NO_ACTION_ONESHOT
#define ONESHOT_TIMEOUT 3000

// Console - save flash
#define USER_PRINT
