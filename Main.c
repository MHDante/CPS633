#include "HashFunctions.h"
//main driver function to call all other sub program
int main()
{
	while (1)
	{
		//output options for user to choose
		printf("Choose which program to run from the following options.\n");
		printf("Type '1' for Part 1: OLMHash\n");
		printf("Type '2' for Part 1: ClientResponseAuth\n");
		printf("Type '3' for Part 1: OPassword Cracker\n");
		printf("Type '0' to exit.\n");
		int input = -1;
		scanf("%d", &input);
		if (input == 0)
		{
			return 0;
		}
		else if (input == 1)
		{
			printf("----------OLMHash----------\n");
			olmHash();
			break;
		}
		else if (input == 2)
		{
			printf("----------ClientResponseAuth----------\n");
			clientResponseAuth();
			break;
		}
		else if (input == 3)
		{
			printf("----------OPassword Cracker----------\n");
			oPass();
			break;
		}
		else
		{
			printf("Invalid input. Please try again.\n");
			//flush additional characters
			char c;
			do { c = getchar(); } while (c != '\n' && c != '\0');
			//flush the overflow
			fflush(stdin);
		}
	}
	return 0;
}