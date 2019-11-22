
CXX = clang++
CXXFLAGS = -O3 -std=c++1z -Wall -Wextra -pedantic
TARGET = c4
LIBRARIES = -lpthread

all: $(TARGET)

$(TARGET): c4.o game.o agent-null.o agent-human.o agent-minimax.o sarsa-train.o board.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBRARIES)

c4.o: c4.cpp agent-null.hpp game.hpp
	$(CXX) $< -c $(CXXFLAGS)

game.o: game.cpp game.hpp agent.hpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-null.o: agent-null.cpp agent-null.hpp agent.hpp
	$(CXX) $< -c $(CXXFLAGS)
	
agent-human.o: agent-human.cpp agent-human.hpp agent.hpp
	$(CXX) $< -c $(CXXFLAGS)

sarsa_train.o: sarsa-train.cpp sarsa-train.hpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-minimax.o: agent-minimax.cpp agent-minimax.hpp agent.hpp
	$(CXX) $< -c $(CXXFLAGS)

board.o: board.cpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

lint: 
	cpplint *.cpp
	cpplint *.hpp

clean:
	rm -rf *.o $(TARGET)
