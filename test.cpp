#include "test.h"

void Test::startTest(uint8_t& testIndex) 
{
    if (openTest(testIndex)) 
    {
        if (!feof(test)) 
        {
            fgets(fileInput, maxFileInputLength, test);
            fileInput[strcspn(fileInput, "\n")] = '\0';
            char* tmp = strtok(fileInput, ":");
            int numOfQuestions = atoi(strtok(NULL, ":"));
            questions = (Question*)malloc(numOfQuestions * sizeof(Question));

            loadQuestions(questions);

            if (questions && numOfQuestions > 0)
            {
                loadQuestions(questions);
                currentQuestion = &questions[0];
            }
        }
        closeTest();
    }

    
}

bool Test::openTest(uint8_t& index)
{
	test = fopen(testPaths[index], "r");
	return (test != NULL);
}

void Test::loadQuestions(Question* questions)
{
    int currQuestionIndex = -1;
    while (!feof(test))
    {
        if (fgets(fileInput, maxFileInputLength, test))
        {
            fileInput[strcspn(fileInput, "\n")] = '\0';
            char* type = strtok(fileInput, ":");
            char* value = strtok(NULL, ":");

            if (type && value)
                processInput(type, value);
            else if (!strcmp(fileInput, ""))
            {
                currQuestionIndex++;
                currentQuestion = &questions[currQuestionIndex];
            }

        }
    }
}

void Test::closeTest()
{
	if(test != NULL)
		fclose(test);
}

void Test::processInput(char* type, char* value){

    if (!strcmp(type, "questiontype")) 
    {
        if(value)
            currentQuestion->type = evaluateQuestionType(value);
    }
    else if (!strcmp(type, "question")) 
    {

         currentQuestion->question = (char*)malloc(strlen(value));
         if(currentQuestion->question)
             strcpy(currentQuestion->question, value);
    }
    else if (!strcmp(type, "answerstotal")) 
    {
        currentQuestion->answersTotal = atoi(value);
        currentQuestion->answers = (char**)malloc(currentQuestion->answersTotal * sizeof(char*));
        for (int i = 0; i < currentQuestion->answersTotal; i++)
            currentQuestion->answers[i] = NULL;
    }
    else if (strlen(type) == 1) 
    {
         for(int i = 0; i < currentQuestion->answersTotal; i++)
             if (currentQuestion->answers[i] == NULL) 
             {
                 currentQuestion->answers[i] = (char*)malloc(strlen(value));
                 strcpy(currentQuestion->answers[i], value);
             }
    }
    else if (!strcmp(type, "answer")) 
    {

         if (currentQuestion->type == QuestionType::ABC)
             strcpy(&currentQuestion->correctAnswerABC, value);
         else if (currentQuestion->type == QuestionType::TXT) 
         {
             currentQuestion->correctAnswerTXT = (char*)malloc(strlen(value));
             strcpy(currentQuestion->correctAnswerTXT, value);
         }
         else if (currentQuestion->type == QuestionType::NUM)
             currentQuestion->correctAnswerNUM = atoi(value);
    }
    else if (!strcmp(type, "hint"))
    {
         currentQuestion->answerHint = (char*)(malloc(strlen(value)));
         if(currentQuestion->answerHint)
             strcpy(currentQuestion->answerHint, value);
    }
}

QuestionType Test::evaluateQuestionType(char* value)
{
    if (!strcmp(value, "abc"))
        return QuestionType::ABC;
    else if (!strcmp(value, "txt"))
        return QuestionType::TXT;
    else if (!strcmp(value, "num"))
        return QuestionType::NUM;

    return QuestionType::NONE;
}
