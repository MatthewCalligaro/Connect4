CXX = clang++
CXXFLAGS = -O3 -std=c++1z -Wall -Wextra -pedantic
TARGET = c4

all: $(TARGET)

$(TARGET): c4.o board.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

c4.o: c4.cpp game.hpp agent-null.hpp board.hpp

game.o: game.hpp game.cpp
	$(CXX) $< -c $(CXXFLAGS)

agent-null.o: agent-null.cpp agent-null.hpp
	$(CXX) $< -c $(CXXFLAGS)

board.o: board.cpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

clean:
	rm -rf *.o $(TARGET)
