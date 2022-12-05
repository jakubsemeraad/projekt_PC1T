#pragma once
#include "headers.h"

enum QuestionType
{ 
	NONE, ABC, TXT, NUM 
};

typedef struct Question 
{
	QuestionType type = QuestionType::NONE;
	char* question = NULL;
	int answersTotal = 0;

	union 
	{
		char correctAnswerABC;
		char* correctAnswerNUMTXT;
	};

	union 
	{
		char** answers;
	};
	char* answerHint = NULL;
	char* userAnswer = NULL;
};

typedef struct Test 
{
	void startTest(uint8_t& testIndex);

private:
	bool openTest(uint8_t& index);
	void loadQuestions(Question* questions);
	void closeTest();
	void processFileInput(char* type, char* value);
	void processUserInput(char* input);
	bool testEnd = false;
	QuestionType evaluateQuestionType(char* value);
	FILE* test = NULL;
	const char* testPaths[4] = 
	{
		"tests/programming.test",
		"tests/law.test",
		"tests/cryptography.test",
		"tests/networking.test"
	};

	static const uint16_t maxFileInputLength = 512;
	char fileInput[maxFileInputLength];
	int numOfQuestions = 0;
	int questionIndex = 0;
	Question* questions;
	Question* currentQuestion = NULL;
};