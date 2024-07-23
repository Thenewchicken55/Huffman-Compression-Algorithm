all:
	g++ -std=c++11 -c *.cpp
	g++ -std=c++11 *.o -o huffman.out

run: all
	./huffman.out

clean:
	rm -f *.o
	rm -f *.out
	rm -f valgrind-out.txt

gdb:
	g++ *.cpp -g
	gdb ./a.out

valgrind:
	g++ *.cpp -g
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./a.out
	nano valgrind-out.txt