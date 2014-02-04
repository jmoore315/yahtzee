#include "dice_set.h"
#include "preprocessor.h"
#include "cstring"
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
	get_eligible_plays();
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
	if(eligible_plays[YAHTZEE]){
		printf("\nCongrats, you got a yahtzee!\n\n");
	}
}

void DiceSet::set_die(int n, int val){
	dice[n].value = val;
}

void DiceSet::deactivate_die(int n){
	dice[n].value = 0;
}

void DiceSet::get_eligible_plays(){
	memset(eligible_plays, 0, NUM_OPTIONS);

	if(play_values[ACES] = aces())
		eligible_plays[ACES] = true;
	if(play_values[TWOS] = twos())
		eligible_plays[TWOS] = true;
	if(play_values[THREES] = threes())
		eligible_plays[THREES] = true;
	if(play_values[FOURS] = fours())
		eligible_plays[FOURS] = true;
	if(play_values[FIVES] = fives())
		eligible_plays[FIVES] = true;
	if(play_values[SIXES] = sixes())
		eligible_plays[SIXES] = true;
	if(play_values[THREE_OF_KIND] = three_of_kind())
		eligible_plays[THREE_OF_KIND] = true;
	if(play_values[FOUR_OF_KIND] = four_of_kind())
		eligible_plays[FOUR_OF_KIND] = true;
	if(play_values[YAHTZEE] = yahtzee())
		eligible_plays[YAHTZEE] = true;
	if(play_values[SMALL_STRAIGHT] = small_straight())
		eligible_plays[SMALL_STRAIGHT] = true;
	if(play_values[LARGE_STRAIGHT] = large_straight())
		eligible_plays[LARGE_STRAIGHT] = true;
	if(play_values[FULL_HOUSE] = full_house())
		eligible_plays[FULL_HOUSE] = true;
	play_values[CHANCE] = sum_dice();
	eligible_plays[CHANCE] = true;

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
		if (value == 0)
			continue;
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
		if(value == 0)
			continue;
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
	if(value==0)
		return 0;
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
	if (eligible_plays[THREE_OF_KIND]){
		int val1 = 0;
		int count1 = 0;
		int val2 = 0;
		int count2 = 0;
		for(int i = 0; i < num_dice; i++){
			int current_val = dice[i].value;
			if(current_val == 0)
				return false;
			if(!val1){
				val1 = current_val;
				count1++;
			}
			else if (current_val == val1){
				count1++;
			}
			else if (!val2){
				val2 = current_val;
				count2++;
			}
			else if (current_val == val2){
				count2++;
			}
			else
				return 0;
		}
		if (((count1 == 2) && (count2 == 3)) || ((count1 == 3) && (count2 == 2)))
			return 25;
	}
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