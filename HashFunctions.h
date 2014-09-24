//Visual Studio flags:
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)

//Assignment Consts
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 12
#define MAX_LOGIN_ATTEMPTS 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void strToUpper(char * str);
void E(char *in, char *out);
void Hashify(char * password);
int checkUserNameTable(const char * username, char usernames[MAX_USERS][MAX_USERNAME_LENGTH]);
char * enterPassword();
char * enterUsername();
void WriteToFile();
