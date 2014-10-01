#include "HashFunctions.h"

#define MAX_PASS_PART3 4
#define TABLE_LENGTH 456976
void recurse(char * pass, int index, int max);
int initArray(char** arr, int rows, int columns);
void mStrCpy(int size, char* dest, char* src);
char passwords[TABLE_LENGTH][MAX_PASS_PART3 + 1];
char hashes[TABLE_LENGTH][MAX_PASS_PART3 + 1];

int oPass()
{
	//allocate an initial password string
	char * p = (char*)calloc(MAX_PASS_PART3 + 1, sizeof(char));
	//set the last character to null terminator
	p[MAX_PASS_PART3] = 0;
	//call the recurse function to populate the entire dictionary with hashes and passwords
	recurse(p, 0, MAX_PASS_PART3);
	//take input of hashes to output passwords
	while (1){
		//allocate a string of the max username length
		char * hash = (char*)calloc(12, sizeof(char));
		printf("Enter a hash for a four character password, Type 0 to exit:\n");
		scanf("%10s", hash);
		char c;
		//flush additional characters
		do { c = getchar(); } while (c != '\n' && c != '\0');
		//flush the overflow
		fflush(stdin);
		//if the user entered 0, return -1 to signal the end of program
		if (strcmp("0", hash) == 0){
			return -1;
		}
		//if the length of the hash is not four, free the password memory and ask user to try again
		if (strlen(hash) != 4)
		{
			printf("This hash does not map to a four character long password.\nThe hash must also be four characters. Please try again.\n");
			free(hash);
			continue;
		}
		int i;
		int found = 0;
		//search the entire table for the input hash to output the plaintex password
		for (i = 0; i < TABLE_LENGTH; i++)
		{
			//if the table entry matches the input
			if (strcmp(hashes[i], hash) == 0)
			{
				//output the plaintext password
				printf("For the hash (%s), the password is: %s\n", hash, passwords[i]);
				found = 1;
				break;
			}
		}
		//if the hash was not found onthe table, inform the user.
		if (found == 0)
		{
			printf("For the hash (%s), no password was found.\n", hash);
		}
	}
	return 0;
}
int tablePosition = 0;
//populates all hashes for every possible password
void recurse(char * pass, int index, int max)
{
	//base case; after four characters have been put into the string, save that string on the table
	if (index >= max)
	{
		

		//copy the generated password onto the table
		strncpy(passwords[tablePosition], pass, 4);
		//hash the password
		char * hash = Hashify(1, pass);
		printf("%s : %s\n", pass, hash);
		//copy the hash into the table
		strncpy(hashes[tablePosition], hash, 4);
		//increment the table index position
		tablePosition++;
	}
	else
	{
		//at any given index of the word, cycle through every character from A - Z,
		//store that character in the string, and recurse into the next index of the word (and do the same)
		for (int i = 0; i < 26; i++)
		{
			char a = 'A' + i;
			pass[index] = a;
			recurse(pass, index + 1, max);
		}
	}
}