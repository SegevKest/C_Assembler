#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#define TRUE 1
#define FALSE 0
#define MAX_ARGS_NO_INWORD 6

int returnFirstIndexOfChar(char* stringToCheck, char charToFind);
int returnLastIndexOfChar(char* stringToCheck, char charToFind);
char* subString(char* sourceString, int strtIndex, int endIndex);
//int findTheIndexOfTheActionInTable(char* stringToCheck);

char* getTrimmedCodeRow(char* rowFromCode);



//get the index of the character in the array of chars
int returnFirstIndexOfChar(char* stringToCheck, char charToFind) {

	char* pointerToChar;
	int index = -1;

	pointerToChar = strchr(stringToCheck, charToFind);

	index = (int)(pointerToChar - stringToCheck);

	return index;
}

//get the index of the character in the array of chars
int returnLastIndexOfChar(char* stringToCheck, char charToFind) {

	char* pointerToChar;
	int index = -1;

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
//int findTheIndexOfTheActionInTable(char* stringToCheck) {
////
//	int i, j, startOfActionName, endOfActionName, foundAction = FALSE,
//		lengthOfParamAction = strlen(stringToCheck);
//
//	int lengthOfActionsArray = sizeOfActionsByOpcodeTable();
//	char* actionTable = returnActionsByOpcodeTable();
//
//	char currActionToCompare[5];
//
//
//
//	for (i = 0; i < lengthOfActionsArray && !foundAction; i++) {
//
//		j = startOfActionName = endOfActionName = 0;
//
//		
//
//	
//
//		// Get the name of the current ation from the table - put in currActionToCompare
//		strcpy(currActionToCompare, (char*)(actionTable[i] + startOfActionName + 1), endOfActionName - startOfActionName);
//
//		/*strcmp*/
//
//
//
//	}
//
//}






// functin that will get the line from the file and split it to different strings in a new array
char* analyzeCodeRow(char* rowFromCode, int instructCounter, int dataCounter) {

	//check for existing symbol at the sta
	int indexOfColon = returnFirstIndexOfChar(rowFromCode, ':');
	char* newSymbolVar = NULL;

	// check if this is a Action line of directive
	// raise flag of char accordingly 
	// 
	
	// only if found a 
	if (indexOfColon > 0)
	{
		//Has a new Symbol definition inside this row
		newSymbolVar = subString(rowFromCode,0,indexOfColon);
		
		// continue handle the New Symbol Value

	}

}

// This method will iterate all the string and will return a new string with no spaces
char* getTrimmedCodeRow(char* rowFromCode) {

	char* trimmedRow = strdup(rowFromCode);
	char* endOfLine;
	
	// Run from the prefix of the rowFromCode
	while (isspace((unsigned char)*trimmedRow))	trimmedRow++;
	
	if (*trimmedRow == 0)
		return trimmedRow;

	endOfLine = trimmedRow + strlen(trimmedRow) - 1;

	// Run from end of the rowFromCode
	while (endOfLine > trimmedRow && isspace((unsigned char)*endOfLine)) endOfLine--;

	endOfLine[1] = '\0';

	return trimmedRow;

}


// Functions related to the handle of arguments

// method that will receive an argument from the action line and will output the kind of miun needed
// 0 ,1,2,3 - 
// It will know by the criteria of each miun

int findMatchedMiun(char* argmntFromLine) {




}

