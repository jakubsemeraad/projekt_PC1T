#include "user.h"

User::User() {
	printf("Vase jmeno: ");
	scanf_s("%s", &name, (unsigned int)sizeof(name));
	printf("Vase prijmeni: ");
	scanf_s("%s", &surname, (unsigned int)sizeof(surname));
	printf("Vas vek: ");
	scanf_s(" %hhu", &age);
	printf("Vase pohlavi(m/z): ");
	scanf_s(" %c", &gender, (unsigned int)sizeof(char));
}

uint32_t User::getUserDataSize(){
	return strlen(name) + 1 + strlen(surname) + 1 + sizeof(gender) + 1 + sizeof(age) + 1;
}

char* User::getUserData(){
	uint32_t userDataSize = getUserDataSize();
	char* userData = (char*)malloc(userDataSize);
	uint32_t offset = 0;
	char dataSeparator = '/';

	memcpy(&userData[offset], name, sizeof(name));
	offset += strlen(name);
	userData[offset] = dataSeparator;
	offset += 1;
	memcpy(&userData[offset], surname, sizeof(surname));
	offset += strlen(surname);
	userData[offset] = dataSeparator;
	offset += 1;
	memset(&userData[offset], age, sizeof(age));
	offset += sizeof(age);
	userData[offset] = dataSeparator;
	offset += 1;
	memset(&userData[offset], gender, sizeof(gender));
	offset += sizeof(gender);
	userData[offset] = '\0';

	return userData;
}
