#pragma once
#include "headers.h"

typedef struct Test {
	void startTest(uint8_t& testIndex);

	enum TestType { ABC, TXT };
private:
	bool openTest(uint8_t& index);
	void closeTest();
	FILE* test = NULL;
	const char* testPaths[4] = {
		"tests/programming",
		"tests/law",
		"tests/cryptography",
		"tests/networking"
	};
};
