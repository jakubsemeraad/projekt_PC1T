#include "headers.h"

uint8_t userInput;

void takeTest() 
{
	do 
	{
		printf("===============================================================================================================\n\n");
		printf("Obor testu:   1 - programovani | 2 - pravo | 3 - kryptografie | 4 - pocitacove site | 5 - zpet\n\n");
		printf("===============================================================================================================\n\n>");
		scanf_s(" %hhu", &userInput);
	
		if (userInput >= 1 && userInput <= 4) 
		{
			Test test;
			userInput -= 1; //
			test.startTest(userInput);
			Statistics::showTestResult(test);
			Statistics::writeTestResult(test);

		}
		else if (userInput == 5) 
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
	Statistics::showStatistics();
}

int main(int argc, char** argv) 
{

	User user;
	system("cls");
	do 
	{
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