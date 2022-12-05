#include "test.h"

void Test::startTest(uint8_t& testIndex){
	openTest(testIndex);



	closeTest();
}

bool Test::openTest(uint8_t& index){
	test = fopen(testPaths[index], "r");
	return (test != NULL);
}

void Test::closeTest(){
	if(test != NULL)
		fclose(test);
}
