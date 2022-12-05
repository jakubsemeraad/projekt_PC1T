#include "headers.h"

uint8_t userInput;

void takeTest() {
	printf("Obor testu\n    0 - Pocitacove site | 1 - pravo | 2 - kryptografie | 3 - programovani | 4 - zpet\n>");

	do {
		scanf_s(" %hhu", &userInput);
		
		if (userInput >= 0 && userInput <= 3) {
			Test t;
			t.startTest(userInput);
			Statistics::showTestResult(t);
		}

	} while (userInput < 0 || userInput > 3);
}

void showStatistics() {
	Statistics::showStatistics();
}

int main(int argc, char** argv) {

	User user;

	do {
		printf("	1 - spustit test | 2 - zobrazit statistiky | 3 - konec\n>");
		scanf_s(" %hhu", &userInput);

		switch (userInput) {
		case 1:
			takeTest();
			break;
		case 2:
			showStatistics();
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("neplatna volba!\n\n");
		}

	} while (true);
}