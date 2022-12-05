#pragma once
#include "headers.h"

enum QuestionType { NONE, ABC, TXT };

typedef struct Question {
	QuestionType type;
	char* correctAnswer;
	char* userAnswer;
};

typedef struct Test {
	void startTest(uint8_t& testIndex);

private:
	bool openTest(uint8_t& index);
	void closeTest();
	void processInput(char* type, char* value);

	QuestionType evaluateQuestionType(char* value);
	FILE* test = NULL;
	const char* testPaths[4] = {
		"tests/programming",
		"tests/law",
		"tests/cryptography",
		"tests/networking"
	};

	static const uint32_t maxUserInputLength = 128;
	char userInput[maxUserInputLength];
	Question* questions;
	Question* currentQuestion = NULL;
};