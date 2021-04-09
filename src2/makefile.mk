a.out : client.o splay_tree.o
	g++ -std=c++11 client.o splay_tree.o
client.o : client.cpp splay_tree.h
	g++ -c -std=c++11 client.cpp
splay_tree.o : splay_tree.cpp splay_tree.h
	g++ -c -std=c++11 splay_tree.cpp