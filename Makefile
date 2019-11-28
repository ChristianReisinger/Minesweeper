all:
	gcc -x c -o bin/Minesweeper -I"include" src/Minesweeper.c
	
clean:
	rm -rf bin/*