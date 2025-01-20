# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Source files
SOURCES = src/main.cpp src/commands.cpp src/app.cpp src/database.cpp src/table.cpp src/trees/tree.cpp src/trees/node.cpp src/util.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Output executable
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
