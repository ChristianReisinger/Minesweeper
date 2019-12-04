BIN_DIR=bin
BUILD_DIR=build
INCLUDE_DIR=include
SRC_DIR=src

GEOMETRY_PATH=geometry/rectangle

OBJ_NAMES=util board command_line_rect console_ui
GEOMETRY_OBJ_NAMES=geometry
TEST_OBJ_NAMES=board util command_line_rect

###################################################################################################

OBJS=${OBJ_NAMES:%=${BUILD_DIR}/%.o}
GEOMETRY_OBJS=${GEOMETRY_OBJ_NAMES:%=${BUILD_DIR}/%.o}
TEST_OBJS=${TEST_OBJ_NAMES:%=${BUILD_DIR}/tests/%.o}

.PHONY: all clean

all: bin/Minesweeper bin/Test

${BIN_DIR}/Minesweeper: ${SRC_DIR}/Minesweeper.c ${OBJS} ${GEOMETRY_OBJS}
	gcc -o $@ -I"${INCLUDE_DIR}" $^ -lm
	
${BIN_DIR}/Test: ${SRC_DIR}/tests/Test.c ${TEST_OBJS} ${OBJS} ${GEOMETRY_OBJS}
	gcc -o $@ -I"${INCLUDE_DIR}" $^ -lm

${GEOMETRY_OBJS}: ${BUILD_DIR}/%.o: ${SRC_DIR}/${GEOMETRY_PATH}/%.c ${INCLUDE_DIR}/%.h
	gcc -c -o $@ -I"${INCLUDE_DIR}" $<
	
${OBJS} ${TEST_OBJS}: ${BUILD_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE_DIR}/%.h
	gcc -c -o $@ -I"${INCLUDE_DIR}" $<
	
clean:
	rm -rf bin build
	mkdir -p bin build/tests