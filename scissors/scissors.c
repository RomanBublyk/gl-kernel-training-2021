#include "scissors.h"

int char2name(char choice, char *full_choice){
	switch(choice){
		case 'r':
			strcpy(full_choice, "rock");
			return 0;
		case 'p':
			strcpy(full_choice, "paper");
			return 1;
		case 's':
			strcpy(full_choice, "scissors");
			return 2;
		default:
			return -1;
	}
}
