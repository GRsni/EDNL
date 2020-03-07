all: main

CXX=g++

main: main.o 
	$(CXX) main.o -o abin.exe

main.o: main.cpp 
	$(CXX) -c main.cpp

Abin_din.o: Abin_din.hpp
	$(CXX) -c Abin_din.hpp

abin_E-S.o: abin_E-S.hpp
	$(CXX) -c abin_E-S.hpp

Oper_Abin.o: Oper_Abin.hpp
	$(CXX) -c Oper_Abin.hpp

clean:
	del main.exe *.o *.hpp.gch core *~
