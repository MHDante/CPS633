
#include "HashFunctions.h"

#define MAX_PASS_PART3 4
#define TABLE_LENGTH 456976
//#define TABLE_LENGTH 676 
//26 ^ 4
//void handleNewUser2(const char * username);
//void handleExistingUserCRA(const char * username, int usernameIndex);
//char * generateRandXOR(char* hash, int r);
//void R(char* in, char* out, int r);
//void populateHashes();
//void traverseHashes();
//void recurse(char ** passwords, char** hashes, char * pass, int index, int max);
void recurse(char * pass, int index, int max);
int initArray(char** arr, int rows, int columns);
void mStrCpy(int size, char* dest, char* src);

//int table_length;

char passwords[TABLE_LENGTH][MAX_PASS_PART3 + 1];
char hashes[TABLE_LENGTH][MAX_PASS_PART3 + 1];

int mainx()
{
	
	char * p = (char*)calloc(MAX_PASS_PART3 + 1);
	p[MAX_PASS_PART3] = 0;
	printf("Writing pass:%s\n", p);

	recurse(p, 0, MAX_PASS_PART3);
	while (1){
		//allocate a string of the max username length
		char * hash = (char*)calloc(sizeof(char)*MAX_PASSWORD_LENGTH);
		printf("Enter a hash for a four digit password, Type 0 to exit:\n");
		char format[80];
		//create format string for reading in the max length
		sprintf(format, "%%%ds", MAX_PASSWORD_LENGTH);
		//use that format string to read name
		scanf(format, hash);
		//flush the overflow
		fflush(stdin);
		//if the user entered 0, return -1 to signal the end of program
		if (strcmp("0", hash) == 0){
			return -1;
		}
		int i;
		for (i = 0; i < MAX_PASSWORD_LENGTH; i++)
		{

		}
	}


	return 0;
}
//int depth = 0;
int tablePosition = 0;
//void recurse(char ** passwords, char** hashes, char * pass, int index, int max)
void recurse(char * pass, int index, int max)
{
	//depth++;
	//printf("%d\n",depth);
	if (index >= max)
	{
		//printf("%d,", tablePosition);
		//printf("%s\n", pass);
		//char* newPass = (char*)malloc(max+1);
		//6473839666
		mStrCpy(4,passwords[tablePosition], pass);
		//passwords[tablePosition] = newPass;
		//calculuate hash and throw in table
		//char* temp = (char*)calloc(max + 1);
		//mStrCpy(4, temp, pass);
		char * hash = Hashify(1, pass);
		//char* newHash = (char*)malloc(max + 1);

		mStrCpy(4, hashes[tablePosition], hash);

		printf("Writing pass:%s   hash:%s    pos:%d\n", pass, hash, tablePosition);
		//hashes[tablePosition] = hash;
		tablePosition++;
	}
	else
	{
		for (int i = 0; i < 26; i++)
		{
			char a = 0; 'A' + i;
			pass[index] = a;
			//recurse(passwords, hashes, pass, index + 1, max);
			recurse(pass, index + 1, max);
		}
	}
	//depth--;
}
//void traverseHashes()
//{
//	for (int i = 0; i < MAX_PASS_PART3; i++)
//	{
//		printf("%s : %s\n", passwords[i], hashes[i]);
//	}
//}

int initArray(char** arr, int rows, int columns)
{
	if ((arr = (char**)malloc(sizeof(char*) * rows)) == NULL)
	{
		printf("Damn.");
		return -1;
	}
	for (int i = 0; i < rows; i++)
	{
		if ((arr[i] = (char*)malloc(sizeof(char)*columns)) == NULL){
			printf("Damn^2.");
			for (; i > 0; i--)
			{
				free(arr[i]);
			}
			free(arr);
			return -1;
		}
	}
	return 1;
}

void mStrCpy(int size, char* dest, char* src){
	int i;
	for (i = 0; i < size; i++){
		dest[i] = src[i];
		if (src[i] == 0) break;
	}
	src[i] = 0;
}