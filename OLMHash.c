#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 12
#define MAX_LOGIN_ATTEMPTS 3

char usernames[MAX_USERS][MAX_USERNAME_LENGTH];
char passwords[MAX_USERS][MAX_PASSWORD_LENGTH];
int attempts[MAX_USERS];

int currentUserAmount = 0;

void E(char *in, char *out);
void Hashify(char * password);

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

int main()
{
	while (1){
		int entryCount = 0;
		char name[MAX_USERNAME_LENGTH];
		while (1)
		{
			printf("Enter your username:\n");
			char format[80];
			sprintf(format, "%%%ds", MAX_USERNAME_LENGTH);
			scanf(format, &name);
			fflush(stdin);
			if (strlen(name) < 4)
			{
				printf("Username must be at least 4 characters.\n");
				memset(name, 0, sizeof(char) * MAX_USERNAME_LENGTH);
			}
			else
			{
				break;
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

void strToUpper(char * str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}


void Hashify(char * password){
	strToUpper(password);
	E(password, password);
	E(&password[4], &password[4]);
	E(&password[8], &password[8]);
}

/********************* E function *************************/
// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out)
{
	out[0] = (in[0] & 0x80) ^ (((in[0] >> 1) & 0x7F) ^ ((in[0]) & 0x7F));
	out[1] = ((in[1] & 0x80) ^ ((in[0] << 7) & 0x80)) ^ (((in[1] >> 1) & 0x7F) ^ ((in[1]) & 0x7F));
	out[2] = ((in[2] & 0x80) ^ ((in[1] << 7) & 0x80)) ^ (((in[2] >> 1) & 0x7F) ^ ((in[2]) & 0x7F));
	out[3] = ((in[3] & 0x80) ^ ((in[2] << 7) & 0x80)) ^ (((in[3] >> 1) & 0x7F) ^ ((in[3]) & 0x7F));
}

