# Include configuration files
include cfg/docker.mk

BUILD_CMD := "$(MAKE) build"
TEST_CMD := "$(MAKE) test"
RUN_CMD := "$(MAKE) run"
CLEAN_CMD := "$(MAKE) clean"

# Define the path to the Dockerfile
DOCKER_FILE_PATH := dockerfiles/Dockerfile.alpine

# Define the default target
.PHONY: all

# Targets
all: build run

# Target: build-image
# Description: Builds the Docker image using the specified Dockerfile
.PHONY: build-image
build-image:
	@$(DOCKER_HOST) image build -t $(DOCKER_IMG_NAME) -f $(DOCKER_FILE_PATH) $(DOCKER_BUILD_CONTEXT)

# Code Build
docker-build: build-image
	@$(DOCKER_HOST) container run $(DOCKER_ARG) $(DOCKER_IMG_NAME) $(BUILD_CMD)

# Test code
docker-test: build-image
	@$(DOCKER_HOST) container run $(DOCKER_ARG) $(DOCKER_IMG_NAME) $(TEST_CMD)

# Run code
docker-run: build-image
	@$(DOCKER_HOST) container run $(DOCKER_ARG) $(DOCKER_IMG_NAME) $(RUN_CMD)

# Clean
docker-clean: build-image
	@$(DOCKER_HOST) container run $(DOCKER_ARG) $(DOCKER_IMG_NAME) $(CLEAN_CMD)