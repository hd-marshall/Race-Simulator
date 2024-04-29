# g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include/ -o ../build/prog -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Include directories
INCLUDES = -I/opt/homebrew/Cellar/sfml/2.6.1/include/

# Library directories
LIB_DIRS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib

# Libraries to link
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source directory
SRCDIR = src

# Object directory
OBJDIR = build

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Target executable
TARGET = ../build/prog

# Build rule
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB_DIRS) $(LIBS)

# Rule to compile .cpp files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create the build directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm -rf $(OBJDIR) $(TARGET)
