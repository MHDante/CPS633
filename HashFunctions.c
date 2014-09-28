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
char * Hashify(int n, char * password){
	char * hash = (char*)calloc(MAX_PASSWORD_LENGTH, sizeof(char));
	if (hash == NULL)
	{
		printf("calloc returned NULL in hashify\n");
		return hash;
	}
	strcpy(hash, password);
	strToUpper(hash);
	int i;
	for (i = 0; i < n; i++)
	{
		E(&hash[4*i], &hash[4*i]);
	}
	return hash;
}

//check for the index of the username in the table
int checkUserNameTable(const char * username, char usernames[MAX_USERS][MAX_USERNAME_LENGTH])
{
	int i;
	//for every username in the table
	for (i = 0; i < MAX_USERS; i++)
	{
		//if the usernames are equal, return the index
#ifdef _WIN32
		int cmp = stricmp(username, usernames[i]);
#else
		int cmp = strcasecmp(username, usernames[i]);
#endif
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
	sprintf(format, "%%%ds", MAX_PASSWORD_LENGTH-1); // Last byte must remain null.
	//use that format string to read the password in from the user
	scanf(format, password);
	printf("password was: %s\n length is: %d", password, (int)strlen(password));
	while(getchar() != '\n')  // Get rid of all the extra characters now...
	{
		// Loopy!
	}
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
	sprintf(format, "%%%ds", MAX_USERNAME_LENGTH-1); // Last byte must remain null.
	//use that format string to read name
	scanf(format, name);
	//flush the overflow
	printf("User name was: %s\n length is: %d", name, (int)strlen(name));
	//fflush(stdin); // This is doing nothing.
	while(getchar() != '\n')  // Get rid of all the extra characters now... Now that's a man's fflush.
	{
		// Loopy!
	}
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
void WriteToFile(char usernames[MAX_USERS][MAX_USERNAME_LENGTH], char passwords[MAX_USERS][MAX_PASSWORD_LENGTH], int usercount){
	//TODO: Write the Grid to a file.
	FILE * output;
	char newLine = '\n'; // fwrite wants a pointer... :(
	if ((output = fopen("ignoreme.txt","w")) == NULL)
	{
		printf("Couldn't create output file!\n");
		return;
	}
	usercount--; // Since it will initially point to an empty slot
	while(usercount > -1) // Write all the usernames and hashes into the file.
	{
		if(fwrite((usernames[usercount]), sizeof(char), (strlen(usernames[usercount])), output) != strlen(usernames[usercount])) // Write in the username.
		{
			printf("Error writing to file! (1)\n");
			fclose(output);
			return;
		}
		if(fwrite(&newLine, sizeof(char), 1, output) != 1) // Newline!
		{
			printf("Error writing to file! (2)\n");
			fclose(output);
			return;
		}
		if(fwrite((passwords[usercount]), sizeof(char), (strlen(passwords[usercount])), output) != strlen(passwords[usercount])) // Write in the password hash.
		{
			printf("Error writing to file! (3)\n");
			fclose(output);
			return;
		}
		if(fwrite(&newLine, sizeof(char), 1, output) != 1) // Newline!
		{
			printf("Error writing to file! (4)\n");
			fclose(output);
			return;
		}
		usercount--; // Go write the next pair.
	}
	fclose(output);
	printf("Written to disk!");
	return;
}
