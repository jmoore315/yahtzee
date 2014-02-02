Yhatzee: main.o die.o dice_set.o
	g++ main.o die.o dice_set.o -o Yhatzee

main.o: main.cc die.h dice_set.h
	g++ -c main.cc

die.o: die.cc die.h
	g++ -c die.cc

dice_set.o: dice_set.cc dice_set.h die.h
	g++ -c dice_set.cc