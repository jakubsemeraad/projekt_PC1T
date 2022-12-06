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
            numOfQuestions = atoi(strtok(NULL, ":"));
            questions = (Question*)malloc(numOfQuestions * sizeof(Question) + 1);
            toFree[toFreeCount++] = questions;


            loadQuestions(questions);

            if (questions && numOfQuestions > 0)
            {
                loadQuestions(questions);
                currentQuestion = &questions[questionIndex];
            }
        }
        closeTest();
    }


    const uint32_t maxUserInputLength = 128;
    char userInp[maxUserInputLength];


    time_t start, stop;

    start = time(NULL);
    while (!testEnd)
    {
        memset(userInp, 0, maxUserInputLength);
        currentQuestion = &questions[questionIndex];
        system("cls");
        printf("NAPOVEDA:\n     '+' = dalsi otazka\n     '-' = predchozi otazka\n     '*' = odevzdat a ukoncit test\n     '/' = zrusit pokus(ukoncit)\n\n");
        printf("===============================================================================================================\n\n");
        printf("%d/%d) %s\n\n", (questionIndex + 1), numOfQuestions, currentQuestion->question);
        if (currentQuestion->answersTotal)
        {
            for (int i = 0; i < currentQuestion->answersTotal; i++)
                printf("%c - %s\n", (char)('a' + i), currentQuestion->answers[i]);
            printf("\n");
        }
        printf("===============================================================================================================\n\n");

        if (currentQuestion->answered == true)
        {
            printf("Zaznamenana odpoved('!' pro zruseni odpovedi): %s\n\n", currentQuestion->userAnswer);
        }

        if (currentQuestion->answerHint)
            printf("%s:", currentQuestion->answerHint);
        else
            printf(":");

        scanf("%s", userInp);

        for (int i = 0; userInp[i]; i++) {
            userInp[i] = tolower(userInp[i]);
        }

        processUserInput(userInp);
    }
    stop = time(NULL);
    timeElapsed = stop - start;




    if (saveResult)
    {
        system("cls");
        printf("===============================================================================================================\n\n");
        printf("Vysledek:\n\n");
        printf("    Pocet otazek: %d\n", numOfQuestions);
        printf("    Cas testu(s): %d\n", timeElapsed);
        printf("    Spravne odpovedi: %d\n", correct);
        printf("    Spatne odpovedi: %d\n", wrong);
        printf("    Nezodpovezeno: %d\n\n", (numOfQuestions - wrong - correct));
        printf("===============================================================================================================\n\n(stisknutim ENTER pokracovat)");
        getchar();
        getchar();

        /*FILE* fptr = fopen("tests_statistics/stats.st", "a");
        for (int i = 0; i < numOfQuestions; i++)
        {
            
        }*/
    }

}

Test::~Test()
{
    
    for (int i = 0; i < toFreeCount; i++)
    {
        free(toFree[i]);
    }
}

void Test::processUserInput(char* input)
{
    if (input)
    {
        if (strlen(input) == 1 && !isalnum(input[0]))
        {
            switch (input[0])
            {
                //dalsi otazka
            case '+':
                if (questionIndex < numOfQuestions - 1)
                    questionIndex++;
                else
                    questionIndex = 0;
                break;
                //predchozi otazka
            case '-':
                if (questionIndex > 0)
                    questionIndex--;
                else
                    questionIndex = numOfQuestions - 1;
                break;
                //ukoncit test a odevzdat
            case '*':
                testEnd = true;
                saveResult = true;
                break;
                //ukoncit test - zrusit pokus
            case '/':
                testEnd = true;
                break;
            case '!':
                if (currentQuestion->answered == true)
                {
                    currentQuestion->answered = false;
                    if (strlen(currentQuestion->userAnswer) == 1)
                    {
                        if (currentQuestion->userAnswer[0] == currentQuestion->correctAnswerABC)
                            correct--;
                        else
                            wrong--;
                    }
                    else
                    {
                        if (!strcmp(currentQuestion->userAnswer, currentQuestion->correctAnswerNUMTXT))
                            correct--;
                        else
                            wrong--;
                    }

                    free(currentQuestion->userAnswer);
                }
                break;
            }
        }
        else if (validateAndWriteAnswer(input))
        {
            currentQuestion->answered = true;
            
            if (questionIndex < numOfQuestions - 1)
            {
                questionIndex++;
                currentQuestion = &questions[questionIndex];
            }
        }
    }

}

bool Test::validateAndWriteAnswer(char* input)
{
    if (currentQuestion->type == QuestionType::ABC)
    {
        if (strlen(input) == 1)
            if ((input[0] < ('a' + currentQuestion->answersTotal) && input[0] >= 'a'))
            {
                currentQuestion->userAnswer = (char*)malloc(strlen(input) + 1);
                strcpy(currentQuestion->userAnswer, input);

                if (strlen(currentQuestion->userAnswer) == 1)
                {
                    if (currentQuestion->userAnswer[0] == currentQuestion->correctAnswerABC)
                        correct++;
                    else
                        wrong++;
                }

                return true;
            }
    }
    else if (currentQuestion->type == QuestionType::TXT)
    {
        currentQuestion->userAnswer = (char*)malloc(strlen(input) + 1);
        strcpy(currentQuestion->userAnswer, input);
        if (!strcmp(currentQuestion->userAnswer, currentQuestion->correctAnswerNUMTXT))
            correct++;
        else
            wrong++;
        return true;
    }
    else if (currentQuestion->type == QuestionType::NUM)
    {
        int i = 0;
        while (input[i] != '\0')
        {
            if (!isdigit(input[i]))
                return false;
            i++;
        }
        currentQuestion->userAnswer = (char*)malloc(strlen(input) + 1);
        strcpy(currentQuestion->userAnswer, input);
        if (!strcmp(currentQuestion->userAnswer, currentQuestion->correctAnswerNUMTXT))
            correct++;
        else
            wrong++;
        return true;

    }

    return false;
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
                processFileInput(type, value);
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

void Test::processFileInput(char* type, char* value){

    if (!strcmp(type, "questiontype")) 
    {
        if(value)
            currentQuestion->type = evaluateQuestionType(value);
    }
    else if (!strcmp(type, "question")) 
    {
         currentQuestion->question = (char*)malloc(strlen(value) + 1);
         toFree[toFreeCount++] = currentQuestion->question;
         if(currentQuestion->question)
             strcpy(currentQuestion->question, value);
    }
    else if (!strcmp(type, "answerstotal")) 
    {
        currentQuestion->answersTotal = atoi(value);
        currentQuestion->answers = (char**)malloc(currentQuestion->answersTotal * sizeof(char*) + 1);
        toFree[toFreeCount++] = currentQuestion->answers;
        for (int i = 0; i < currentQuestion->answersTotal; i++)
            currentQuestion->answers[i] = NULL;
    }
    else if (strlen(type) == 1) 
    {
         for(int i = 0; i < currentQuestion->answersTotal; i++)
             if (currentQuestion->answers[i] == NULL) 
             {
                 currentQuestion->answers[i] = (char*)malloc(strlen(value) + 1);
                 toFree[toFreeCount++] = currentQuestion->answers[i];
                 strcpy(currentQuestion->answers[i], value);
                 break;
             }
    }
    else if (!strcmp(type, "answer")) 
    {

         if (currentQuestion->type == QuestionType::ABC)
             strcpy(&currentQuestion->correctAnswerABC, value);
         else if (currentQuestion->type == QuestionType::TXT || currentQuestion->type == QuestionType::NUM)
         {
             currentQuestion->correctAnswerNUMTXT = (char*)malloc(strlen(value) + 1);
             toFree[toFreeCount++] = currentQuestion->correctAnswerNUMTXT;
             strcpy(currentQuestion->correctAnswerNUMTXT, value);
         }
    }
    else if (!strcmp(type, "hint"))
    {
         currentQuestion->answerHint = (char*)malloc(strlen(value) + 1);
         toFree[toFreeCount++] = currentQuestion->answerHint;
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
