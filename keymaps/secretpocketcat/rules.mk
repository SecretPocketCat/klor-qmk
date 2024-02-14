# Bootloader selection
BOOTLOADER = caterina

OLED_ENABLE = yes
OLED_DRIVER_ENABLE = yes

ENCODER_ENABLE = no

EXTRAKEY_ENABLE = yes
AUDIO_ENABLE = no
MUSIC_ENABLE = no
MOUSEKEY_ENABLE = yes

DYNAMIC_MACRO_ENABLE = no
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no

#HAPTIC FEEBACK
HAPTIC_ENABLE = no

#PER KEY RGB
RGB_MATRIX_ENABLE = no

UNICODEMAP_ENABLE = yes
CAPS_WORD_ENABLE = yes

# Mouse
MOUSEKEY_ENABLE = no

# Space cadet
SPACE_CADET_ENABLE = yes
COMMAND_ENABLE = no

#Autoshift
AUTO_SHIFT_ENABLE = no

#HID/Virtual Serial
CONSOLE_ENABLE = yes
RAW_ENABLE = no
VIRTSER_ENABLE = no

# OS detection
OS_DETECTION_ENABLE = yes

#Extras
SRC += features/layer_lock.c
