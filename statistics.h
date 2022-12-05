#pragma once
#include "headers.h"

typedef struct TestResults {
	uint32_t questionsTotal = 0;
	uint32_t questionsAnswered = 0;
	uint32_t correctAnswers = 0;
	uint32_t wrongAnswers = 0;
	uint32_t unasweredQuestions = 0;

};

struct Statistics {
	static void showTestResult(struct Test& test);
	static void showStatistics();
	static void writeTestResult(struct Test& test);

private:
	FILE* statsFile = NULL;
};