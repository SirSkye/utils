SRC_DIR := src
BIN_DIR := bin

$(MAKECMDGOALS): %: $(BIN_DIR)/%

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	g++ $< -o $@