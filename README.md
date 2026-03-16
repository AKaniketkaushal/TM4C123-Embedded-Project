# TM4C123 Embedded Project

Embedded firmware template for the Texas Instruments TM4C123GH6PM / EKâ€‘TM4C123GXL LaunchPad using:

- GCC arm-none-eabi
- CMake
- CMSIS
- TivaWare driver library
- FreeRTOS RTOS kernel

This repository is a working Cortexâ€‘M4F firmware project with:

- Startup code and linker script for TM4C123GH6PM
- FreeRTOS portable layer for GCC/ARM_CM4F
- UART and GPIO drivers using TivaWare
- A FreeRTOSâ€‘based demo application with tasks, queues, and UART interrupts

It is intended as a starting point for real projects, not just a trivial LED blink.

## Quick Start (WSL + CMake + OpenOCD)

From WSL (Ubuntu/Debian), assuming the repo is already cloned:

```bash
# 1) Install tools
sudo apt update
sudo apt install \
    gcc-arm-none-eabi binutils-arm-none-eabi gdb-multiarch \
    cmake ninja-build make git openocd

# 2) Configure + build
cd /mnt/c/YourPath/tm4c123gxl
mkdir -p build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm-none-eabi.cmake
cmake --build . -j4

# 3) Flash with OpenOCD (from build/)
sudo openocd \
  -f /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg \
  -c "program tm4c123gxl.elf verify reset exit"
```

Open a serial terminal at 115200 8â€‘Nâ€‘1 on the LaunchPadâ€™s virtual COM port to see output.

## Current Firmware Behavior

The example application in src/main.c currently does the following:

- Configures the system clock to 80 MHz using the PLL.
- Configures UART0 on PA0/PA1 at 115200 8â€‘Nâ€‘1.
- Creates a FreeRTOS queue to hold received UART characters.
- Sets up a UART0 interrupt handler that:
  Reads characters from the UART RX FIFO.
  Pushes them into a FreeRTOS queue (from ISR context).
- Creates a UART task that:
  Waits for characters from the queue.
  Echoes them back over UART.
  Prints " - received" after each character.
- Creates a heartbeat task that:
  Runs every 2 seconds.
  Prints an incrementing "Alive: N" counter.
- Starts the FreeRTOS scheduler.

Typical serial output after reset:

```text
=== System Starting ===
Starting FreeRTOS scheduler...
UART Task Running!
Heartbeat Task Running!
Alive: 0
Alive: 1
Alive: 2
...
```

Typing characters in the serial terminal echoes them and prints:

```text
a - received
b - received
...
```

## Repository Layout

Highâ€‘level structure:

```text
.
|- CMakeLists.txt                     # Top-level CMake project
|- toolchain-arm-none-eabi.cmake      # Cross-compile toolchain definition
|
|- linker/
|  \- tm4c123.ld                      # Linker script for TM4C123GH6PM
|
|- src/
|  |- main.c                          # Application entry point + tasks + ISRs
|  \- FreeRTOSConfig.h                # FreeRTOS configuration for this board
|
|- CMSIS/                             # CMSIS core support (startup, headers)
|- Freertos/                          # FreeRTOS kernel source / port
|- tivaware/                          # TivaWare driverlib (GPIO, UART, etc.)
|
|- SVD/
|  \- TM4C123GH6PM.svd                # SVD file for debug (register view)
|
\- Keil.TM4C_DFP.pdsc                 # Device description package (Keil-style)
```

Most user code lives under src/. You generally donâ€™t need to modify CMSIS, FreeRTOS, or TivaWare directly.

## Prerequisites

### 1. WSL on Windows

From Windows PowerShell:

```powershell
wsl --install
```

Reboot if requested, then complete the Linux distro setup.

### 2. Install toolchain and build tools (inside WSL)

On Ubuntu/Debian inside WSL:

```bash
sudo apt update
sudo apt install \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    gdb-multiarch \
    cmake \
    ninja-build \
    make \
    git \
    openocd
```

Verify:

```bash
arm-none-eabi-gcc --version
arm-none-eabi-objcopy --version
arm-none-eabi-gdb --version
cmake --version
openocd --version
```

### 3. Locate the project directory in WSL

If the repo is on Windows at:

```text
C:\My_project\tm4c123gxl
```

Then in WSL:

```bash
cd /mnt/c/My_project/tm4c123gxl
```

You can also clone from WSL directly:

```bash
cd /mnt/c/My_project
git clone https://github.com/yourusername/tm4c123gxl.git
cd tm4c123gxl
```

## Configure and Build (CMake + arm-none-eabi)

This project uses a separate build directory and a toolchain file to target TM4C123 with GCC.

From the project root in WSL:

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm-none-eabi.cmake
cmake --build . -j4
```

Explanation:

- cmake .. configures the project:
  Uses ../toolchain-arm-none-eabi.cmake to set:
  CMAKE_C_COMPILER=arm-none-eabi-gcc
  CMAKE_CXX_COMPILER=arm-none-eabi-g++
  CPU/FPU flags for Cortexâ€‘M4F (-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16)
- cmake --build . -j4 builds with 4 parallel jobs (tune -j for your CPU).

On success, build/ contains:

- tm4c123gxl.elf â€“ ELF image with symbols and debug info.
- tm4c123gxl.bin â€“ raw binary.
- tm4c123gxl.hex â€“ Intel HEX.
- output.map â€“ linker map (memory layout, symbol addresses).

To inspect size:

```bash
arm-none-eabi-size tm4c123gxl.elf
```

Note: newlibâ€‘nano may print warnings like _write is not implemented and will always fail; these are normal for bareâ€‘metal unless you hook up lowâ€‘level syscalls.

## Flashing with OpenOCD

### 1. Connect the EKâ€‘TM4C123GXL

Plug the EKâ€‘TM4C123GXL LaunchPad into your Windows machine via USB.

Ensure the onâ€‘board ICDI debugger is recognized (Windows installs drivers and exposes a debug interface + virtual COM port).

WSL uses the same USB devices via Windows; OpenOCD will communicate through those drivers.

### 2. Oneâ€‘line flash command (no GDB)

From the build/ directory after a successful build:

```bash
cd build
sudo openocd \
  -f /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg \
  -c "program tm4c123gxl.elf verify reset exit"
```

This will:

- Use the builtâ€‘in EKâ€‘TM4C123GXL board config.
- Program tm4c123gxl.elf into flash.
- Verify the contents.
- Reset the MCU.
- Exit OpenOCD automatically.

### 3. Flash + debug with GDB (optional)

If you want breakpoints and singleâ€‘stepping with FreeRTOS tasks:

Terminal 1 â€“ OpenOCD server

```bash
sudo openocd \
  -f /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg
```

This starts an OpenOCD GDB server at localhost:3333.

Terminal 2 â€“ GDB client

```bash
cd /path/to/tm4c123gxl/build
arm-none-eabi-gdb tm4c123gxl.elf
```

From the GDB prompt:

```text
(gdb) target remote localhost:3333     # connect to OpenOCD
(gdb) monitor reset halt               # reset and halt MCU
(gdb) load                             # flash the ELF
(gdb) monitor reset run                # reset and run
```

Common GDB commands:

```text
(gdb) break main                       # set breakpoint
(gdb) continue
(gdb) info registers
(gdb) bt                               # backtrace
```

## Viewing Serial Output

After flashing, identify the virtual COM port exposed by the LaunchPad on Windows.

Open a serial terminal (PuTTY, TeraTerm, minicom, etc.) on that COM port at:

- Baud: 115200
- Data: 8 bits
- Parity: None
- Stop bits: 1

Press reset on the board to see the startup banner and FreeRTOS messages.

You should see something like:

```text
=== System Starting ===
Starting FreeRTOS scheduler...
UART Task Running!
Heartbeat Task Running!
Alive: 0
...
```

## FreeRTOS Configuration and Diagnostics

The project uses FreeRTOS with:

- CPU / FPU flags for Cortexâ€‘M4F (ARM_CM4F port).
- heap_4.c allocator.

FreeRTOSConfig.h is tuned for this project and can enable:

- Preemptive scheduling.
- API functions such as:
  vTaskDelay()
  Queues, semaphores, mutexes.
- Diagnostics:
  xPortGetFreeHeapSize()
  xPortGetMinimumEverFreeHeapSize()
  uxTaskGetStackHighWaterMark() for perâ€‘task stack usage.
  vTaskList() and vTaskGetRunTimeStats() if configUSE_TRACE_FACILITY and configGENERATE_RUN_TIME_STATS are set.

You can adjust these options in src/FreeRTOSConfig.h to match your use case (debug heavy vs productionâ€‘minimal).

## Extending the Template

Some ideas for using this as a base for real projects:

- Add more tasks for:
  Sensor acquisition (I2C/SPI).
  Communication protocols (BLE, UART, CAN).
  Logging to internal flash or external EEPROM.
- Replace the UART echo with a command parser.
- Use the SVD file (TM4C123GH6PM.svd) with your debugger to see registers.
- Enable and use more FreeRTOS runâ€‘time stats for profiling.

The current structure already demonstrates:

- Interruptâ€‘driven UART feeding a FreeRTOS queue from ISRs.
- Multiple tasks with different priorities.
- A realistic project layout that can scale beyond simple demos.

## Git Tips

Useful commands while working on this project:

```bash
# Show changed files
git status

# See unstaged changes
git diff

# See staged changes
git diff --staged

# Compare against origin/main
git fetch origin
git diff origin/main
```

## License

This project bundles thirdâ€‘party components:

- TivaWare (TI driver library).
- CMSIS (ARM core support).
- FreeRTOS (RTOS kernel).

Please review and comply with their respective licenses before redistributing or using this project in a commercial context.
