#include "statistics.h"

void Statistics::showTestResult(struct Test& test) 
{
	TestResults tr;
	tr.questionsTotal = test.numOfQuestions;
	tr.timeElapsed = test.timeElapsed;
	
	for (int i = 0; i < tr.questionsTotal; i++)
	{
		if (test.questions[i].answered)
		{
			if (test.questions[i].correctAnswerNUMTXT)
			{
				if (!strcmp(test.questions[i].userAnswer, test.questions[i].correctAnswerNUMTXT))
					tr.correctAnswers++;
				else
					tr.wrongAnswers++;
			}
			else
			{
				if (test.questions[i].userAnswer[0] == test.questions[i].correctAnswerABC)
					tr.correctAnswers++;
				else
					tr.wrongAnswers++;
			}
				
		}
		else
		{
			tr.unasweredQuestions++;
		}
	}


}

void Statistics::writeTestResult(struct Test& test)
{

}

void Statistics::showStatistics()
{

}
