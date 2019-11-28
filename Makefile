all:
	gcc -x c -o bin/Minesweeper -I"include" src/Minesweeper.c src/command_line.c
	
clean:
	rm -rf bin/*