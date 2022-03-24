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
#define MAX_LENGTH_OF_PARAM 12


int returnFirstIndexOfChar(char* stringToCheck, char charToFind);
int returnLastIndexOfChar(char* stringToCheck, char charToFind);
char* subString(char* sourceString, int strtIndex, int endIndex);
//int findTheIndexOfTheActionInTable(char* stringToCheck);

char* getTrimmedCodeRow(char* rowFromCode);
void analyzeCodeRow(symbolList* symbolTable, machineCode* actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int instructCounter, int dataCounter);
void handleSymbolScenario(symbolList* symbolTable, char* symbolName, char* symbolAttributes, int symbolValue);
char** buildArrayOfRowParams(char* rowFromCode, int* lengthOfArr);





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
		strncpy(destString, (sourceString + strtIndex), endIndex - strtIndex);
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

// OPEN ------ MUST !
// functin that will get the line from the file and split it to different strings in a new array
void analyzeCodeRow(symbolList* symbolTable, machineCode* actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int instructCounter, int dataCounter) {

	char* newSymbolName = NULL;
	char* restOfRowFromCode = NULL;
	char newSymbolAttribute[MAX_LENGTH_OF_ATTRBIUTE];
	char** arrayOfArgumentFromCode = NULL;

	int	i, validationFlag, lengthOfArr,
		whiteSpaceLine , commentLine ,rowHasSymbol , actionRow , directiveRow, typeOfDirective, commaLocation;
	


	whiteSpaceLine = commentLine = rowHasSymbol = actionRow = directiveRow = lengthOfArr = FALSE;

	// raise flag of char accordingly 
	whiteSpaceLine = isWhiteSpacesLine(rowFromCode);
	commentLine = isCommentLine(rowFromCode);

	// Check If the row has symbol 
	rowHasSymbol = isRowContainSymbol(rowFromCode);



	// if empty row or comment Row - finish this row
	if (whiteSpaceLine == TRUE || commentLine == TRUE)
		return;

	// Cut the row if it contains a symbol - and create the rest of the row
	if (rowHasSymbol == TRUE)
	{
		commaLocation = returnFirstIndexOfChar(rowFromCode, ':');
		newSymbolName = getTrimmedCodeRow(subString(rowFromCode, 0, commaLocation));
		restOfRowFromCode = getTrimmedCodeRow(subString(rowFromCode, commaLocation + 1, strlen(rowFromCode)));
		printf("\Symbol Name:%s	;", newSymbolName);

	}
	else
	{
		if (rowHasSymbol == FALSE)
			restOfRowFromCode = getTrimmedCodeRow(rowFromCode);
	}

	// check type of row
	if (isActionLine(rowFromCode)) {
		actionRow = TRUE;
	}
	else {
		directiveRow = TRUE;
	}

	printf("\nCode is:%s", restOfRowFromCode);

	printf("\nAction - %d; Directive - %d ;Symbol - %d\n Counters: ic: %d	\t dc:%d\n ", actionRow, directiveRow, rowHasSymbol, instructCounter, dataCounter);

	// if symbol exist - handle it. else - continue with rest of logic for each row
	//if (rowHasSymbol == TRUE)
	//{

	//	// indicate which line is it - action or directive
	//	// create the new attribute to the symbol by the row 
	//	if (actionRow) {
	//		printf("\n Action l : %d", rowHasSymbol);
	//		handleSymbolScenario(symbolTable, newSymbolName, "code", instructCounter);
	//	}
	//	if (directiveRow) {
	//		// check what is the value of isDirective line and by that continue flow
	//		//1. '.data' -> 2. '.string' -> 3. '.entry' -> 4. '.extern'
	//		typeOfDirective = isDirectiveLine(rowFromCode);

	//		printf("\n Directive : %d,\t typeOfDirective: %d", rowHasSymbol, typeOfDirective);

	//		if (typeOfDirective == 1 || typeOfDirective == 2) {
	//			// Data and String

	//			//Handle symbol scenario
	//			handleSymbolScenario(symbolTable, newSymbolName, "data", dataCounter);

	//			// identify all the data received - insert code in data machine code
	//			// increase the data counter by the number of data arguments reveiced (coded)?

	//		}
	//		else if (typeOfDirective == 4) {	// extern

	//			//Handle symbol scenario
	//			handleSymbolScenario(symbolTable, newSymbolName, "external", 0);

	//		}

	//	}
	//}


	arrayOfArgumentFromCode = buildArrayOfRowParams(restOfRowFromCode, &lengthOfArr);

	// validate the all array
	//  

	validationFlag = validateRowOfCode(arrayOfArgumentFromCode, lengthOfArr);

	
	//for (i = 0; 0 <= strlen(arrayOfArgumentFromCode[i]); i++)
	//	printf("\n%s", arrayOfArgumentFromCode[i]);

	if (directiveRow) {		// handle an directive row 
		
		typeOfDirective = isDirectiveLine(rowFromCode);
		printf("\n Directive line - type	: %d", typeOfDirective);

		if (rowHasSymbol == TRUE) {

			if (typeOfDirective == 1 || typeOfDirective == 2) {		// Data and String symbols

				handleSymbolScenario(symbolTable, newSymbolName, "data", dataCounter);
			}
			else if (typeOfDirective == 4) {	// extern

				handleSymbolScenario(symbolTable, newSymbolName, "external", 0);
			}
			// else entry typeOfDirective == 3
			// Ignore this row and wait for the second PASS
		}		

		// Handle the rest of the logic for directive 
		if (typeOfDirective == 1 || typeOfDirective == 2) {
			printf("\n Insert data machine code ");

			// Insert a new data machine code words accordingly
			
		}
	}
	
	if (actionRow) { 		// handle an action row

		printf("\n Action line:");

		if (rowHasSymbol == TRUE) {
			printf("\n With Symbol ");
			//Handle action scenario
			handleSymbolScenario(symbolTable, newSymbolName, "code", instructCounter);
		}
		// Handle the rest of the logic for action
		printf("\n No Symbol ");


		// search for valid action name 


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
		insertNewSymbolData(symbolTable,symbolName, symbolValue, symbolAttributes);

	}
}


// _------- Open
// Handle scenraio of action Row 
void handleActionRowScenario() {

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


// Build the array for the parameters of the line 
// the first cell will be the action or directive
char** buildArrayOfRowParams(char* rowFromCode, int* lengthOfArr) {

	char** arrOfParamsFromCode = (char*)malloc(sizeof(char*) * MAX_ARGS_NO_INWORD);
	int i = 1, startIndex = 0, endIndex = 0, indexToCutFirstParam, indexToContinueFrom;

	if (arrOfParamsFromCode != NULL) {

		//split between the action / directive to all params
		arrOfParamsFromCode[0] = (char*)malloc(sizeof(char) * MAX_LENGTH_OF_PARAM);

		strcpy(arrOfParamsFromCode[0], getTrimmedCodeRow(subString(rowFromCode, 0, returnFirstIndexOfChar(rowFromCode, ' '))));

		startIndex = returnFirstIndexOfChar(rowFromCode, ' ') + 1;
	
		for (i; startIndex < strlen(rowFromCode); i++) {

			indexToContinueFrom = returnFirstIndexOfChar(subString(rowFromCode, startIndex, strlen(rowFromCode)), ',');

			if (indexToContinueFrom > 0 && indexToContinueFrom < strlen(rowFromCode)) {
				endIndex = startIndex + indexToContinueFrom;
			}
			else
			{
				endIndex = strlen(rowFromCode);
			}

			// Create memory for this element in array
			arrOfParamsFromCode[i] = (char*)malloc(sizeof(char) * MAX_LENGTH_OF_PARAM);

			strcpy(arrOfParamsFromCode[i], getTrimmedCodeRow(subString(rowFromCode, startIndex, endIndex)));

			startIndex = endIndex + 1;
		}
	}

	*lengthOfArr = i;

	return arrOfParamsFromCode;
}


// Functions related to the handle of arguments

// method that will receive an argument from the action line and will output the kind of miun needed
// 0 ,1,2,3 - 
// It will know by the criteria of each miun

int findMatchedMiun(char* argmntFromLine) {




}


// _------- Open
// // 1. '.data' -> 2. '.string' -> 3. '.entry' -> 4. '.extern'
// Handle scenraio of Directive Row 
void handleDirectiveRowScenario(char* rowFromCode) {

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

