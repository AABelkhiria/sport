# Makefile for building the Zephyr application

# Variables
BOARD = esp32c3_supermini
APP_DIR = app
WEST = west

# Targets
.PHONY: all build clean flash

all: build

build:
	$(WEST) build -p always -b $(BOARD) $(APP_DIR)

clean:
	$(WEST) build -t clean

flash:
	$(WEST) flash

debug:
	$(WEST) debug