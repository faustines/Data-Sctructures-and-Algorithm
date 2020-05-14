CXX := g++
CXXFLAGS := -Wall -Werror -std=c++11

all: shortest_path

shortest_path: shortest_path.cc index_min_pq.h
	-$(CXX) $(CXXFLAGS) -o shortest_path shortest_path.cc

execs = shortest_path

clean:
	-rm -f $(execs)
