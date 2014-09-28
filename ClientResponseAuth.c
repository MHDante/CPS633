
#include "HashFunctions.h"


void handleNewUser2(const char * username);

void handleExistingUserCRA(const char * username, int usernameIndex);
char * generateRandXOR(char* hash, int r);
void R(char* in, char* out, int r);

char usernames[MAX_USERS][MAX_USERNAME_LENGTH];
char passwords[MAX_USERS][MAX_PASSWORD_LENGTH];
int attempts[MAX_USERS];
int currentUserAmount2 = 0;

int main3()
{
	srand(time(NULL));
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
			handleExistingUserCRA(name, usernameIndex);
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
	char * hash = Hashify(3, pw);
	//place the new user on the table with username and hashed password
	strcpy(usernames[currentUserAmount2], username);
	strcpy(passwords[currentUserAmount2], hash);
	//point to the next free spot on the table
	currentUserAmount2++;
	printf("User was added to the table!\n\n");
}

void handleExistingUserCRA(const char * username, int usernameIndex)
{
		printf("Enter your password:\n");
		//ask user to enter old password and check hash against stored hash in table
		char * pw = enterPassword();

		//int* a = (int*)pw;
		//printf("pw = %s\n", pw);
		//printf("*a = %d\n", *a);

		//hash entered password
		char * hash = Hashify(3, pw);
		//generates random number "on server side"
		int r = rand();
		//calculates new hash with number from server "on client side" and sends back to server
		char* clientOut = generateRandXOR(hash, r);
		//also calculates the xor'd number "on server side"
		char* serverOut = generateRandXOR(passwords[usernameIndex], r);

		//compare the the two xor'd password hashes "on server side"
		int cmp = strcmp(clientOut, serverOut);
		//if they are a match (correct password)
		if (cmp == 0)
		{
			printf("access granted\n");
		}
		else
		{
			printf("access denied\n");
		}

}
//xor the hash with the server's random number
char * generateRandXOR(char* hash, int r)
{
	char * out = (char*)calloc(sizeof(char) * MAX_PASSWORD_LENGTH);
	R(hash, out, r);
	R(&hash[4], &out[4], r);
	R(&hash[8], &out[8], r);
	return out;
}
//xor function for each bundle (4 bytes)
void R(char* in, char* out, int r)
{
	char rr = r;
	out[3] = in[3] ^ (r & 255);
	r = r >> 8;
	out[2] = in[2] ^ (r & 255);
	r = r >> 8;
	out[1] = in[1] ^ (r & 255);
	r = r >> 8;
	out[0] = in[0] ^ (r & 255);
}




//0010110101
//1101011001
//			&
//1111101100