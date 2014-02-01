#include "die.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define ACES 0
#define TWOS 1
#define THREES 2
#define FOURS 3
#define FIVES 4
#define SIXES 5
#define THREE_OF_KIND 6
#define FOUR_OF_KIND 7
#define FULL_HOUSE 8
#define SMALL_STRAIGHT 9
#define LARGE_STRAIGHT 10
#define YAHTZEE 11
#define CHANCE 12


int main(int argc, char const *argv[])
{	
	srand(time(0));
	/* code */

	fprintf(stdout, "Welcome to Yatzee!\n\n");

	//get input: n to start a new game, q to quit
	bool new_game = false;

	Die * die_1 = new Die();
	die_1->roll();
	int val = die_1->value;
	fprintf(stdout, "%d\n", val);


	fprintf(stdout, "Remaining slots:\n");
	int num_options = 13;
	
	const char * options[num_options];	//list of play options
	const char * sixes = "Sixes\t";
	const char * fives = "Fives\t";
	const char * fours = "Fours\t";
	const char * threes = "Threes\t";
	const char * twos = "Twos\t";
	const char * aces = "Aces\t";
	const char * three_of_kind = "Three-of-a-kind";
	const char * four_of_kind = "Four-of-a-kind";
	const char * five_of_kind = "Five-of-a-kind";
	const char * yahtzee = "Yahtzee\t";
	const char * full_house = "Full House";
	const char * small_straight = "Small Straight";
	const char * large_straight = "Large Straight";
	const char * chance = "Chance\t";
	options[0] = aces;
	options[1] = twos;
	options[2] = threes;
	options[3] = fours;
	options[4] = fives;
	options[5] = sixes;
	options[6] = three_of_kind;
	options[7] = four_of_kind;
	options[8] = full_house;
	options[9] = small_straight;
	options[10] = large_straight;
	options[11] = yahtzee;
	options[12] = chance;

//	fprintf(stdout, "%d\n", num_options);

	//for(int i = 0; i<num_options; i++ ){
//		fprintf(stdout, "%s\n", options[i]);
//	}

	bool played_option[13];
	played_option[ACES] = 1;
	played_option[TWOS] = 1;
	played_option[YAHTZEE] = 1;
	played_option[FULL_HOUSE] = 1;
	played_option[THREE_OF_KIND] = 1;
	played_option[SMALL_STRAIGHT] = 1;
	played_option[CHANCE] = 1;

	for(int i = 0; i<num_options; i++){
		fprintf(stdout, "%s\t\t", options[i]);
		if(played_option[i])
			fprintf(stdout, "%s\n\n", "*********");
		else
			fprintf(stdout, "%s\n\n", "available");
	}



	//if input is n, set new_game to true

	//do, while new_game = true;

	//game loop
		//initialize everything
		//print 'board'

		//turn loop
			//ask for user to roll
			//display roll
			//ask if user wants to roll again
				//if yes, ask what dice to keep
			//repeat
			//after 3rd roll, or user is done rolling, provide options for where to use that roll on the board
		//print new board (after update)
		//continue until out of spaces on board





	return 0;
}