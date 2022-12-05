#include "test.h"

void Test::startTest(uint8_t& testIndex) {
    if (openTest(testIndex)) {

        TestType type;
        const uint16_t maxQuestionLength = 1024;
        char question[maxQuestionLength];

        while (!feof(test)) {
            fgets(question, maxQuestionLength, test);
            printf("%s", question);
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
