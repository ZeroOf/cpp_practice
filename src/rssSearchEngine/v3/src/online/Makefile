INC_DIR:= ../../inc
SRCS:=$(wildcard ./*.cpp) $(wildcard ./*.cc)
LIBS:= -lpthread -ljson 

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:=./test_server.exe

$(EXE):$(SRCS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
