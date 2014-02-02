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

int DiceSet::value_of(int n){
	int score = 0;
	for (int i = 0; i < num_dice; i++){
		if (dice[i].value == n){
			score += n;
		}
	}
	return score;
}

int DiceSet::aces(){
	return value_of(1);
}

int DiceSet::twos(){
	return value_of(2);
}


int DiceSet::threes(){
	return value_of(3);
}

int DiceSet::fours(){
	return value_of(4);
}

int DiceSet::fives(){
	return value_of(5);
}

int DiceSet::sixes(){
	return value_of(6);
}

int DiceSet::three_of_kind(){
	int count = 0;
	for (int i = 0; i < 3; i++){
		int value = dice[i].value;
		count = 1;
		for(int j = i+1; j<num_dice; j++){
			if (dice[j].value == value){
				count++;
			}
		}
		if(count >= 3)
			return sum_dice();
	}
	return 0;
}

int DiceSet::four_of_kind(){
	int count = 0;
	for (int i = 0; i < 2; i++){
		int value = dice[i].value;
		count = 1;
		for(int j = i+1; j<num_dice; j++){
			if (dice[j].value == value){
				count++;
			}
		}
		if(count >= 4)
			return sum_dice();
	}
	return 0;
}
int DiceSet::yahtzee(){
	int count = 1;
	int value = dice[0].value;
	for(int i = 1; i<num_dice; i++){
		if (dice[i].value == value){
			count++;
		}
		else
			return 0;
	}
	return 50;
}

int DiceSet::full_house(){
	int three_num = three_of_kind()/3;	//0 if set does not include a 3 of a kind
	if (three_num){
		int two_num = 0;
		for(int i = 0; i < num_dice; i++){
			if(dice[i].value != three_num){
				if(!two_num)
					two_num = dice[i].value;
				else if (two_num != dice[i].value){
					//no pair present. return 0
					return 0;
				}
			}
		}
	}
	return 25;
}

int DiceSet::small_straight(){
	if(contains(4) && contains(3))
	{
		if((contains(5) && contains(6)) || (contains(1) && contains(2)) || (contains(2) && contains(5)))
			return 30;
	}
	return 0;
}

int DiceSet::large_straight(){
	if(small_straight()){
		if(contains(5) && contains(2)){
			if(contains(1) || contains(6)){
				return 40;
			}
		}
	}
	return 0;
}

bool DiceSet::contains(int val){
	for(int i = 0; i <num_dice; i++)
		if(dice[i].value == val)
			return true;
	return false;
}

int DiceSet::sum_dice(){
	int score = 0;
	for(int i=0; i<num_dice; i++){
		score += dice[i].value;
	}
	return score;

}