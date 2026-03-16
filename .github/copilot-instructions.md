Purpose
-------
This file contains concise, project-specific guidance for AI coding agents working on this repo. Focus on the TM4C123 embedded firmware layout, build entry points, vendor library usage, and safe editing spots.

- **Project type:** Embedded C firmware targeting the TI TM4C123 family (ARM Cortex-M4).

Key locations
-------------
- **Application entry:** [src/main.c](src/main.c)
- **Startup / vectors:** [startup/startup.c](startup/startup.c)
- **Linker script:** [linker/tm4c123.ld](linker/tm4c123.ld)
- **Vendor drivers:** [tivaware/driver/](tivaware/driver/) (contains a Makefile)
- **Vendor headers:** [tivaware/inc/](tivaware/inc/) (contains `hw_*.h`, `hw_types.h`)
- **Top-level build files:** [CMakeLists.txt](CMakeLists.txt) and [toolchain-arm-none-eabi.cmake](toolchain-arm-none-eabi.cmake) — currently empty/placeholders.

What matters (big picture)
--------------------------
- This repository is firmware for a microcontroller — most code interacts with hardware through the TivaWare driver library in `tivaware/` and the low-level headers `tivaware/inc/hw_*.h`.
- The runtime is shaped by the startup file and the linker script: do not change symbol names or memory region sizes unless you understand Cortex-M reset vectors, stack/heap layout, and available RAM/Flash in `linker/tm4c123.ld`.
- High-level dataflow: application code in `src/` calls driver APIs in `tivaware/driver/` which manipulate registers defined in `tivaware/inc/`.

Build & debug notes (discoverable)
---------------------------------
- Toolchain: The repo expects an ARM cross toolchain (`arm-none-eabi-*`). The `toolchain-arm-none-eabi.cmake` file exists but is empty; there is no working CMake configuration currently in the tree.
- Vendor build: `tivaware/driver/Makefile` exists and describes how TivaWare drivers are built — inspect that Makefile for concrete compiler flags and include paths when preparing a toolchain invocation.
- Typical commands an engineer might use (adjust for your environment):

  - Install ARM toolchain (outside repo): `arm-none-eabi-gcc` / `arm-none-eabi-gdb`.
  - Build with CMake (if a proper toolchain file is added): `cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-none-eabi.cmake` then `cmake --build build`.
  - Use the provided driver Makefile to build the TivaWare pieces: run `make` in `tivaware/driver/` to inspect flags and object layout.

Project-specific conventions & patterns
-------------------------------------
- Vendor-first layout: device headers and low-level register definitions live in `tivaware/inc/` (example: [tivaware/inc/hw_gpio.h](tivaware/inc/hw_gpio.h)).
- Drivers live in `tivaware/driver/` and follow the TivaWare style (functions named like `GPIOPinWrite`, `SysCtlPeripheralEnable`, etc.). Use those APIs where present rather than hand-rolling register sequences.
- The linker script exports symbols that code may rely on (e.g. `Reset_Handler`, `__StackTop`). Search `linker/tm4c123.ld` before renaming or removing symbols.

Integration, licensing and safety
--------------------------------
- TivaWare is TI-supplied; see [tivaware/driver/readme.txt](tivaware/driver/readme.txt) for licensing terms. Do not remove or relicense vendor code; preserve the copyright notices.
- Hardware access is direct — avoid introducing dynamic memory allocations or large static buffers without checking `linker/tm4c123.ld` RAM limits.

Quick examples (where to look)
----------------------------
- To find how GPIOs are used: open [tivaware/driver/gpio.c](tivaware/driver/gpio.c) and cross-reference register macros in [tivaware/inc/hw_gpio.h](tivaware/inc/hw_gpio.h).
- To see interrupt/vector layout: inspect [startup/startup.c](startup/startup.c) and the `KEEP(*(.isr_vector))` section in [linker/tm4c123.ld](linker/tm4c123.ld).

When you are uncertain
---------------------
- Prefer reading the vendor `Makefile` and `tivaware` headers to infer compiler flags and peripheral macros.
- If you need to add a build system or toolchain configuration, keep changes isolated (new files and docs) and do not modify vendor sources in `tivaware/` beyond trivial fixes.

Next steps I can do now
----------------------
- Draft a minimal working `toolchain-arm-none-eabi.cmake` and `CMakeLists.txt` that compile `src/main.c` with `linker/tm4c123.ld` and the TivaWare drivers.

If any of the above is unclear or you'd like a specific scaffold (CMake or flash/debug scripts), tell me which target/toolchain you use and I'll prepare it.
