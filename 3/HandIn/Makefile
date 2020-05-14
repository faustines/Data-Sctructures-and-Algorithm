all: bt_succinct_dec bst_tester

bt_succinct_dec: bt_succinct_dec.o
	-g++ -Wall -Werror -std=c++11 -g -o $@ $<
bt_succinct_dec.o: bt_succinct_dec.cc binary_tree.h
	-g++ -Wall -Werror -std=c++11 -g -o $@ -c $<

bst_tester: bst_tester.o
	-g++ -Wall -Werror -std=c++11 -g -o $@ $<
bst_tester.o: bst_tester.cc bst.h
	-g++ -Wall -Werror -std=c++11 -g -o $@ -c $<

clean:
	-rm -f bt_succinct_dec bt_succinct_dec.o bst_tester bst_testerr.o
