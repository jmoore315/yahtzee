#include "dice_set.h"
#include <stdio.h>

DiceSet::DiceSet(int num_dice){
	this->num_dice = num_dice;
	dice = new Die[num_dice];
	for (int i = 0; i < num_dice; i++)
	{
		dice[i].value = 0;
	}
}

DiceSet::~DiceSet(){
	for(int i = 0; i < num_dice; i++){
		delete[] dice;
	}
}

void DiceSet::roll_dice(){
	for(int i = 0; i < num_dice; i++){
		if(dice[i].value == 0)
			dice[i].roll();
	}
}

void DiceSet::print_dice(){
	printf("Die:\t");
	for(int i = 1; i<=num_dice; i++)
		printf("|  %d  ", i);
	printf("\n______________________________________");
	printf("\nValue:\t");
	for(int i = 0; i<num_dice; i++)
		printf("|  %d  ", dice[i].value);
	printf("\n\n");
}

void DiceSet::set_die(int n, int val){
	dice[n].value = val;
}

void DiceSet::deactivate_die(int n){
	dice[n].value = 0;
}