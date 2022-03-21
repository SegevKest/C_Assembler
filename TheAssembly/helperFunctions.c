#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "validations.h"
#include "wordInCode.h"
#include "symbol.h"


#define TRUE 1
#define FALSE 0
#define MAX_ARGS_NO_INWORD 6
#define MAX_LENGTH_OF_ATTRBIUTE 9


int returnFirstIndexOfChar(char* stringToCheck, char charToFind);
int returnLastIndexOfChar(char* stringToCheck, char charToFind);
char* subString(char* sourceString, int strtIndex, int endIndex);
//int findTheIndexOfTheActionInTable(char* stringToCheck);

char* getTrimmedCodeRow(char* rowFromCode);
void analyzeCodeRow(symbolList* symbolTable, machineCode* actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int instructCounter, int dataCounter);
void handleSymbolScenario(symbolList* symbolTable, char* symbolName, char* symbolAttributes, int symbolValue);

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

	int lengthOfDestString = endIndex - strtIndex + 1;
	char endOfString = '\0';
	char* destString, pPrint;


	//destString = (char*)malloc( lengthOfDestString * sizeof(char));
	destString = (char*)calloc(lengthOfDestString, sizeof(char));


	if(destString!=NULL)
		strncpy(destString, (sourceString), endIndex - strtIndex);
		//strncpy(destString, originString, lengthOfDestString);


	//printf("\nSubstring: %s", destString);

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
void analyzeCodeRow(symbolList* symbolTable, machineCode* actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int instructCounter, int dataCounter) {

	char* newSymbolName = NULL;
	char newSymbolAttribute[MAX_LENGTH_OF_ATTRBIUTE];

	int	whiteSpaceLine , commentLine ,rowHasSymbol , actionRow , directiveRow;
	
	whiteSpaceLine = commentLine = rowHasSymbol = actionRow = directiveRow = FALSE;

	// raise flag of char accordingly 
	whiteSpaceLine = isWhiteSpacesLine(rowFromCode);
	commentLine = isCommentLine(rowFromCode);


	// if empty row or comment Row - finish this row
	if (whiteSpaceLine == TRUE || commentLine == TRUE)
		return;

	if (isActionLine(rowFromCode)) {
		actionRow = TRUE;
	}
	else
		directiveRow = TRUE;

	// Check If the row has symbol 
	rowHasSymbol = isRowContainSymbol(rowFromCode);

	printf("%s\n%d action - %d directive \n Symbol - %d\n Counters: ic: %d	\t dc:%d", rowFromCode, actionRow, directiveRow, rowHasSymbol, instructCounter, dataCounter);


	// if symbol exist - handle it. else - continue with rest of logic for each row
	if (rowHasSymbol == TRUE)
	{
		// extarct the name of symbol 
		newSymbolName = getTrimmedCodeRow(subString(rowFromCode, 0, returnFirstIndexOfChar(rowFromCode, ':') ));

		// indicate which line is it - action or directive
		// create the new attribute to the symbol by the row 
		if (actionRow) {
			printf("\n Action l : %d", rowHasSymbol);
			//Handle action scenario
			handleSymbolScenario(symbolTable, newSymbolName, "code", instructCounter);
		}
		if (directiveRow) {
			printf("\n Directive : %d", rowHasSymbol);
			//Handle symbol scenario
			handleSymbolScenario(symbolTable, newSymbolName, "data", dataCounter);
		}
	}
	
	// Row without a symbol
	if (actionRow) {
		// handle an action row  - method for this
	}
	if (directiveRow) {
		// handle an directive row - method for this

	}
}

// _------- Open
// Handle scenraio of row with symbol 
void handleSymbolScenario(symbolList* symbolTable, char* symbolName, char* symbolAttributes, int symbolValue) {

	symbolList* isSymbolExist = NULL;
	int isValidName;

	//Validations on the symbol
	// check if the symbolName equals any of the saved words - method
	isValidName = isValidNameOfSymbol(symbolName);

	if (isValidName == FALSE)	{
		printf("ERROR: The symbol is named as a saved word");
	}
	else	{
		// insert the new symbol if all validation are valid
		insertNewSymbolData(symbolTable,symbolName, ++symbolValue, symbolAttributes);
	}
}


// _------- Open
// Handle scenraio of action Row 
void handleActionRowScenario() {

}


// _------- Open
// Handle scenraio of Directive Row 
void handleDirectiveRowScenario() {

}


//To handle the .data directive
void handleDirectiveData() {

}


//To handle the .string directive
void handleDirectiveString() {

}


//To handle the .entry directive
void handleDirectiveEntry() {

}


//To handle the .extern directive
void handleDirectiveExtern() {

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

