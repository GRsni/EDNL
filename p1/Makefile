all: main
CXX=g++

main: main.o Abin_din.o abin_E-S.o Oper_Abin.o
	$(CXX) main.o Abin_din.o abin_E-S.o Oper_Abin.o -o abin.exe

main.o: main.cpp Abin_din.h abin_E-S.h Oper_Abin.h
	$(CXX) -c main.cpp Abin_din.h abin_E-S.h Oper_Abin.h
