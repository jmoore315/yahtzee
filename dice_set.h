#ifndef _DICE_SET_INCLUDED
#define _DICE_SET_INCLUDED

#include "die.h"

class DiceSet
{
public:
	DiceSet(int num_dice);
	~DiceSet();
	void roll_dice();
	void print_dice();
	void set_die(int n, int val);
	void deactivate_die(int n);
	Die * dice;
	int num_dice;
	int num_active_dice;
};

#endif