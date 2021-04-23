a.out : client2.o splay_tree.o
	g++ -g -std=c++11 client2.o splay_tree.o
client2.o : client2.cpp splay_tree.h
	g++ -c -g -std=c++11 client2.cpp
splay_tree.o : splay_tree.cpp splay_tree.h
	g++ -c -g -std=c++11 splay_tree.cpp