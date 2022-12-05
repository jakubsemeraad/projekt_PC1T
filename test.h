#pragma once
#include "headers.h"

enum QuestionType
{ 
	NONE, ABC, TXT, NUM 
};

typedef struct Question 
{
	bool answered = false;
	QuestionType type = QuestionType::NONE;
	char* question = nullptr;
	int answersTotal = 0;

	union
	{
		char correctAnswerABC;
		char* correctAnswerNUMTXT = nullptr;
	};

	char** answers = nullptr;
	char* answerHint = nullptr;
	char* userAnswer = nullptr;
};

typedef struct Test 
{
	void startTest(uint8_t& testIndex);
	~Test();
private:
	bool openTest(uint8_t& index);
	void loadQuestions(Question* questions);
	void closeTest();
	void processFileInput(char* type, char* value);
	void processUserInput(char* input);
	bool validateAndWriteAnswer(char* input);
	bool testEnd = false;
	bool saveResult = false;
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
	int QuestionsAnswered = 0;
	Question* questions = nullptr;
	Question* currentQuestion = nullptr;
	void* toFree[1024]{ 0 };
	int toFreeCount = 0;
};