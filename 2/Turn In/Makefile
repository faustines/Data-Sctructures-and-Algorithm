all: postfix_eval luggage_handling

postfix_eval: postfix_eval.o
	-g++ -Wall -Werror -std=c++11 -o postfix_eval postfix_eval.o
postfix_eval.o: postfix_eval.cc
	-g++ -Wall -Werror -std=c++11 -o postfix_eval.o -c postfix_eval.cc

luggage_handling: luggage_handling.o
	-g++ -Wall -Werror -std=c++11 -o luggage_handling luggage_handling.o
luggage_handling.o: postfix_eval.cc
	-g++ -Wall -Werror -std=c++11 -o luggage_handling.o -c luggage_handling.cc

clean:
	-rm postfix_eval postfix_eval.o luggage_handling luggage_handling.o 
