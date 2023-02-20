CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
.PHONY: clean

SOURCE_FILES = main.cpp Board.cpp TranspositionTable.cpp ZobristHash.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)#Takes source files and replaces the .cpp with .o

EXECUTABLE = xiangqi.exe

$(EXECUTABLE): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -force $(OBJECT_FILES) $(EXECUTABLE)