#include "HashFunctions.h"

void strToUpper(char * str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
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
void Hashify(char * password){
	strToUpper(password);
	E(password, password);
	E(&password[4], &password[4]);
	E(&password[8], &password[8]);
}

//check for the index of the username in the table
int checkUserNameTable(const char * username, char usernames[MAX_USERS][MAX_USERNAME_LENGTH])
{
	int i;
	//for every username in the table
	for (i = 0; i < MAX_USERS; i++)
	{
		//if the usernames are equal, return the index
		int cmp = strcasecmp(username, usernames[i]);
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
	char * password = (char *)calloc(sizeof(char),  MAX_PASSWORD_LENGTH);
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
	char * name = (char*)calloc(sizeof(char), MAX_USERNAME_LENGTH);
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
