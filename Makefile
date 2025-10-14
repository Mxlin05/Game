## Simple Makefile to build and run the OpenGL project without VS Code tasks

# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -I./include -DFREETYPE_AVAILABLE -I/mingw64/include/freetype2 -I/mingw64/include
LDFLAGS := -L./lib -L/mingw64/lib
LIBS := -lglfw3dll -lopengl32 -lgdi32 -luser32 -lkernel32 -lfreetype

# Files and directories
OUTDIR := build
TARGET := $(OUTDIR)/main.exe
SOURCES := src/main.cpp src/glad.c src/Input.cpp src/Shadder.cpp src/VertexBuffer.cpp src/IndexBuffer.cpp src/VertexArray.cpp src/Render.cpp src/Camera.cpp src/GameObject.cpp src/Scene.cpp src/Sprite.cpp src/Texture.cpp src/TileMap.cpp src/Player.cpp src/Physics.cpp src/Enemy.cpp src/Pathfind.cpp src/UIManager.cpp src/UIScreen.cpp src/StartMenuScreen.cpp src/Item.cpp src/Inventory.cpp src/Weapon.cpp src/Armor.cpp src/Npc.cpp src/TextRender.cpp

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
