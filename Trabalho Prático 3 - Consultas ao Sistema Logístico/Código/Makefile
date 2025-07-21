# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++11 -I$(INCLUDE_DIR)

# Directories aliases
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (automatically derived from SRC)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# .exe alias desired by the problem statement
EXEC = tp3.out
TARGET = $(BIN_DIR)/$(EXEC)

HEADERS = $(wildcard $(INCLUDE_DIR)/*.hpp)

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

# --- Directory creation rules ---
# These are order-only prerequisites '|' meaning they are created before
# the rule runs, but changes to them don't force recompilation of the targets
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# --- Clean target ---
clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(TARGET)

c:
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(TARGET)

clear:
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(TARGET)

.PHONY: all clean