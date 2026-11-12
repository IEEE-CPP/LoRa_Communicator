.PHONY: all clean build prog setup

BOARD ?= esp32_devkitc_procpu
BUILD_DIR ?= build
PYTHON ?= $(abspath .venv/bin/python)
ESPTOOL ?= esptool
CHIP ?= esp32
PORT ?= /dev/ttyUSB0
BAUD ?= 921600
FLASH_OFFSET ?= 0x1000
BIN ?= $(abspath $(BUILD_DIR)/zephyr/zephyr.bin)
CMAKE_ARGS ?=

all: clean build

clean:
	rm -rf "$(BUILD_DIR)"

build:
	cmake -S . -B "$(BUILD_DIR)" -G Ninja -DBOARD="$(BOARD)" -DPython3_EXECUTABLE="$(PYTHON)" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $(CMAKE_ARGS)
	cmake --build "$(BUILD_DIR)"

prog:
	@test -f "$(BIN)" || { echo "Build not found: $(BIN)" >&2; exit 1; }
	$(ESPTOOL) --chip "$(CHIP)" --port "$(PORT)" --baud "$(BAUD)" write-flash "$(FLASH_OFFSET)" "$(BIN)"

setup:
	bash setup.sh
