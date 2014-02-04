#ifndef _DICE_SET_INCLUDED
#define _DICE_SET_INCLUDED

#include "die.h"
#include "preprocessor.h"

class DiceSet
{
public:
	DiceSet(int num_dice);
	~DiceSet();

	Die * dice;
	bool eligible_plays[NUM_OPTIONS];
	int play_values[NUM_OPTIONS];
	int num_dice;
	int num_active_dice;


	void roll_dice();
	void print_dice();
	void set_die(int n, int val);
	void deactivate_die(int n);

	//the following functions return 0 if dice set does not fit the category, returns the score if it does
	int aces();
	int twos();
	int threes();
	int fours();
	int fives();
	int sixes();
	int three_of_kind();
	int four_of_kind();
	int yahtzee();
	int full_house();
	int small_straight();
	int large_straight();

private:
	int value_of(int);	//returns total value of a number 1..6 in the dice set
	bool contains(int);	//returns true if dice set contains a die with specified value
	int sum_dice();
	void get_eligible_plays();

};

#endif