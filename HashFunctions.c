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
	//make the input characters uppercase.
	char c0 = toupper(in[0]);
	char c1 = toupper(in[1]);
	char c2 = toupper(in[2]);
	char c3 = toupper(in[3]);

	out[0] = (c0 & 0x80) ^ (((c0 >> 1) & 0x7F) ^ ((c0) & 0x7F));
	out[1] = ((c1 & 0x80) ^ ((c0 << 7) & 0x80)) ^ (((c1 >> 1) & 0x7F) ^ ((c1) & 0x7F));
	out[2] = ((c2 & 0x80) ^ ((c1 << 7) & 0x80)) ^ (((c2 >> 1) & 0x7F) ^ ((c2) & 0x7F));
	out[3] = ((c3 & 0x80) ^ ((c2 << 7) & 0x80)) ^ (((c3 >> 1) & 0x7F) ^ ((c3) & 0x7F));
}
char * Hashify(int n, char * password){
	//allocate a string that is initially cleared
	char * hash = (char*)calloc(MAX_PASSWORD_LENGTH, sizeof(char));
	//if the allocation fails print error message
	if (hash == NULL)
	{
		printf("calloc returned NULL in hashify\n");
		return hash;
	}
	int i;
	//iterate through every 4 byte chunk and perform the hashing function
	for (i = 0; i < n; i++)
	{
		E(&password[4*i], &hash[4*i]);
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
	char * password = (char *)calloc(MAX_PASSWORD_LENGTH, sizeof(char));
	char format[80];
	//create a format string that will only accept up to the maximum password length
	sprintf(format, "%%%ds", MAX_PASSWORD_LENGTH-1); // Last byte must remain null.
	//use that format string to read the password in from the user
	scanf(format, password);
	//printf("password was: %s\n length is: %d", password, (int)strlen(password));
	while (getchar() != '\n') { }  // Get rid of all the extra characters now...
	return password;
}
//read input from user as a username with a max and min length
char * enterUsername()
{
	//allocate a string of the max username length
	char * name = (char*)calloc(MAX_USERNAME_LENGTH, sizeof(char));
	printf("Enter your username, Type 0 to exit:\n");
	char format[80];
	//create format string for reading in the max length
	sprintf(format, "%%%ds", MAX_USERNAME_LENGTH-1); // Last byte must remain null.
	//use that format string to read name
	scanf(format, name);
	//flush the overflow
	//printf("User name was: %s\n length is: %d", name, (int)strlen(name));
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
//read from file (if exists) and populate the tables
int ReadFromFile(char usernames[MAX_USERS][MAX_USERNAME_LENGTH], char passwords[MAX_USERS][MAX_PASSWORD_LENGTH])
{
	FILE * file;
	char line[80];
	char newLine = '\n';
	//attempt to open file
	if ((file = fopen("ignoreme.txt", "rt")) == NULL)
	{
		//printf("Couldn't open output file!\n");
		return;
	}
	int counter = 0;
	char * str = (char*)calloc(13, sizeof(char));
	//for every line in the file, add to the table
	while (fgets(line, 80, file) != NULL)
	{
		sscanf(line, "%12s", str);
		//even numbered lines are usernames, odd are passwords
		if (counter % 2 == 0)
		{
			strncpy(usernames[counter / 2], str, 12);
		}
		else
		{
			strncpy(passwords[counter / 2], str, 12);
		}
		counter++;
	}
	fclose(file);
	return counter / 2;
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
