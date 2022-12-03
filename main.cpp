#include <iostream>
#include "test.h"
#include "user.h"



int main(int argc, char** argv) {

	char name[NAME_SIZE];
	char surname[SURNAME_SIZE];
	char gender;
	uint8_t age;

	printf("Vase jmeno: ");
	scanf_s("%s", &name, (unsigned int)sizeof(name));
	printf("Vase prijmeni: ");
	scanf_s("%s", &surname, (unsigned int)sizeof(surname));
	printf("Vas vek: ");
	scanf_s(" %hhu", &age);
	printf("Vase pohlavi(m/z): ");
	scanf_s(" %c", &gender, (unsigned int)sizeof(char));

	User user(name, surname, gender, age);
	uint8_t userInput;

	do
	{
		printf("0 - ukoncit program | 1 - spustit test | 2 - zobrazit statistiky\n>");
		scanf_s(" %hhu", &userInput);
	} while (userInput);
}