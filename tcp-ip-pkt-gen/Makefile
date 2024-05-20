# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra
LDFLAGS := -pthread

# Commands
MKDIR := mkdir -p
RMDIR := rm -rf

# Directories
INC_DIR := inc
SRC_DIR := src
TEST_INC := test/inc
TEST_DIR := test/src
BUILD_DIR := build
BIN_DIR := bin

DEBUG_EXEC:=debugBin
RELEASE_EXEC:=releaseBin

# Files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
TESTSRC := $(wildcard $(TEST_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
TESTOBJ := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TESTSRC))
DEP := $(OBJ:.o=.d)
TESTDEP := $(TESTOBJ:.o=.d)
EXEC := $(BIN_DIR)/$(DEBUG_EXEC)

# Targets
.DEFAULT_GOAL := all

.PHONY: all clean

all: clean build test run

build: clean $(EXEC)

test: $(EXEC) # TODO
	$(EXEC)

run: $(EXEC)
	@./$(EXEC)

clean:
	@$(RMDIR) $(BUILD_DIR) $(BIN_DIR)

# Compile rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR) $(@D)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@$(MKDIR) $(@D)
	@$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(TEST_DIR) -MMD -MP -c $< -o $@

# Link rule
$(EXEC): $(OBJ) $(TESTOBJ)
	@$(MKDIR) $(@D)
	@$(CXX) $(LDFLAGS) $^ -o $@