CXX := g++
CXXFLAGS := -Wall -Werror -std=c++11

all: cfs_sched map_tester multimap_tester

cfs_sched: cfs_sched.cc llrb_multimap.h
	-$(CXX) $(CXXFLAGS) -o cfs_sched cfs_sched.cc

map_tester: map_tester.cc llrb_map.h
	-$(CXX) $(CXXFLAGS) -o map_tester map_tester.cc

multimap_tester: multimap_tester.cc llrb_multimap.h
	-$(CXX) $(CXXFLAGS) -o multimap_tester multimap_tester.cc

execs = cfs_sched map_tester multimap_tester

clean:
	-rm -f $(execs)
