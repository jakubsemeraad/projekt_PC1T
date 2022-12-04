#pragma once
#include "test.h"

struct TestResults {
	uint32_t questionsTotal = 0;
	uint32_t questionsAnswered = 0;
	uint32_t correctAnswers = 0;
	uint32_t wrongAnswers = 0;
	uint32_t unasweredQuestions = 0;

};

typedef struct Statistics {
	static void showTestResult(Test& test);
	static void showStatistics();
};