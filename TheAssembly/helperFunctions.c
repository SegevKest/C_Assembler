#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#define TRUE 1
#define FALSE 0


//get the index of the character in the array of chars
int returnIndexOfChar(char* stringToCheck, char charToFind) {

	char* pointerToChar;
	int index;

	pointerToChar = strchr(stringToCheck, charToFind);

	index = (int)(pointerToChar - stringToCheck);

	return index;
}



// returns the index of a given action - in the actionByCodeTable
int findTheIndexOfTheActionInTable(char* stringToCheck) {

	int i, j, startOfActionName, endOfActionName, foundAction = FALSE,
		lengthOfParamAction = strlen(stringToCheck);

	int lengthOfActionsArray = sizeOfActionsByOpcodeTable();
	char* actionTable = returnActionsByOpcodeTable();

	char currActionToCompare[5];



	for (i = 0; i < lengthOfActionsArray && !foundAction; i++) {

		j = startOfActionName = endOfActionName = 0;

		startOfActionName = returnIndexOfChar(actionTable[i], ':');
		endOfActionName = returnIndexOfChar(actionTable[i], ',');

	

		// Get the name of the current ation from the table - put in currActionToCompare
		strcpy(currActionToCompare, (char*)(actionTable[i] + startOfActionName + 1), endOfActionName - startOfActionName);

		/*strcmp*/



	}

}


