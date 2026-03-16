# TM4C123 Embedded Project

Embedded firmware template for the Texas Instruments TM4C123GH6PM / TM4C123GXL platform using:

- GCC `arm-none-eabi`
- CMake
- CMSIS
- TivaWare driver library
- FreeRTOS

This repository is set up as a working Cortex-M4F firmware project with a linker script, startup code, FreeRTOS port, and a UART-based demo application.

## Current Firmware Behavior

The example in `src/main.c` configures:

- System clock at 80 MHz
- UART0 on `PA0/PA1` at `115200 8-N-1`
- A FreeRTOS queue for received UART characters
- A UART interrupt handler that pushes received characters into the queue
- A UART processing task that echoes received characters
- A heartbeat task that prints a periodic alive counter every 2 seconds

Expected serial output after boot is similar to:

```text
=== System Starting ===
Starting FreeRTOS scheduler...
UART Task Running!
Heartbeat Task Running!
Alive: 0
Alive: 1
...
```

Typing in the serial terminal should echo the character and print ` - received`.

## Repository Layout

```text
.
|- CMakeLists.txt
|- toolchain-arm-none-eabi.cmake
|- linker/
|  \- tm4c123.ld
|- src/
|  |- main.c
|  \- FreeRTOSConfig.h
|- CMSIS/
|- Freertos/
|- tivaware/
|- SVD/
|- TM4C123GH6PM.svd
\- Keil.TM4C_DFP.pdsc
```

## Prerequisites

Install the following tools before building:

- `cmake` 3.22 or newer
- GNU Arm Embedded Toolchain with:
  - `arm-none-eabi-gcc`
  - `arm-none-eabi-g++`
  - `arm-none-eabi-objcopy`
  - `arm-none-eabi-size`
- A build generator supported by CMake, such as `MinGW Makefiles` or `Ninja`

The toolchain file is already provided in `toolchain-arm-none-eabi.cmake`.

## Build

Example CMake configure and build flow:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

If you use Ninja instead:

```powershell
cmake -S . -B build -G Ninja
cmake --build build
```

Generated outputs include:

- `tm4c123gxl.elf`
- `tm4c123gxl.bin`
- `tm4c123gxl.hex`
- `output.map`

## Flashing and Debug

This repo includes files useful for debug tooling and device description:

- `TM4C123GH6PM.svd`
- `Keil.TM4C_DFP.pdsc`

You can flash the generated `.elf`, `.bin`, or `.hex` using the debug probe and programmer that matches your setup, such as:

- Keil / ULINK
- OpenOCD with a supported probe
- Vendor or board-specific flash tools

## Notes

- The project targets a Cortex-M4F with hardware floating point:
  - `-mcpu=cortex-m4`
  - `-mthumb`
  - `-mfloat-abi=hard`
  - `-mfpu=fpv4-sp-d16`
- FreeRTOS uses the GCC ARM CM4F port and `heap_4.c`
- The linker script is located at `linker/tm4c123.ld`

## Git Tips

To see local changes before pushing to GitHub:

```powershell
git status
git diff
git diff --staged
git fetch origin
git diff origin/main
```

## License

Review the upstream license terms for bundled third-party components such as TivaWare, CMSIS, and FreeRTOS before redistributing this project.
