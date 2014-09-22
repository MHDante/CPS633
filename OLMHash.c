#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include "HashFunctions.h"

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 12
#define MAX_LOGIN_ATTEMPTS 3

void handleNewUser(const char * username);

void handleExistingUser(const char * username, int usernameIndex);

int checkUserNameTable(const char * username);

char * enterPassword();

char * enterUsername();

void WriteToFile();

char usernames[MAX_USERS][MAX_USERNAME_LENGTH];
char passwords[MAX_USERS][MAX_PASSWORD_LENGTH];
int attempts[MAX_USERS];
int currentUserAmount = 0;

int main()
{
	while (1){
		//Checks for initial input (a username), when a valid input is given, the program proceeds.
		char * name = 0;
		while (name == 0){
			//attemps to get another valid username from the user
			name = enterUsername();
			//if user enters 0, we write the tables to file and exit the program
			if (name == -1) {
				WriteToFile();
				return 0;
			}
		}
			
		//with the inputted username, we check if it exist in the table (and retrieve the index of the table if so)
		int usernameIndex = checkUserNameTable(name);
		//if the username was not found on the table
		if (usernameIndex == -1)
		{
			handleNewUser(name);
		} 
		//if the username was already found on the table
		else 
		{
			handleExistingUser(name, usernameIndex);
		}
	}
	return 0;
}
void handleNewUser(const char * username)
{
	//ask user to enter new password for new user account
	printf("User not found; Created user; Enter new user password:\n");
	char * pw = enterPassword();
	//hash the entered password
	Hashify(pw);
	//place the new user on the table with username and hashed password
	strcpy(usernames[currentUserAmount], username);
	strcpy(passwords[currentUserAmount], pw);
	//point to the next free spot on the table
	currentUserAmount++;
	printf("User was added to the table!\n\n");
}
void handleExistingUser(const char * username, int usernameIndex)
{
	//asks for user's password until they have exceeded their maximum login attempts
	while (attempts[usernameIndex] < MAX_LOGIN_ATTEMPTS)
	{
		printf("Enter your password:\n");
		//ask user to enter old password and check hash against stored hash in table
		char * pw = enterPassword();
		//hash entered password
		Hashify(pw);
		//compare the entered hashed password against the hash saved in the table
		int cmp = strcmp(pw, passwords[usernameIndex]);
		//if they are a match (correct password)
		if (cmp == 0)
		{
			//reset the password attempts of that user
			attempts[usernameIndex] = 0;
			//prompt user for new password
			printf("User Authenticated, Enter new password:\n");
			char * npw = enterPassword();
			//hash the new password
			Hashify(npw);
			//store it in the table
			strcpy(passwords[usernameIndex], npw);
			printf("User's password was updated!\n\n");
			break;
		}
		//increment user's attempts to enter password and try again
		printf("Incorrect password, please try again:!\n");
		attempts[usernameIndex]++;
	}
	//if the user has exceeded their maximum login attempts, their account is locked and no more attempts are given
	if (attempts[usernameIndex] >= MAX_LOGIN_ATTEMPTS){
		printf("User Account Locked, please contact SysAdmin at ENG-246.\n\n");
	}
}

//check for the index of the username in the table
int checkUserNameTable(const char * username)
{
	int i;
	//for every username in the table
	for (i = 0; i < MAX_USERS; i++)
	{
		//if the usernames are equal, return the index
		int cmp = stricmp(username, usernames[i]);
		if (cmp == 0)
		{
			return i;
		}
	}
	//if username was not found, return -1 indicating so
	return -1;
}
//read input from user as a password with a maximum length
char * enterPassword()
{
	//allocate a string
	char * password = (char *)calloc(sizeof(char) * MAX_PASSWORD_LENGTH);
	char format[80];
	//create a format string that will only accept up to the maximum password length
	sprintf(format, "%%%ds", MAX_PASSWORD_LENGTH);
	//use that format string to read the password in from the user
	scanf(format, password);
	return password;
}
//read input from user as a username with a max and min length
char * enterUsername()
{
	//allocate a string of the max username length
	char * name = (char*)calloc(sizeof(char)*MAX_USERNAME_LENGTH);
	printf("Enter your username, Type 0 to exit:\n");
	char format[80];
	//create format string for reading in the max length
	sprintf(format, "%%%ds", MAX_USERNAME_LENGTH);
	//use that format string to read name
	scanf(format, name);
	//flush the overflow
	fflush(stdin);
	//if the user entered 0, return -1 to signal the end of program
	if (strcmp("0", name) == 0){
		return -1;
	}
	//if the name is less than 4 characters, free the memory and return 0 to indicate the input was invalid
	if (strlen(name) < 4)
	{
		printf("Username must be at least 4 characters.\n");
		free(name);
		return 0;
	}
	//return the valid username
	else
	{
		return name;
	}
}

void WriteToFile(){
	//TODO: Write the Grid to a file.
}



