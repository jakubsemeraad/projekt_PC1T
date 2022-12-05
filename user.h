#pragma once
#include "headers.h"

#define NAME_SIZE 20
#define SURNAME_SIZE 20

typedef struct User {
	User();
	char* getUserData();
	uint32_t getUserDataSize();
private:

	char name[NAME_SIZE];
	char surname[SURNAME_SIZE];
	char gender;
	uint8_t age;
};


