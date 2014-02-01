Yhatzee: main.o die.o
	g++ main.o die.o -o Yhatzee

mian.o: main.cc die.h
	g++ -c main.cc

die.o: die.cc die.h
	g++ -c die.cc