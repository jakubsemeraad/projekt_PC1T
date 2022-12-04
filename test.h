#pragma once
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include "statistics.h"

typedef struct Test {
	void startTest(uint8_t& testIndex);
	

private:
	bool openTest(uint8_t& index);
	void closeTest();
	FILE* test;
	const char* testPaths[4] = {
		"tests/networking",
		"tests/law",
		"tests/cryptography",
		"tests/programming"
	};
};
