# Author: Manzill0 (http://stackoverflow.com/questions/231229/how-to-generate-a-makefile-with-source-in-sub-directories-using-just-one-makefil)

sm	  := STATE_CENTRIC

CC        := gcc -D$(sm)
LD        := gcc

MODULES   := ./ state_machines headers
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ       := $(patsubst src/%.c,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.c $(SRC_DIR)

define make-goal
$1/%.o: %.c
	@$(CC) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

run: clean all
	@echo Running state-machine type: $(sm)
	@./build/trafficlight

all: checkdirs build/trafficlight

build/trafficlight: $(OBJ)
	@$(LD) $^ -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf build

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
