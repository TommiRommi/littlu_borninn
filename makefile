# base dirs
SKETCH 	:= sketch
PROC		:= $(SKETCH)/$(SKETCH).ino
BUILD_DIR	:= build

# hide output
VERBOSE ?= 0
ifeq ($(VERBOSE),0)
	V := @
endif

# compiler
COMP	:= arduino-cli
FQDN	:= --fqbn arduino:avr:uno

# targets
all: $(BUILD_DIR)

$(BUILD_DIR): $(PROC)
	$(V)$(COMP) compile $(FQDN) --output-dir $(BUILD_DIR) $(PROC)

clean:
	$(V)$(RM) -r $(BUILD_DIR)
