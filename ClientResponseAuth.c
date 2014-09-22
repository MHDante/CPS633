
#include "HashFunctions.h"

void handleNewUser2(const char * username);

//void handleExistingUser(const char * username, int usernameIndex);

char usernames[MAX_USERS][MAX_USERNAME_LENGTH];
char passwords[MAX_USERS][MAX_PASSWORD_LENGTH];
int attempts[MAX_USERS];
int currentUserAmount2 = 0;

int main2()
{
	while (1){
		//Checks for initial input (a username), when a valid input is given, the program proceeds.
		char * name = 0;
		while (name == 0)
		{
			//attemps to get another valid username from the user
			name = enterUsername();
			//if user enters 0, we write the tables to file and exit the program
			if (name == -1) {
				WriteToFile();
				return 0;
			}
		}

		//with the inputted username, we check if it exist in the table (and retrieve the index of the table if so)
		int usernameIndex = checkUserNameTable(name, usernames);
		//if the username was not found on the table
		if (usernameIndex == -1)
		{
			handleNewUser2(name);
		}
		//if the username was already found on the table
		else
		{
			//handleExistingUser(name, usernameIndex);
		}
	}
	return 0;
}
void handleNewUser2(const char * username)
{
	//ask user to enter new password for new user account
	printf("User not found; Created user; Enter new user password:\n");
	char * pw = enterPassword();
	//hash the entered password
	Hashify(pw);
	//place the new user on the table with username and hashed password
	strcpy(usernames[currentUserAmount2], username);
	strcpy(passwords[currentUserAmount2], pw);
	//point to the next free spot on the table
	currentUserAmount2++;
	printf("User was added to the table!\n\n");
}
/*
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
}*/