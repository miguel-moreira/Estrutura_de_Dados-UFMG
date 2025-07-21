CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++11 -I$(INCLUDE_DIR)

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include

# Source files
SRC = $(SRC_DIR)/pa2.cpp \
      $(SRC_DIR)/graph.cpp \
      $(SRC_DIR)/listadeadjacencia.cpp \
      $(SRC_DIR)/listaencadeada.cpp

# Object files (automatically derived from SRC)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

EXEC = pa2.out
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

# --- Dependency tracking ---
# Phony target to generate dependency files (.d)
# This requires specific compiler flags like -MMD or -MP,
# which we can add to CXXFLAGS or handle separately if needed.
# For simplicity in this example, we'll manually define dependencies.

# Manual dependencies for headers (more robust way uses auto-generation)
$(OBJ_DIR)/graph.o: $(INCLUDE_DIR)/graph.hpp $(INCLUDE_DIR)/listadeadjacencia.hpp
$(OBJ_DIR)/listadeadjacencia.o: $(INCLUDE_DIR)/listadeadjacencia.hpp $(INCLUDE_DIR)/listaencadeada.hpp
$(OBJ_DIR)/listaencadeada.o: $(INCLUDE_DIR)/listaencadeada.hpp

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

