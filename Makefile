# Copyright Matthew Calligaro, Aditya Khant December 2019

################################################################################
# Variables
################################################################################

CXX = clang++
CXXFLAGS = -O3 -std=c++1z -Wall -Wextra -Wno-unused-parameter -pedantic -g
TARGET = c4
LIBRARIES = -lpthread

################################################################################
# Main Executable
################################################################################

all: $(TARGET)

$(TARGET): agent-benchmark.o agent-human.o agent-mcts.o agent-minimax.o \
	agent-minimaxSARSA.o agent-null.o agent-sarsa.o board.o c4.o game.o \
	mc-train.o sarsa-train.o test.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBRARIES)

################################################################################
# Object Files
################################################################################

agent-benchmark.o: agents/agent-benchmark.cpp agents/agent-benchmark.hpp \
	agents/agent-minimax.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-human.o: agents/agent-human.cpp agents/agent-human.hpp agents/agent.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-mcts.o: agents/agent-mcts.cpp agents/agent-mcts.hpp agents/agent.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-minimax.o: agents/agent-minimax.cpp agents/agent-minimax.hpp \
	agents/agent.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-minimaxSARSA.o: agents/agent-minimaxSARSA.cpp \
	agents/agent-minimaxSARSA.hpp agents/agent.hpp sarsa-train.hpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-null.o: agents/agent-null.cpp agents/agent-null.hpp agents/agent.hpp
	$(CXX) $< -c $(CXXFLAGS)

agent-sarsa.o: agents/agent-sarsa.cpp agents/agent-sarsa.hpp agents/agent.hpp \
	sarsa-train.hpp	board.hpp
	$(CXX) $< -c $(CXXFLAGS)

board.o: board.cpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

c4.o: c4.cpp test.hpp
	$(CXX) $< -c $(CXXFLAGS)

game.o: game.cpp game.hpp agents/agent.hpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

mc-train.o: mc-train.cpp mc-train.hpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

precomputed-values.o: precomputed-values.cpp precomputed-values.hpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

sarsa_train.o: sarsa-train.cpp sarsa-train.hpp board.hpp
	$(CXX) $< -c $(CXXFLAGS)

test.o: test.cpp test.hpp agents/agent-benchmark.hpp agents/agent-human.hpp \
	agents/agent-mcts.hpp agents/agent-minimax.hpp \
	agents/agent-minimaxSARSA.hpp agents/agent-null.hpp board.hpp game.hpp
	$(CXX) $< -c $(CXXFLAGS)

################################################################################
# Special Targets
################################################################################

doxygen:
	doxygen config/doxygen.config

lint:
	-cpplint *.*pp
	-cpplint */*.*pp

auto-format:
	clang-format --style=file -i *.*pp

clean:
	rm -rf *.o $(TARGET) documentation
