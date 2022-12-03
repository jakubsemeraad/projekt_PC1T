#include "test.h"
#include "user.h"

void takeTest() {

}

void showStatistics(Test* t) {

}

void showStatistics() {

}

int main(int argc, char** argv) {

	User user;
	uint8_t userInput;

	do {
		printf("1 - spustit test | 2 - zobrazit statistiky | 3 - konec\n>");
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