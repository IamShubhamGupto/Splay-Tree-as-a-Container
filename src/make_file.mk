a.out : client.o splay_tree.o
	g++ client.o splay_tree.o
client.o : client.cpp splay_tree.h
	g++ -c client.cpp
splay_tree.o : splay_tree.cpp splay_tree.h
	g++ -c splay_tree.cpp