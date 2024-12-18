# Targets
.PHONY: all test clean

BUILD_TOOL_CMD := make -j$(shell nproc) -C $(TOP_DIR)
BUILD_CMD := $(BUILD_TOOL_CMD) build
TEST_CMD := $(BUILD_TOOL_CMD) test
RUN_CMD := $(BUILD_TOOL_CMD) run
CLEAN_CMD := $(BUILD_TOOL_CMD) clean
SONAR_CMD := $(BUILD_TOOL_CMD) sonar