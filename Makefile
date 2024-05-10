# g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include/ -o ../build/prog -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra

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

# Bin directory
BINDIR = bin

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Target executable in bin folder
TARGET = $(BINDIR)/prog

# Build rule
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB_DIRS) $(LIBS)

# Rule to compile .cpp files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create the build and bin directories if they don't exist
$(OBJDIR) $(BINDIR):
	mkdir -p $@

# Clean rule
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)