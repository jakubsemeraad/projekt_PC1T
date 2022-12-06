#include "headers.h"

uint8_t userInput;

void takeTest() 
{
	do 
	{
		system("cls");
		printf("===============================================================================================================\n\n");
		printf("Obor testu:   1 - programovani | 2 - pravo | 3 - kryptografie | 4 - zpet\n\n");
		printf("===============================================================================================================\n\n>");


		scanf(" %hhu", &userInput);
	
		if (userInput >= 1 && userInput <= 3) 
		{
			Test test;
			userInput -= 1;
			test.startTest(userInput);
			system("cls");
			break;
		}
		else if (userInput == 4) 
		{
			system("cls");
			break;
		}
		else 
		{
			system("cls");
			printf("neplatna volba!\n\n");
		}

	} while (true);
}

void showStatistics() {
	
}

int main(int argc, char** argv) 
{

	User user;
	system("cls");
	do 
	{
		system("cls");
		printf("===============================================================================================================\n\n");
		printf("   1 - spustit test | 2 - zobrazit statistiky | 3 - konec\n\n");
		printf("===============================================================================================================\n\n>");
		scanf_s(" %hhu", &userInput);

		switch (userInput) 
		{
		case 1:
			system("cls");
			takeTest();
			break;
		case 2:
			system("cls");
			showStatistics();
			break;
		case 3:
			exit(0);
			break;
		default:
			system("cls");
			printf("neplatna volba!\n\n");
		}

	} while (true);
}