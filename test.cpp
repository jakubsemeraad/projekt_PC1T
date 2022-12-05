#include "test.h"

void Test::startTest(uint8_t& testIndex) {
    if (openTest(testIndex)) {

        QuestionType questionType;
        const uint16_t maxInputLength = 1024;
        char fileInput[maxInputLength];

        if (!feof(test)) {
            fgets(fileInput, maxInputLength, test);
            char* t = strtok(fileInput, ":");
            int numOfQuestions = atoi(strtok(NULL, ":"));
            questions = (Question*)malloc(numOfQuestions * sizeof(Question));
            if (numOfQuestions > 0) 
                currentQuestion = &questions[0];

            while (!feof(test)) {
                if (fgets(fileInput, maxInputLength, test)) {
                    fileInput[strcspn(fileInput, "\n")] = '\0';
                    char* type = strtok(fileInput, ":");
                    char* value = strtok(NULL, ":");

                    if(type)
                        processInput(type, value);
                }
            }
        }

        closeTest();
    }
}

bool Test::openTest(uint8_t& index){
	test = fopen(testPaths[index], "r");
	return (test != NULL);
}

void Test::closeTest(){
	if(test != NULL)
		fclose(test);
}

void Test::processInput(char* type, char* value){

    if (!strcmp(type, "questiontype")) {
        if(value)
            currentQuestion->type = evaluateQuestionType(value);
    }
    else if (!strcmp(type, "question")) {
        if (value) {
            system("cls");
            printf("===============================================================================================================\n\n");
            printf("Otazka:   %s\n\n", value);
            printf("===============================================================================================================\n\n");
        }
    }
    else if (strlen(type) == 1) {
        if (value) {
            if (type[0] >= 'a' && type[0] <= 'z') {
                printf("    %c - %s\n", type[0], value);
            }
        }
    }
    else if (!strcmp(type, "answer")) {
        if (value) {
            currentQuestion->correctAnswer = (char*)malloc(strlen(value));
            if(currentQuestion->correctAnswer)
                strcpy(currentQuestion->correctAnswer, value);
        }
    }
    else if (!strcmp(type, "getuserinput")) {
        if (value)
            printf("\n%s>", value);
        else
            printf(">");
        scanf("%s", userInput);
        currentQuestion->userAnswer = (char*)malloc(strlen(userInput));
        if(currentQuestion->userAnswer)
            strcpy(currentQuestion->userAnswer, userInput);
    }
}

QuestionType Test::evaluateQuestionType(char* value)
{
    if (!strcmp(value, "abc\n"))
        return QuestionType::ABC;
    else if(!strcmp(value, "txt"))
        return QuestionType::TXT;

    return QuestionType::NONE;
}
