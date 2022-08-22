#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void read_flag(){
	FILE * fp;
	char flag[30] = {0,};
	fp = fopen("./flag", "r");
	fgets(flag, 30, fp);
	printf("flag: %s\n", flag);
	fclose(fp);
}

void login(){
	int password;
	int password2;

	printf("enter password : ");
	scanf("%d", password);
	fflush(stdin);

	printf("enter password again : ");
	scanf("%d", password2);
	fflush(stdin);

	printf("check the password\n");
	if(password==3333333 && password2==3333333){
		printf("Login Success!\n");
		read_flag();
	}
	else{
		printf("Login Failed!\n");
		exit(0);
	}
}

void get_id(){
	char name[100];
	printf("enter your id : ");
	scanf("%s", name);
	printf("Welcome %s!\n", name);
}

int main(){
	setreuid(geteuid(), geteuid());
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

	printf("Simple login system.\n");
	get_id();
	login();

	return 0;
}