## Makefile with incremental compilation for OpenGL project

# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -I./include -DFREETYPE_AVAILABLE -I/mingw64/include/freetype2 -I/mingw64/include
DEPFLAGS := -MMD -MP

INCLUDEDIRS := $(shell find include -type d)
INCLUDEFLAGS := $(patsubst %,-I%,$(INCLUDEDIRS)) -I/mingw64/include/freetype2 -I/mingw64/include

LDFLAGS := -L./lib -L/mingw64/lib
LIBS := -lglfw3dll -lopengl32 -lgdi32 -luser32 -lkernel32 -lfreetype

# Files and directories
OUTDIR := build
OBJDIR := $(OUTDIR)/obj
TARGET := $(OUTDIR)/main.exe
SOURCES := $(shell find src -type f \( -name "*.cpp" -o -name "*.c" \))
OBJECTS := $(SOURCES:src/%.cpp=$(OBJDIR)/%.o)
OBJECTS := $(OBJECTS:src/%.c=$(OBJDIR)/%.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(OUTDIR)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $(TARGET)

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $(DEPFLAGS) -MF $(OBJDIR)/$*.d -c $< -o $@

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $(DEPFLAGS) -MF $(OBJDIR)/$*.d -c $< -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

run: all
	$(TARGET)

clean: 
	rm -rf $(OBJDIR) $(TARGET)

# Include dependency files
-include $(OBJECTS:.o=.d)
