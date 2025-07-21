CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++11 -I$(INCLUDE_DIR)

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include

# Source files
SRC = $(SRC_DIR)/pa3.cpp \
      $(SRC_DIR)/heap.cpp
      
# Object files (automatically derived from SRC)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Defining EXEC so it can be reused more easily and clearly
EXEC = pa3.out
TARGET = $(BIN_DIR)/$(EXEC)

# Default target: build the executable
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# Rule to compile .cpp files into .o files
# The $< is the first prerequisite (the .cpp file)
# The $@ is the target (the .o file)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(INCLUDE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Manual dependencies for headers
$(OBJ_DIR)/heap.o: $(INCLUDE_DIR)/heap.hpp

# --- Directory creation rules ---
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(SRC_DIR):
	mkdir -p $(SRC_DIR)

$(INCLUDE_DIR):
	mkdir -p $(INCLUDE_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# --- Clean target ---
clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(TARGET)

.PHONY: all clean

