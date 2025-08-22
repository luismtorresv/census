# Template adapted from that of Job Vranish
# (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)

TARGET_EXEC_NAME := census
TARGET_EXEC_PATH  = $(BUILD_DIR)/$(TARGET_EXEC_NAME)

BUILD_DIR := ./build
SRC_DIRS  := ./src

# Find all the C files we want to compile
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.c turns into ./build/./your_dir/hello.c.o
OBJS_CLASS  := $(SRCS:%=$(BUILD_DIR)/class/%.o)
OBJS_STRUCT := $(SRCS:%=$(BUILD_DIR)/struct/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.c.o turns into ./build/hello.c.d
DEPS := $(OBJS_CLASS:.o=.d) $(OBJS_STRUCT:.o=.d)

# Every folder in ./src will need to be passed to GCXX so that it can find header files
INC_DIRS := src
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCXX understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))


CXX = g++

CXXFLAGS  = -std=c++20
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
CXXFLAGS += -Werror
CXXFLAGS += -Wpedantic
CXXFLAGS += -Wunused
CXXFLAGS += -Wunreachable-code
CXXFLAGS += -g
CXXFLAGS += -Wno-unused-variable

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer



all: help

.PHONY: help
help:
	@echo "make class or make struct"

# Final build step with classes.
class: $(TARGET_EXEC_PATH)-class
	@$(TARGET_EXEC_PATH)-class

# Final build step with structs.
struct: $(TARGET_EXEC_PATH)-struct
	@$(TARGET_EXEC_PATH)-struct

$(TARGET_EXEC_PATH)-class: $(OBJS_CLASS)
	$(CXX) $^ -o $@

$(TARGET_EXEC_PATH)-struct: $(OBJS_STRUCT)
	$(CXX) $^ -o $@

# Build step for C++ source
$(BUILD_DIR)/class/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/struct/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -DPERSON_AS_STRUCT -c $< -o $@

# Memory check
$(BUILD_DIR)/memcheck.out: $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(ASANFLAGS) $(CPPFLAGS) -o $@ $^

.PHONY: memcheck
memcheck: $(BUILD_DIR)/memcheck.out
	./$<
	@echo "Memory check passed"

.PHONY: format
format:
	clang-format -i `find . -depth  -name '*.cpp' -o -name '*.hpp'`

.PHONY: clean
clean:
	$(RM) -r $(TARGET_EXEC) $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)

MKDIR_P ?= mkdir -p
