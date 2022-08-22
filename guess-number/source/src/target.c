#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

void read_flag(){
	int fd = 0;
	char flag[30];
	fd = open("flag", O_RDONLY);
	read(fd, flag, 30);
	close(fd);
	printf("flag: i don't know\n");
}

void correct_answer(){
	char name[0x100];
	memset(name, 0, 0x100);

	puts("what is your name?\n");
	read(0, name, 0x100);
	write(1, name, 0x100);

	puts("You are a prophet\n");
	puts("Congradulation!");
	return ;
}

bool game_start(){
	char guess[0x20];
	int rand;

	memset(guess, 0, 0x20);
	printf("Give 3 chance\n");

	printf("What is the number? (1st chance) :\n");
	read(0, guess, 0x500);

	if(rand == guess){
		correct_answer();
		return true;
	}

	printf("What is the number? (2sd chance) :\n");
	read(0, guess, 0x500);

	if(rand == guess){
		correct_answer();
		return true;
	}

	printf("What is the number? (3rd chance) :\n");
	read(0, guess, 0x500);

	if(rand == guess){
		correct_answer();
		return true;
	}
	printf("round end ...)\n");
	return false;
}

void game(){
	while(true){
		if(game_start()==true){
			printf("You find the answer!\n");
			printf("This is the flag!\n");
			read_flag();
		}
		else{
			sleep(1);
		}
	}
}

int main(){
	setreuid(geteuid(), geteuid());
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

	printf("Guess my number\n");
	printf("There are many chances to guess.\n");
	game();

	return 0;
}