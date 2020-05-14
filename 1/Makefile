vector_search: vector_search.o
	-g++ -Wall -Werror -std=c++11 -o vector_search vector_search.o
vector_search.o: vector_search.cc
	-g++ -Wall -Werror -std=c++11 -o vector_search.o -c vector_search.cc

clean:
	-rm vector_search vector_search.o *.dat
