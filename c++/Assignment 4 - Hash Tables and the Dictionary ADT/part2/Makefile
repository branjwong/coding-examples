all: index_directory ii_debug

index_directory: index_directory.cpp InvertedIndex.o
	g++ index_directory.cpp -o index_directory InvertedIndex.o

InvertedIndex.o: InvertedIndex.cpp InvertedIndex.h
	g++ -c InvertedIndex.cpp

ii_debug: ii_debug.cpp InvertedIndex.o
	g++ ii_debug.cpp -o ii_debug InvertedIndex.o


clean:
	rm -f *.o ii_debug index_directory