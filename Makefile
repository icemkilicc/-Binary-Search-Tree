webstore:BinaryTree main
	g++ -std=c++11 BinaryTree.o main.o -o webstore
BinaryTree:
	g++ -std=c++11 -c BinaryTree.cpp -o BinaryTree.o
main:
	g++ -std=c++11 -c main.cpp -o main.o
	
	

