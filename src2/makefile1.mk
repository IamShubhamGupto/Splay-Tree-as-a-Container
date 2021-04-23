a.out : client1.o splay_tree.o
	g++ -g -std=c++11 client1.o splay_tree.o
client1.o : client1.cpp splay_tree.h
	g++ -c -g -std=c++11 client1.cpp
splay_tree.o : splay_tree.cpp splay_tree.h
	g++ -c -g -std=c++11 splay_tree.cpp