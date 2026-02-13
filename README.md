# Arjun's Hackpad

Arjun's Hackpad is an 8-key macropad with a rotary encoder, OLED display, and per-key RGB lighting. It uses custom QMK firmware with advanced features like RGB mode cycling (including OFF) and a toggleable encoder with 4 different modes.

## Features

* Compact 8-key layout (2 rows × 4 columns)
* 128x32 OLED Display showing encoder mode and RGB status
* EC11 Rotary encoder with 4 switchable modes (Volume, Brightness, Media, Scroll)
* 16x SK6812 MINI-E RGB LEDs (2 per key) for vibrant underglow
* Custom QMK firmware with advanced RGB and encoder control
* Two-piece 3D printed case with 5-degree tilt

## CAD Model

![CAD Assembly](images/cad_assembly.png)

The case consists of two 3D printed parts held together with M3 hardware:
* **Top piece** - Contains 4 heatset inserts for mounting
* **Bottom piece** - Screws pass through bottom into top inserts
* Assembly uses 4x M3×16mm screws and 4x M3×5×4mm heatset inserts
* Features a 5-degree tilt for ergonomic typing

Made in OnShape.

## PCB

![PCB Layout](images/pcb_layout.png)

**PCB Specifications:**
* Dimensions: 78.72mm × 98.51mm (under 100×100mm requirement)
* 2-layer design
* Matrix wired as 2 rows × 4 columns with COL2ROW diode direction
* Seeed XIAO RP2040 microcontroller

### Schematic

![Schematic](images/schematic.png)

The design uses a standard keyboard matrix with diodes to prevent ghosting. RGB LEDs are daisy-chained on GPIO4, OLED uses I2C on GPIO6/GPIO7, and the rotary encoder connects to GPIO0/GPIO1.

## Firmware Overview

This hackpad uses **QMK firmware** with custom code for advanced features.

### Key Layout:
```
[RGB Cycle] [Enc Toggle] [Play/Pause] [Next Track]
[   Copy  ] [   Paste  ] [   Undo   ] [   Redo   ]
```

### Features:
* **RGB Cycle (Key 1)**: Cycles through 10 RGB animation modes plus OFF state
* **Encoder Toggle (Key 2)**: Switches encoder between 4 modes:
  1. Volume Up/Down
  2. Brightness Up/Down
  3. Media Next/Previous
  4. Scroll Up/Down
* **Media Controls**: Play/Pause and Next Track
* **Editing Shortcuts**: Copy, Paste, Undo, Redo
* **OLED Display**: Shows current encoder mode and RGB status in real-time

The firmware is built on QMK with custom `process_record_user()` and `encoder_update_user()` functions to enable the advanced RGB cycling and encoder mode switching.

## BOM (Bill of Materials)

Here's everything you need to build this hackpad:

* 1x Seeed XIAO RP2040 (unsoldered, through-hole)
* 8x MX-Style switches
* 8x White blank DSA keycaps
* 8x 1N4148 DO-35 Diodes (through-hole)
* 16x SK6812 MINI-E RGB LEDs
* 1x 0.91" 128x32 OLED Display (pin order: GND-VCC-SCL-SDA)
* 1x EC11 Rotary Encoder
* 4x M3×16mm screws
* 4x M3×5×4mm heatset inserts
* 1x Custom PCB (78.72mm × 98.51mm)
* 1x 3D printed case (2 parts: Top and Bottom)

## Production Files

All manufacturing files are included in the `production/` folder:
* `gerbers.zip` - PCB manufacturing files
* `firmware.hex` - Compiled QMK firmware ready to flash
* `Top.step` - 3D printable top case part
* `Bottom.step` - 3D printable bottom case part

## Assembly Instructions

1. **Print the case parts** (Top and Bottom)
2. **Install heatset inserts** into the 4 mounting holes in the top piece
3. **Solder components** to the PCB in this order:
   - Diodes (watch polarity!)
   - RGB LEDs (SK6812 MINI-E - watch orientation!)
   - OLED display
   - Rotary encoder
   - XIAO RP2040 (last)
4. **Flash firmware** to the XIAO RP2040
5. **Install switches** into the PCB
6. **Add keycaps** to switches
7. **Mount PCB** into bottom case
8. **Attach top case** using 4x M3×16mm screws through bottom into heatset inserts

## Flashing Firmware

1. Hold the BOOT button on the XIAO RP2040 while plugging in USB
2. A drive called "RPI-RP2" will appear
3. Drag and drop `firmware.hex` (or `.uf2`) onto the drive
4. The hackpad will reboot with QMK firmware loaded

Test all keys at [keyboardtester.com](https://www.keyboardtester.com/)

---

*Built for Hack Club's Hackpad project*
