#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include "HashFunctions.h"

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 12
#define MAX_LOGIN_ATTEMPTS 3

char usernames[MAX_USERS][MAX_USERNAME_LENGTH];
char passwords[MAX_USERS][MAX_PASSWORD_LENGTH];
int attempts[MAX_USERS];

int currentUserAmount = 0;


int checkUserNameTable(const char * username);

char * enterPassword();

char * enterUsername();

void WriteToFile();

int main()
{
	while (1){
		int entryCount = 0;


		char * name = 0;
		while (name == 0){
			name = enterUsername();
			if (name == -1) {
				WriteToFile();
				return 0;
			}
		}
			

		int usernameIndex = checkUserNameTable(name);
		if (usernameIndex == -1)
		{
			//ask user to enter new password for new user account

			printf("User not found; Created user; Enter new user password:\n");
			char * pw = enterPassword();
			//printf("NEW PASS: %s\n", pw);
			Hashify(pw);

			//char*usrname = (char*)calloc(sizeof(char)*MAX_USERNAME_LENGTH);
			strcpy(usernames[currentUserAmount], name);
			strcpy(passwords[currentUserAmount], pw);

			currentUserAmount++;
			printf("User was added to the table!\n\n"); 
		} else {
			while (attempts[usernameIndex] < MAX_LOGIN_ATTEMPTS)
			{
				printf("Enter your password:\n");
				//ask user to enter old password and check hash against stored hash in table
				char * pw = enterPassword();
				Hashify(pw);
				
				int cmp = strcmp(pw, passwords[usernameIndex]);
				
				if (cmp == 0)
				{
					attempts[usernameIndex] = 0;
					printf("User Authenticated, Enter new password:\n");
					char * npw = enterPassword();
					Hashify(npw);
					strcpy(passwords[usernameIndex], npw);
					printf("User's password was updated!\n\n");
					break;
				}
				
				printf("Incorrect password, please try again:!\n");
				attempts[usernameIndex]++;
			}

			if (attempts[usernameIndex] >= MAX_LOGIN_ATTEMPTS){
				printf("User Account Locked, please contact SysAdmin at ENG-246.\n\n");
			}
			
		}


		//printf("%s\n", str);
		
	}
	return 0;
}

int checkUserNameTable(const char * username)
{
	int i;
	//todo: keep track of current user amount
	for (i = 0; i < MAX_USERS; i++)
	{
		int cmp = stricmp(username, usernames[i]);
		if (!cmp)
		{
			return i;
		}
	}
	return -1;
}
char * enterPassword()
{
	char * password = (char *)calloc(sizeof(char) * MAX_PASSWORD_LENGTH);
	char format[80];

	sprintf(format, "%%%ds", MAX_PASSWORD_LENGTH);
	scanf(format, password);
	return password;
}
char * enterUsername()
{
	char * name = (char*)calloc(sizeof(char)*MAX_USERNAME_LENGTH);
	printf("Enter your username, Type 0 to exit:\n");
	char format[80];
	sprintf(format, "%%%ds", MAX_USERNAME_LENGTH);
	scanf(format, name);
	fflush(stdin);
	if (strcmp("0", name) == 0){
		return -1;
	}
	if (strlen(name) < 4)
	{
		printf("Username must be at least 4 characters.\n");
		//memset(name, 0, sizeof(char) * MAX_USERNAME_LENGTH);
		free(name);
		return 0;
	}
	else
	{
		return name;
	}
}

void WriteToFile(){
	//TODO: Write the Grid to a file.
}



