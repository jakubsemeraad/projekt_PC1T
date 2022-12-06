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
	FILE* f = fopen("tests_statistics/stats.st", "r");
	char readBuf[512];
	
	float nCr = 0 , nPr = 0, nLa = 0;
	int crTimeTotal = 0, crCorrTotal = 0, crWrTotal = 0, crNaTotal = 0;
	int prTimeTotal = 0, prCorrTotal = 0, prWrTotal = 0, prNaTotal = 0;
	int laTimeTotal = 0, laCorrTotal = 0, laWrTotal = 0, laNaTotal = 0;
	int qNcr = 0, qNla = 0, qNpr = 0;

	while (!feof(f))
	{
		fgets(readBuf, 512, f);
		

		if (readBuf[0] != '\n')
		{
			readBuf[strcspn(readBuf, "\n")] = '\0';

			char* type = strtok(readBuf, ";");
			int qNum = atoi(strtok(NULL, ";"));
			int time = atoi(strtok(NULL, ";"));
			int corr = atoi(strtok(NULL, ";"));
			int wr = atoi(strtok(NULL, ";"));
			int na = atoi(strtok(NULL, ";"));

			if (!strcmp(type, "tests/programming.test"))
			{
				nPr++;
				qNpr = qNum;
				prCorrTotal += corr;
				prTimeTotal += time;
				prWrTotal += wr;
				prNaTotal += na;
			}
			else if (!strcmp(type, "tests/law.test"))
			{
				nLa++;
				qNla = qNum;
				laCorrTotal += corr;
				laTimeTotal += time;
				laWrTotal += wr;
				laNaTotal += na;
			}
			else if (!strcmp(type, "tests/cryptography.test"))
			{
				nCr++;
				qNcr = qNum;
				crCorrTotal += corr;
				crTimeTotal += time;
				crWrTotal += wr;
				crNaTotal += na;
			}

		}
	}

	printf("TEST NA PRAVO:\n     pocet otazek: %d\n     prumerne straveny cas: %.2f sekund\n     prumerny pocet chyb: %.2f\n     prumerny pocet spravnych odpovedni: %.2f\n     prumerny pocet nezodpovezenych otazek: %.2f\n\n===============================================================================================================\n\n",
		qNla, (laTimeTotal/nLa), (laWrTotal/nLa), (laCorrTotal/nLa), (laNaTotal/nLa));
	printf("TEST NA KRYPTOGRAFII:\n     pocet otazek: %d\n     prumerne straveny cas: %.2f sekund\n     prumerny pocet chyb: %.2f\n     prumerny pocet spravnych odpovedni: %.2f\n     prumerny pocet nezodpovezenych otazek: %2.f\n\n===============================================================================================================\n\n",
		qNcr, (crTimeTotal / nCr), (crWrTotal / nCr), (crCorrTotal / nCr), (crNaTotal / nCr));
	printf("TEST NA PROGRAMOVANI:\n     pocet otazek: %d\n     prumerne straveny cas: %.2f sekund\n     prumerny pocet chyb: %.2f\n     prumerny pocet spravnych odpovedni: %.2f\n     prumerny pocet nezodpovezenych otazek: %2.f\n\n===============================================================================================================\n\n",
		qNpr, (prTimeTotal / nPr), (prWrTotal / nPr), (prCorrTotal / nPr), (prNaTotal / nPr));

	printf("\n(stisknutim ENTER pokracovat)\n");
	getchar();
	getchar();
	
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