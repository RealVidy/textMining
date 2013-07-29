all:
	g++ -std=c++11 -O3 -march=native -pedantic src/patriciaTrie/patriciaTrie.cpp src/patriciaTrie/main.cpp -o compilator -lz
	g++ -std=c++11 -O3 -march=native -pedantic src/patriciaTrie/patriciaTrie.cpp src/interpreter/interpreter.cpp src/interpreter/main.cpp -o compilator -lz
