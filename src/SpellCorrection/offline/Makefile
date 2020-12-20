SRC_DIR:= ./src
OBJ_DIR:= ./obj
BIN_DIR:= ./bin
INC_DIR:= ./inc

SRCS:= ${wildcard ${SRC_DIR}/*.cc}
OBJS:= ${patsubst %.cc,${OBJ_DIR}/%.o, ${notdir ${SRCS}}}

TARGET=main
BIN_TARGET=${BIN_DIR}/${TARGET}

CXX = g++
LIBS:= -lpthread -g
CXXFLAGS:= -std=c++11 -g -I${INC_DIR} 

${BIN_TARGET}:${OBJS}
	${CXX} ${OBJS} -o $@  ${LIBS}

${OBJ_DIR}/%.o:${SRC_DIR}/%.cc
	${CXX}  ${CXXFLAGS} -c $< -o $@ 

clean:
	rm -rf $(OBJS)
	rm -rf $(BIN_TARGET)
