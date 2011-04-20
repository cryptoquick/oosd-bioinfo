OBJS = 

bioinfo : src/main.o src/ui.o src/file.o src/seq.o
	g++ -o bioinfo src/main.o src/ui.o src/file.o src/seq.o

main.o: src/main.cpp
	g++ -c src/main.cpp

ui.o: src/ui.cpp src/ui.h
	g++ -c src/ui.cpp src/ui.h

file.o: src/file.cpp src/file.h
	g++ -c src/file.cpp src/file.h

seq.o: src/seq.cpp src/seq.h
	g++ -c src/seq.cpp src/seq.h

clean:
	rm -f src/*.o bioinfo
