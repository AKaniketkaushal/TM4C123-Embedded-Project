cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain-arm-none-eabi.cmake)

project(tm4c123gxl C ASM)
set(CMAKE_C_STANDARD 11)


# CPU flags - use string() to properly combine
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

# Compiler flags
set(CMAKE_C_FLAGS "${CPU_FLAGS} -Wall -O0 -g3 -ffunction-sections -fdata-sections")
set(CMAKE_ASM_FLAGS "${CPU_FLAGS}")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -T${CMAKE_SOURCE_DIR}/linker/tm4c123.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=output.map")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=nosys.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc -lm -lnosys")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/CMSIS/core/Include
    ${CMAKE_SOURCE_DIR}/CMSIS/core/Include/m-profile
    ${CMAKE_SOURCE_DIR}/CMSIS/Device/Inludes
    ${CMAKE_SOURCE_DIR}/tivaware
    ${CMAKE_SOURCE_DIR}/tivaware/inc
    ${CMAKE_SOURCE_DIR}/tivaware/driver
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/Freertos/include
    ${CMAKE_SOURCE_DIR}/Freertos/portable/GCC/ARM_CM4F
)

# Defines
add_definitions(-DPART_TM4C123GH6PM -DTARGET_IS_TM4C123_RB1 -D__FPU_PRESENT=1)

# Source files
set(TIVAWARE_SOURCES
    ${CMAKE_SOURCE_DIR}/tivaware/driver/adc.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/aes.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/can.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/comp.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/cpu.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/crc.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/des.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/eeprom.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/emac.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/epi.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/flash.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/fpu.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/gpio.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/hibernate.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/i2c.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/interrupt.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/lcd.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/mpu.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/onewire.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/pwm.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/qei.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/shamd5.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/ssi.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/sw_crc.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/sysctl.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/sysexc.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/systick.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/timer.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/uart.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/udma.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/usb.c
    ${CMAKE_SOURCE_DIR}/tivaware/driver/watchdog.c
)

set(FREERTOS_SOURCES
    ${CMAKE_SOURCE_DIR}/Freertos/croutine.c
    ${CMAKE_SOURCE_DIR}/Freertos/event_groups.c
    ${CMAKE_SOURCE_DIR}/Freertos/list.c
    ${CMAKE_SOURCE_DIR}/Freertos/queue.c
    ${CMAKE_SOURCE_DIR}/Freertos/stream_buffer.c
    ${CMAKE_SOURCE_DIR}/Freertos/tasks.c
    ${CMAKE_SOURCE_DIR}/Freertos/timers.c
    ${CMAKE_SOURCE_DIR}/Freertos/MemMang/heap_4.c
    ${CMAKE_SOURCE_DIR}/Freertos/portable/GCC/ARM_CM4F/port.c
)

# Combine all source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/CMSIS/Device/Source/startup.c
    ${CMAKE_SOURCE_DIR}/CMSIS/Device/Source/system_TM4C123.c
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${TIVAWARE_SOURCES}
    ${FREERTOS_SOURCES}
)

# Verify sources
message(STATUS "Checking source files:")
foreach(src_file ${SOURCES})
    if(EXISTS ${src_file})
        message(STATUS "  ✓ ${src_file}")
    else()
        message(FATAL_ERROR "  ✗ NOT FOUND: ${src_file}")
    endif()
endforeach()

# Create executable
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Post-build commands
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Generating binary and hex files, showing size"
)

message(STATUS "")
message(STATUS "Configuration complete!")
message(STATUS "Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C Flags: ${CMAKE_C_FLAGS}")
message(STATUS "Linker Flags: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "Build with: make")
