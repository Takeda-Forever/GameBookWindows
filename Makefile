TARGET = Window

SRC = window.cpp Bee.cpp Background.cpp Cloud.cpp Tree.cpp Text.cpp

SFML_INCLUDE_DIR = F:/ProgInc/SFML/include
SFML_LIB_DIR = F:/ProgInc/SFML/lib

CXX = g++
CXXFLAGS = -I$(SFML_INCLUDE_DIR)
LDFLAGS = -L$(SFML_LIB_DIR) -lsfml-window -lsfml-graphics -lsfml-system

all: $(TARGET)	

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	erase $(TARGET).exe

rebuild: clean all
