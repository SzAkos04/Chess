CXX := g++
PROJECT := chess
CFLAGS := -Wall -Wextra -Werror -Wpedantic -std=c++20
LDFLAGS := -lSDL2
INCLUDES := -Iinclude
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR := build
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
.PHONY: all build run clean

all: run

build: $(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDES) $(BUILD_ARGS)

$(BUILD_DIR)/$(PROJECT): $(OBJ)
	$(CXX) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(BUILD_ARGS)

release:
	$(MAKE) BUILD_ARGS="-O3" -B

run: build
	./$(BUILD_DIR)/$(PROJECT) $(ARGS)

clean:
	rm -rf $(BUILD_DIR)
