#pragma once

#define NAME_SIZE 20
#define SURNAME_SIZE 20

typedef struct User {

	char name[NAME_SIZE];
	char surname[SURNAME_SIZE];
	char gender;
	uint8_t age;

	User(char name[20], char surname[20], char& gender, uint8_t& age) {
		strcpy_s(this->name, NAME_SIZE, name);
		strcpy_s(this->surname, SURNAME_SIZE, surname);
		this->gender = gender;
		this->age = age;
	}
};
