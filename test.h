#pragma once
#include "headers.h"

enum QuestionType
{ 
	NONE, ABC, TXT, NUM 
};

typedef struct Question 
{
	QuestionType type;
	char* question;
	int answersTotal;

	union 
	{
		char correctAnswerABC;
		char* correctAnswerTXT;
		int correctAnswerNUM;
	};

	union 
	{
		char** answers;
	};
	char* answerHint;
	char* userAnswer;
};

typedef struct Test 
{
	void startTest(uint8_t& testIndex);

private:
	bool openTest(uint8_t& index);
	void loadQuestions(Question* questions);
	void closeTest();
	void processInput(char* type, char* value);

	QuestionType evaluateQuestionType(char* value);
	FILE* test = NULL;
	const char* testPaths[4] = 
	{
		"tests/programming.test",
		"tests/law.test",
		"tests/cryptography.test",
		"tests/networking.test"
	};

	static const uint32_t maxUserInputLength = 128;
	char userInput[maxUserInputLength];
	static const uint16_t maxFileInputLength = 512;
	char fileInput[maxFileInputLength];
	uint32_t questionsTotal = 0;
	Question* questions;
	Question* currentQuestion = NULL;
};