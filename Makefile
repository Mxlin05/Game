## Simple Makefile to build and run the OpenGL project without VS Code tasks

# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -I./include
LDFLAGS := -L./lib
LIBS := -lglfw3dll -lopengl32 -lgdi32 -luser32 -lkernel32

# Files and directories
OUTDIR := build
TARGET := $(OUTDIR)/main.exe
SOURCES := src/main.cpp src/glad.c src/Input.cpp src/Shadder.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) | $(OUTDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SOURCES) $(LIBS) -o $(TARGET)

$(OUTDIR):
	mkdir -p $(OUTDIR)

run: all
	$(TARGET)

clean:
	rm -f $(TARGET)


