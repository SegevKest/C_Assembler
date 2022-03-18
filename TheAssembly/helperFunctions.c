#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#define TRUE 1
#define FALSE 0


//get the index of the character in the array of chars
int returnFirstIndexOfChar(char* stringToCheck, char charToFind) {

	char* pointerToChar;
	int index;

	pointerToChar = strchr(stringToCheck, charToFind);

	index = (int)(pointerToChar - stringToCheck);

	return index;
}

//get the index of the character in the array of chars
int returnLastIndexOfChar(char* stringToCheck, char charToFind) {

	char* pointerToChar;
	int index;

	pointerToChar = strrchr(stringToCheck, charToFind);

	index = (int)(pointerToChar - stringToCheck);

	return index;
}


// This function gets a string and 2 indexes - return a new String between the 2 indexes
char* subString(char *sourceString, int strtIndex, int endIndex) {

	int lengthOfDestString = endIndex - strtIndex;
	char endOfString = '\0';


	char* destString = (char*)malloc( sizeof(char) * lengthOfDestString );


	if(destString)
		strncpy(destString, (sourceString + strtIndex), lengthOfDestString);


	return destString;
}


//// returns the index of a given action - in the actionByCodeTable
int findTheIndexOfTheActionInTable(char* stringToCheck) {
//
	int i, j, startOfActionName, endOfActionName, foundAction = FALSE,
		lengthOfParamAction = strlen(stringToCheck);

	int lengthOfActionsArray = sizeOfActionsByOpcodeTable();
	char* actionTable = returnActionsByOpcodeTable();

	char currActionToCompare[5];



	for (i = 0; i < lengthOfActionsArray && !foundAction; i++) {

		j = startOfActionName = endOfActionName = 0;

		

	

		// Get the name of the current ation from the table - put in currActionToCompare
		strcpy(currActionToCompare, (char*)(actionTable[i] + startOfActionName + 1), endOfActionName - startOfActionName);

		/*strcmp*/



	}

}









// Functions related to the handle of arguments

// method that will receive an argument from the action line and will output the kind of miun needed
// 0 ,1,2,3 - 
// It will know by the criteria of each miun

int findMatchedMiun(char* argmntFromLine) {




}


//identify miun 0 exc,
int isMiunZero(char* argmntFromLine) {

	// the operand will be in format : "#{int}"
	return *argmntFromLine == '#' ? TRUE : FALSE;
}

int isMiunOne(char* argmntFromLine) {

	// check if the argument is a Symbol

}
int isMiunZTwo() {

	// if containa  name of a symbol and concat  [{register}]
}
int isMiunThree() {

}