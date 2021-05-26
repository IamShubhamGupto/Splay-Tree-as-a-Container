OUTPUT_PATH = bin
SRC_PATH = src
FLAGS = -c -g -std=c++11 -O3
CC = g++

a.out : client.o splay_tree.o
	$(CC) -g -std=c++11 $(OUTPUT_PATH)/client.o $(OUTPUT_PATH)/splay_tree.o -o $(OUTPUT_PATH)/a.out

client.o : $(clientfile) 
	@mkdir -p ${OUTPUT_PATH}
	$(CC) $(FLAGS) $(clientfile) -o $(OUTPUT_PATH)/client.o

splay_tree.o : $(SRC_PATH)/splay_tree.cpp 
	$(CC) $(FLAGS) $(SRC_PATH)/splay_tree.cpp -o $(OUTPUT_PATH)/splay_tree.o

clean:
	rm -r -f $(OUTPUT_PATH)/