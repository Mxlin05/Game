## Simple Makefile to build and run the OpenGL project without VS Code tasks

# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -I./include -DFREETYPE_AVAILABLE -I/mingw64/include/freetype2 -I/mingw64/include
LDFLAGS := -L./lib -L/mingw64/lib
LIBS := -lglfw3dll -lopengl32 -lgdi32 -luser32 -lkernel32 -lfreetype

# Files and directories
OUTDIR := build
TARGET := $(OUTDIR)/main.exe
SOURCES := $(shell find src -type f \( -name "*.cpp" -o -name "*.c" \))

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) | $(OUTDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SOURCES) $(LIBS) -o $(TARGET)

$(OUTDIR):
	mkdir -p $(OUTDIR)

run: all
	$(TARGET)

clean: 
	rm -f $(TARGET)/*o $(TARGET)

test-math: src/Math/Vector2D.cpp test/Math_test/Vector2D_test.cpp
	$(CXX) $(CXXFLAGS) -o build/test_math src/Math/Vector2D.cpp test/Math_test/Vector2D_test.cpp $(LDFLAGS)
	./build/test_math
