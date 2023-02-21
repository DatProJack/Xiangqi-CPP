CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
.PHONY: clean

SOURCE_DIR = src
INCLUDE_DIR = includes
BUILD_DIR = bin

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

EXECUTABLE = xiangqi.exe

$(EXECUTABLE): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
