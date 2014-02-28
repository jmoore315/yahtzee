#include "die.h"
#include "dice_set.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include "preprocessor.h"
#include <ctype.h>

void print_options(char * options[], bool played_option[]);
char * get_input (char *s, size_t n);
void clear_screen();
void reset_game(bool played_option[], int * score);
void print_game(char * options[], bool played_option[], int score);
void get_open_plays(DiceSet * current_dice, bool played_option[], bool * open_plays);
void print_available_options(char * options[], bool open_plays[], int values[]);
int count_open_plays(bool open_plays[]);
bool is_number(char *s, int len);

int main(int argc, char const *argv[])
{	
	//initialization
	srand(time(0));
	int turn = 0;
	int roll = 0;

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
	
	const char * options[NUM_OPTIONS];	//list of play options
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

	bool new_game = false;
	bool bad_input;
	int score;
	bool played_option[NUM_OPTIONS];	//array element is true if option has been played
	DiceSet * played_dice[NUM_OPTIONS];

	char input[BUFFER_LENGTH];	//buffer for user input
	//char * input_p;
	int input_length;

	//print instructions
	clear_screen();
	printf("Welcome to Yatzee!\n\n");
	

	//get user input
	bad_input = true;
	do{
		printf("Enter 'n' for a new game, 'q' anytime to quit.\n");
		get_input(input, BUFFER_LENGTH);
		clear_screen();
		input_length = strlen(input);
		if(input_length == 1){
			if(input[0] == 'n'){
				//call newgame
				reset_game(played_option, &score);
				bad_input = false;
			}
			if(input[0] == 'q'){
				printf("\nThanks for playing. cy@\n");
				exit(-1);
			}
		}
	}while(bad_input);
	clear_screen();
	//new game:
	turn = 1;
	while(turn <= 13 ){
		//print_game((char **) options, played_option, score);
		bad_input = true;
		do{
			printf("Input 'roll' to begin a new turn by rolling the dice, 'info' to show your current board, 'n' to start a new game, or 'q' to quit.\n\n");
			get_input(input, BUFFER_LENGTH);
			clear_screen();
			input_length = strlen(input);
			if(input_length == 1){
				if(input[0] == 'n'){
					//call newgame
					reset_game(played_option, &score);
					//bad_input = false;
				}
				if(input[0] == 'q'){
					printf("\nThanks for playing. cy@\n");
					exit(-1);
				}
			}
			else if(input_length == 4){
				if(strcmp(input, "roll") == 0){
					//new turn
					bad_input = false;
				}
				if(strcmp(input, "info") == 0){
					//print board
					print_game((char **) options, played_option, score);

				}

			}

		}while(bad_input);
		clear_screen();

		//new turn
		roll = 1;
		int dice_to_roll = 5;
		DiceSet * current_dice = new DiceSet(5);
		clear_screen();
		printf("rolling.......\n");
		sleep(1);
		clear_screen();
		current_dice->roll_dice();
		printf("First Roll:\n");
		current_dice->print_dice();
		while(roll < 3){


			do{
				printf("Do you want to roll some dice again? Enter 'y' to roll again or 'n' to keep this roll.\n");
				get_input(input, BUFFER_LENGTH);
				clear_screen();
				input_length = strlen(input);
				if(input_length == 1){
					if(input[0] == 'y'){
						//get dice to keep
						bad_input = false;
					}
					if(input[0] == 'n'){
						bad_input = false;
					}
				}
			}while(bad_input);
			if(input[0] == 'y'){
				roll++;
				//get dice to keep
				//printf("Enter which dice to roll again (number) separated by spaces.\n");
				//to be implemented later, for now just re-roll all dice
				for(int i = 0; i<5; i++)
					current_dice->dice[i].value = 0;
				current_dice->roll_dice();
				clear_screen();
				printf("rolling.......\n");
				sleep(1);
				clear_screen();
				if(roll == 2)
					printf("Second Roll:\n");
				else
					printf("Final Roll: \n");
				current_dice->print_dice();
			}
			else{
				current_dice->print_dice();
				break;
			}
		}

		//User selects which option to play with the roll
		bool open_plays[NUM_OPTIONS];
		get_open_plays(current_dice, played_option, open_plays);
		int open_plays_count = count_open_plays(open_plays);
		int play;
		if(open_plays_count > 0){
			print_available_options((char **) options, open_plays, current_dice->play_values);
			printf("Where would you like to play this roll? Enter the number of the option.\n\n");
			bad_input = true;
			while(bad_input){
				get_input(input, BUFFER_LENGTH);
				input_length = strlen(input);
				if((input_length != 2 && input_length != 1) || !is_number(input, input_length)) {
					printf("Bad input. Please enter the number of the option you'd like to play.\n");
				}
				else{
					play = atoi(input);
					//check to make sure input number is valid
					if(play >= 1 && play <= open_plays_count){
						printf("You selected option %d\n", play); 
						bad_input = false;
					}
					else{
						printf("Bad input. Please enter the number of the option you'd like to play.\n");
					}
				}
			}	
		}
		else{
			printf("There are no available plays for your roll...sorry!\n\n");
		}
		



		


		//new turn
			//3 rolls (max) per turn, though user can stop rolling before 3 rolls
			//on each roll user decides if they want to roll again
				//if they want to roll again they choose dice they want to keep
				//the dice they keep are stored in current_turn array
				//make a new dice_set for the number of dice still needed to roll
			//repeat
			//after 3rd roll, or user stop, the user can choose where to play the roll
			//display available options
			//get user input for which spot to put it
			//calculate spot based on user input
			//associate the dice set with that particular option
			//calculate score
			//end turn
		turn++;

	}
	
	

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

//possibly change this to print available options, since including a different method to print screen
void print_options(char * options[], bool played_option[]){
	for(int i = 0; i<NUM_OPTIONS; i++){
		printf("%s\t\t", options[i]);
		if(played_option[i])
			printf("%s\n\n", "*********");
		else
			printf("%s\n\n", "available");
	}
}

void print_available_options(char * options[], bool open_plays[], int values[]){
	printf("Available options:\n");
	int count = 1;
	for(int i = 0; i<NUM_OPTIONS; i++){
		if(open_plays[i]){
			printf("%d)\t", count);
			printf("%s\t\t", options[i]);
			printf("%d points\n\n", values[i]);
			count++;
		}
	}
}

int count_open_plays(bool open_plays[]){
	int count = 0;
	for(int i = 0; i<NUM_OPTIONS; i++){
		if(open_plays[i])
			count++;
	}
	return count;
}

char * get_input (char *s, size_t n){
	char *p = fgets (s, n, stdin);
	if (p != NULL){
		size_t last = strlen(s) - 1;
		if(s[last] == '\n')
			s[last] = '\0';
	}
	return p;
}

void clear_screen(){
	system("clear");
	//for(int i = 0; i<60; i++){
	//	fprintf(stdout, "\n");
	//}
}

void reset_game(bool played_option[], int * score){
	for (int i = 0; i < NUM_OPTIONS; i++){
		played_option[i] = 0;
	}
	*score = 0;
	printf("New Game:\n");
} 

void print_game(char * options[], bool played_option[], int score){
	int i, j;
	clear_screen();
	printf("Current game info:\n\n");
	j = 0;
	for(i = 0; i<NUM_OPTIONS; i++){
		printf("%s\t\t", options[i]);
		if(played_option[i]){
			j++;
			printf("%s\n\n", "*********");
		}
		else
			printf("%s\n\n", "available");
	}
	printf("\n**********************************\n");
	printf("Score: %d\n", score);
	printf("Remaining turns: %d\n", NUM_OPTIONS - j);
	printf("**********************************\n\n");
}

void get_open_plays(DiceSet * current_dice, bool played_option[], bool * open_plays){
	bool * eligible_plays = current_dice->eligible_plays; 
	for (int i = 0; i < NUM_OPTIONS; ++i)
	{
		open_plays[i] = !played_option[i] && eligible_plays[i];
	}

}

bool is_number(char *s, int len){
	for (int i = 0; i<len; i++){
		if(!isdigit(s[i]))
			return false;
	}
	return true;
}
