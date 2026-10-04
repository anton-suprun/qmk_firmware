SRC += users/nerf_caffeine/nerf_caffeine.c
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE = yes

# This checkout predates these Clang diagnostics in QMK's core/test helpers.
# Keep the workarounds local to this native test target, not the AVR firmware.
ifneq ($(findstring clang,$(shell $(CC_PREFIX)gcc --version 2>/dev/null)),)
    CFLAGS += -Wno-error=include-next-absolute-path -Wno-error=tautological-constant-out-of-range-compare -Wno-unused-command-line-argument
    CXXFLAGS += -Wno-c++11-narrowing
endif
