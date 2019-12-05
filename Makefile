BIN_DIR=bin
BUILD_DIR=build
INCLUDE_DIR=include
SRC_DIR=src

GEOMETRY=rectangle

OBJ_NAMES=util board console_ui/formatting console_ui/console_ui
TEST_OBJ_NAMES=board util command_line_rect

###################################################################################################

OBJS=${OBJ_NAMES:%=${BUILD_DIR}/%.o}
TEST_OBJS=${TEST_OBJ_NAMES:%=${BUILD_DIR}/tests/%.o}

.PHONY: all clean

all: bin/Minesweeper bin/Test

${BIN_DIR}/Minesweeper: ${SRC_DIR}/Minesweeper.c ${OBJS} ${BUILD_DIR}/geometry/geometry.o ${BUILD_DIR}/geometry/console_ui.o ${BUILD_DIR}/geometry/command_line.o
	gcc -o $@ -I"${INCLUDE_DIR}" $^ -lm
	
${BIN_DIR}/Test: ${SRC_DIR}/tests/Test.c ${TEST_OBJS} ${OBJS} ${BUILD_DIR}/geometry/geometry.o ${BUILD_DIR}/geometry/console_ui.o ${BUILD_DIR}/geometry/command_line.o
	gcc -o $@ -I"${INCLUDE_DIR}" $^ -lm

${BUILD_DIR}/geometry/geometry.o: ${SRC_DIR}/geometry/${GEOMETRY}/geometry.c ${INCLUDE_DIR}/geometry/geometry.h
	gcc -c -o $@ -I"${INCLUDE_DIR}" $<
	
${BUILD_DIR}/geometry/console_ui.o: ${SRC_DIR}/geometry/${GEOMETRY}/console_ui.c ${INCLUDE_DIR}/geometry/console_ui.h
	gcc -c -o $@ -I"${INCLUDE_DIR}" $<
	
${BUILD_DIR}/geometry/command_line.o: ${SRC_DIR}/geometry/${GEOMETRY}/command_line.c ${INCLUDE_DIR}/geometry/command_line.h
	gcc -c -o $@ -I"${INCLUDE_DIR}" $<
	
	
${OBJS} ${TEST_OBJS}: ${BUILD_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE_DIR}/%.h
	gcc -c -o $@ -I"${INCLUDE_DIR}" $<
	
clean:
	rm -rf bin build
	mkdir -p bin build/geometry build/tests build/console_ui