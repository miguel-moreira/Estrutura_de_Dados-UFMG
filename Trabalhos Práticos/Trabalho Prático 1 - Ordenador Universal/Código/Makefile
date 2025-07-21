# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++11 -I$(INCLUDE_DIR)

# Directories aliases
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include

# Source files
SRC = $(SRC_DIR)/tp1.cpp \
	  $(SRC_DIR)/estatisticas.cpp

# Object files (automatically derived from SRC)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# .exe alias desired by the problem statement
EXEC = tp1.out
TARGET = $(BIN_DIR)/$(EXEC)

# All the headers used to make it easier to compile
HEADERS = $(INCLUDE_DIR)/vector.hpp $(INCLUDE_DIR)/ordenadoruniversal.hpp $(INCLUDE DIR)/estatisticas.hpp $(INCLUDE_DIR)/sorts.hpp

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

# Manual dependencies for headers (more robust way uses auto-generation)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) # Depende do .cpp e dos headers relevantes
	@$(CXX) $(CXXFLAGS) -c $< -I $(INCLUDE_DIR) -o $@

# --- Directory creation rules ---
# These are order-only prerequisites '|' meaning they are created before
# the rule runs, but changes to them don't force recompilation of the targets
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