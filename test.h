#pragma once

typedef struct Test {
	
	enum Subject {
		NETWORKING,
		LAW,
		CRYPTOGRAPHY,
		PROGRAMMING,
	};

	const char* testPath[4] = { 
		"tests/networking",
		"tests/lew",
		"tests/cryptography",
		"tests/programming" 
	};

	bool loadTest() {
		FILE* test;
	}



};
