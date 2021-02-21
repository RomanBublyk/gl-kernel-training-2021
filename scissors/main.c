#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scissors.h"

int main(int argc, char **argv){
	char choices[] = {'r', 'p', 's'};
	char user_choice;
	char full_user_choice[9];
	char full_program_choice[9];
	srand(time(0));
	char program_choice = choices[rand() % 3];
	printf("> Please choose: rock (r) - paper (p) - scissors (s)\n");
	printf("> ");
	scanf("%c", &user_choice);

	if(char2name(user_choice, full_user_choice) < 0){
		printf("> An unused character was entered. "\
			"The game did not take place.\n");
		return 0;
	}

	program_choice = choices[rand() % 3];

	char2name(program_choice, full_program_choice);

	printf("> You choose %s, I choose %s\n", full_user_choice,
	       full_program_choice);

	if(user_choice == program_choice){
		printf("> Draw\n");
	} else if(user_choice == 'r'){
		if(program_choice == 'p'){
			printf("> I win: %s beats %s\n", full_program_choice,
			       full_user_choice);
		} else {
			printf("> You win: %s beats %s\n", full_user_choice,
			       full_program_choice);
		}
	} else if(user_choice == 'p'){
		if(program_choice == 's'){
			printf("> I win: %s beats %s\n", full_program_choice,
			       full_user_choice);
		} else {
			printf("> You win: %s beats %s\n", full_user_choice,
			       full_program_choice);
		}
	} else {
		if(program_choice == 'r'){
			printf("> I win: %s beats %s\n", full_program_choice,
			       full_user_choice);
		} else {
			printf("> You win: %s beats %s\n", full_user_choice,
			       full_program_choice);
		}
	}

	return 0;
}
