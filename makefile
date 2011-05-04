bioinfo: src/main.o src/ui.o src/file.o src/seq.o src/needleman_wunsch.o src/smith.o src/algorithm.o
	g++ -o bioinfo src/main.o src/ui.o src/file.o src/seq.o src/needleman_wunsch.o src/smith.o src/algorithm.o

main.o: src/main.cpp
	g++ -Wall -c src/main.cpp

ui.o: src/ui.cpp src/ui.h
	g++ -Wall -c src/ui.cpp src/ui.h

file.o: src/file.cpp src/file.h
	g++ -Wall -c src/file.cpp src/file.h

seq.o: src/seq.cpp src/seq.h
	g++ -Wall -c src/seq.cpp src/seq.h
	
algorithm.o: src/algorithm.cpp src/algorithm.h
	g++ -Wall -c src/algorithm.cpp src/algorithm.h

needleman_wunsch.o:
	g++ -Wall -c src/needleman_wunsch.cpp src/needleman_wunsch.h

smith.o:
	g++ -Wall -c src/smith.cpp src/smith.h

clean:
	rm -f src/*.o bioinfo
