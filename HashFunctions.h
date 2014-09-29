//Visual Studio flags:
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)

//Assignment Consts, uname and pass length 1 greater to allow space for null byte.
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 33
#define MAX_PASSWORD_LENGTH 13
#define MAX_LOGIN_ATTEMPTS 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void strToUpper(char * str);
void E(char *in, char *out);
char * Hashify(int n, char * password);
int checkUserNameTable(const char * username, char usernames[MAX_USERS][MAX_USERNAME_LENGTH]);
char * enterPassword();
char * enterUsername();
void ReadFromFile(char usernames[MAX_USERS][MAX_USERNAME_LENGTH], char passwords[MAX_USERS][MAX_PASSWORD_LENGTH]);
void WriteToFile(char usernames[MAX_USERS][MAX_USERNAME_LENGTH], char passwords[MAX_USERS][MAX_PASSWORD_LENGTH], int usercount);

int olmHash();
int clientResponseAuth();
int oPass();