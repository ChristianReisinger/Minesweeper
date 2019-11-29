all: bin/Minesweeper bin/Test

bin/Minesweeper: src/Minesweeper.c src/command_line.c build/board.o 
	gcc -x c -o $@ -I"include" $^
	
bin/Test: src/test/Test.c src/tests/board.c include/tests/board.h build/board.o
	gcc -x c -o $@ -I"include" $< -lm
	
build/board.o: src/board.c include/board.h
	gcc -x c -c -o $@ -I"include" $<
	
clean:
	rm -rf bin/* build/*