CC=gcc

SRC=src
BUILD=build
DOCS=docs
INCLUDE=include

SOURCES := \
	uxhw

OBJECTS := $(patsubst %,$(BUILD)/%.o,$(SOURCES))

LDFLAGS=
INCLUDE_FLAGS=-I$(INCLUDE)

.PHONY:= \
	build \
	run \
	docs \
	clean

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(BUILD)/main: $(BUILD)/main.o $(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

run : $(BUILD)/main
	echo $(OBJECTS)
	$(BUILD)/main

docs : $(DOCS)/config
	doxygen $(DOCS)/config

build : $(BUILD)/main

clean :
	rm -rf $(BUILD)


