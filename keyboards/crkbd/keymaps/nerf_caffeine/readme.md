# nerf_caffeine — 36-key Corne

A macOS/US-layout keymap adapted from the working Kinesis `absoluteunit1`
keymap. Hardware target: `crkbd/rev1`, Pro Micro / ATmega32U4, USB on the left.
The six-column Corne's outer columns are unused. Shared behavior lives in
`users/nerf_caffeine`, which QMK includes automatically by keymap name.

## Base

```text
 Q   W   E   R   T          Y   U   I   O   Tab
 A   S   D   F   G          H   J   K   L    P
 Z   X   C   V   B          N   M   ,   .    /

       Num  F4/Sym  Bspc    Space  F4/Sym  Raycast
```

Thumb positions are shown left to right. Backspace and Space are nearest the
center. Numbers and Raycast are outermost. Raycast sends Command+Space.

- Hold F for Navigation; tap it for F.
- Hold either middle thumb for Symbols; tap it for the F4 tmux prefix.
- Holding both Symbols thumbs works: releasing either one leaves the other active.
- Numbers is a dedicated hold, with no tap action.

Bottom-row modifier holds on Base:

| Key | Hold |
| --- | --- |
| Z / slash | Left / right Shift |
| X / period | Left / right Option |
| C / comma | Left / right Command |
| V / M | Left / right Control |

## Symbols

```text
 !   @   #   &   %          ;   (   )   ?   CapsWord
 "   `   _   ~   *          ^   {   }   $      :
 '   -   +   =   \          <   [   ]   >      |
```

These are plain punctuation keys, including the bottom row: there are no
modifier holds on this layer. Thumbs retain their underlying assignments.
Caps Word is at the base Tab position. Quotes, colon, and pipe preserve the
Kinesis's outer-edge positioning; brackets keep their previous finger positions.
Comma, period, and slash are directly available on Base.

## Numbers

Hold the left outer thumb. Left finger keys retain their underlying assignments;
the right hand becomes:

```text
 /   7   8   9   *
 -   4   5   6   +
 =   1   2   3   .

 Space    0    Enter
```

The right middle thumb is plain 0 and repeats when held. Space remains Space;
Raycast becomes Enter. Digits and operators use ordinary keycodes, so Num Lock
is not needed. The left middle thumb still taps F4 and holds Symbols.

## Navigation and shortcuts

Hold F:

- H/J/K/L: Left/Down/Up/Right.
- M/comma: Tab/Shift+Tab.
- P: Command+Tab.
- Backspace: forward Delete.

| Gesture | Result |
| --- | --- |
| Physical S+D | Escape on every typing layer |
| Physical K+L | Enter on every typing layer |
| Shift+Space | Underscore |
| Option+Space | Option+forward Delete (next word in supporting Mac applications) |
| Option+H / Option+L | Option+Left / Option+Right, for word navigation |
| Option+Backspace | Normal macOS previous-word deletion |

There is no D+F Space combo and no Shift+Backspace override. The combo window is
50 ms; this also applies to the corresponding number/symbol positions. For
example, chording the 5 and 6 positions on Numbers sends Enter.

Caps Word shifts letters and minus, and continues across digits, Backspace, and
underscore. Other word-breaking keys, including Escape, end it normally. Escape,
J, and K never forcibly turn off Numbers; releasing its thumb does.

The inherited same-side typing repairs are intentional:

| Held modifier | Following letter | Replacement |
| --- | --- | --- |
| Left Command (C) | A / W / R | ca / cw / cr |
| Left Control (V) | A / E | va / ve |
| Right Control (M) | I / O | mi / mo |
| Left Command (C) | S | cs, only with the original nonzero tap-count guard |

These inspect active modifiers, not the cause or age of a hold. Use the
opposite-hand modifier for the corresponding genuine application shortcuts.
The `cs` exception's extra guard is preserved exactly; it is not broadened to
every ordinary S keypress. Other already-held modifiers are preserved by repairs.

Tap/hold timing is 185 ms, with permissive hold and ignored mod-tap interruption.
Quick-tap timing is also 185 ms, matching the effective Kinesis configuration:
a quick tap followed by a hold of the same dual-role key can repeat its tap
action instead of selecting the hold action.

## Firmware reset and layer priority

Hold **Numbers + the left middle Symbols thumb**, then press the physical **Q**
position to enter the bootloader. Symbols may be held first or second. The right
middle thumb becomes 0 after Numbers is active, so use the left middle thumb.

Layer priority is Reset > Numbers > Symbols > Navigation > Base. Reset is derived
from Numbers+Symbols and disappears as soon as either layer is released. All
reset-layer positions other than Q are transparent. Bootmagic is also enabled;
the Corne PCB's physical reset buttons remain available.

No League layer, leader sequences, paired-delimiter macros, extra application
shortcuts, media controls, mouse keys, lighting, or OLED rendering are included.

## Build and checks

With the QMK CLI and AVR toolchain on PATH, run from the repository root:

```sh
qmk compile -kb crkbd/rev1 -km nerf_caffeine
make test:nerf_caffeine
```

The firmware output is `crkbd_rev1_nerf_caffeine.hex`. Both halves use the same
firmware; normal use connects USB to the left half.

The implementation session used the existing Homebrew AVR tools and a temporary
Python environment, without changing global QMK configuration. While that
environment exists, the equivalent local commands are:

```sh
export PATH="/private/tmp/nerf-caffeine-qmk-venv/bin:/opt/homebrew/opt/avr-gcc@8/bin:/opt/homebrew/opt/avr-binutils/bin:$PATH"
qmk compile -kb crkbd/rev1 -km nerf_caffeine
make test:nerf_caffeine
```

Automated regression tests exercise userspace through QMK's event loop. The
following checks still require the physical keyboard and target applications:

- [ ] Confirm left/right handedness, all 36 positions, Tab/P, and plain Backspace.
- [ ] Test all eight modifier holds and real shortcuts using opposite-hand modifiers.
- [ ] Test ca/cw/cr/va/ve/mi/mo repairs and document the guarded cs behavior.
- [ ] Tap each F4 in tmux; hold each for Symbols; release overlapping holds in both orders.
- [ ] Type every Symbols key, including repeated bottom-row symbols.
- [ ] Toggle Caps Word with Symbols+Tab; type letters/digits/underscore and end with Escape.
- [ ] Enter numbers/operators/decimal, hold 0 to repeat, and use Space and Enter.
- [ ] Check Enter/Escape combos on Base, Symbols, Numbers, and Navigation.
- [ ] Verify arrows, Tab/Shift+Tab, app switching, and both word-navigation directions.
- [ ] Verify underscore, forward-word deletion, Option+Backspace, and forward Delete.
- [ ] Hold/release Numbers and Symbols in either order and confirm no stuck layer.
- [ ] When ready to reflash, enter the bootloader with Numbers+Symbols+Q.
