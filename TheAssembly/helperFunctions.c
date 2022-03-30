#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#include "validations.h"
#include "wordInCode.h"
#include "symbol.h"
#include "constantTables.h"


#define TRUE 1
#define FALSE 0
#define MAX_ARGS_NO_INWORD 6
#define MAX_LENGTH_OF_ATTRBIUTE 9
#define MAX_LENGTH_OF_PARAM 12
#define LENGTH_OF_BIN_NUMBER 16

int returnFirstIndexOfChar(char* stringToCheck, char charToFind);
int returnLastIndexOfChar(char* stringToCheck, char charToFind);
char* subString(char* sourceString, int strtIndex, int endIndex);
//int findTheIndexOfTheActionInTable(char* stringToCheck);

char* getTrimmedCodeRow(char* rowFromCode);
void analyzeCodeRow(symbolList* symbolTable, machineCode* actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int instructCounter, int dataCounter, int* validationFlag);
void handleSymbolScenario(symbolList* symbolTable, char* symbolName, char* symbolAttributes, int symbolValue);
char** buildArrayOfRowParams(char* rowFromCode, int* lengthOfArr);
void handleActionRowScenario(machineCode* actionsMachineCode, symbolList* symbolTable, char** arrayOfArgs, int lengthOfArr, int* pToActionsCounter);

char* convertNumberToBinaryString(int numberToConvert);
char* getRegisterCode(char* argFromLine);

char* findMatchedMiun(char* argmntFromLine, symbolList* symbolTable);




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


// This method will iterate all the string and will return a new string with no spaces
char* getTrimmedCodeRow(char* rowFromCode) {

	char* trimmedRow = malloc(sizeof(rowFromCode));
		
	char* endOfLine;
	
	trimmedRow = strdup(rowFromCode);
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

		if (arrOfParamsFromCode[0] != NULL) {
			strcpy(arrOfParamsFromCode[0], getTrimmedCodeRow(subString(rowFromCode, 0, returnFirstIndexOfChar(rowFromCode, ' '))));
		}

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
			
			if (arrOfParamsFromCode[i] != NULL) {
				strcpy(arrOfParamsFromCode[i], getTrimmedCodeRow(subString(rowFromCode, startIndex, endIndex)));
			}
			startIndex = endIndex + 1;
		}
	}

	*lengthOfArr = i;

	return arrOfParamsFromCode;
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

// _------- Open
// Handle scenraio of row with symbol 
void handleSymbolScenario(symbolList* symbolTable, char* symbolName, char* symbolAttributes, int* symbolValue) {

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
		insertNewSymbolData(symbolTable,symbolName, *symbolValue, symbolAttributes);

	}
}



// Functions related to the handle of arguments
// method that will receive an argument from the action line and will output the kind of miun needed
// 0 ,1,2,3
// It will know by the criteria of each miun
char* findMatchedMiun(char* argmntFromLine, symbolList* symbolTable) {

	int resultOfMiunChecks;
	char* miunMethod= "";

	resultOfMiunChecks = isMiunZero(argmntFromLine); // Miun 0

	if (resultOfMiunChecks == FALSE) {	
		resultOfMiunChecks = isMiunTwo(argmntFromLine, symbolTable); // miun 2

		if (resultOfMiunChecks == FALSE) {		
			resultOfMiunChecks = isMiunThree(argmntFromLine); // miun 3

			if (resultOfMiunChecks == FALSE) {

				/*if (resultOfMiunChecks == TRUE)	*/// miun 1 - only if not all miun check were valid
					return "01\0";
			}
			else
				return "11\0";
		}
		else
			return "10\0";
	}
	else
		return "00\0";
	

	//return miunMethod;

}


// this function receive a argument from the array of arguments and return the Register Code- for inserting to the row.
char* getRegisterCode(char* argFromLine) {

	int i, foundRegister = FALSE, indexOfColon, resultCmp, isMiunIndex = FALSE, indexOfStartBrace, indexOfLastBrace;

	char** registerValuesTable = returnRegistersValues();
	char* currRegisterName = NULL;
	char* currRegisterRow = malloc(sizeof(char) * 9);
	char* regFromArg = NULL;

	char* regVal = NULL;

	if (isRegsiter(argFromLine) == TRUE) {

		if (isValidRegister(argFromLine) == FALSE) {
			printf("ERROR - Not valid Register name");
			return;
		}

		if (strstr(argFromLine, "[") != NULL) {
			isMiunIndex = TRUE;
			indexOfStartBrace = returnFirstIndexOfChar(argFromLine, '[');
			indexOfLastBrace = returnFirstIndexOfChar(argFromLine, ']');
			regFromArg = subString(argFromLine, indexOfStartBrace + 1, indexOfLastBrace);
		}

		for (i = 0; i < REGISTERS_NO && !foundRegister; i++) {

			// if the i is smaller than 9 - split by 2 first chars
			currRegisterRow = registerValuesTable[i];
			indexOfColon = returnFirstIndexOfChar(currRegisterRow, ':');

			currRegisterName = subString(currRegisterRow, 0, indexOfColon);

			// Only if the miun is a 
			if (isMiunIndex == TRUE) {
				resultCmp = strcmp(currRegisterName, regFromArg);
			}
			else  {
				resultCmp = strcmp(currRegisterName, argFromLine);
			}
			

			if (resultCmp == 0) {
				foundRegister = TRUE;
				regVal = subString(currRegisterRow, indexOfColon + 1, strlen(currRegisterRow));
			}
		}

		/*	free(currRegisterName);
			free(currRegisterRow);*/

		return regVal;
	}
	else
		return "0000\0";

}

// Helper finction to convert an integer to a 16 digit binary data
char* convertNumberToBinaryString(int numberToConvert) {

	char binaryNumber[LENGTH_OF_BIN_NUMBER] = { 0 };

	int numberBuff = 0, i, isPositive = TRUE;


	//If the number is negative - handle it
	if (numberToConvert < 0) {
		isPositive = FALSE;
		numberToConvert += 1;
		numberToConvert = abs(numberToConvert);
	}

	// Calculate the bits as necessary
	for (i = LENGTH_OF_BIN_NUMBER - 1; i >= 0 && numberToConvert > 0; i--) {

		binaryNumber[i] = (numberToConvert % 2) + '0';
		numberToConvert = numberToConvert / 2;
	}

	// switch all other bits to '0'
	for (i; i >= 0; i--) {
		binaryNumber[i] = '0';
	}

	// Flip the bits if necessary
	if (!isPositive) {

		for (i = 0; i < LENGTH_OF_BIN_NUMBER; i++) {
			if (binaryNumber[i] == '0')
				binaryNumber[i] = '1';
			else
				binaryNumber[i] = '0';
		}
	}

	return &binaryNumber;
}


// _------- Open
// // 1. '.data' -> 2. '.string' -> 3. '.entry' -> 4. '.extern'
// Handle scenraio of Directive Row 
void handleDirectiveRowScenario(char* rowFromCode) {


}


//- OPEN 
//To handle the .entry directive
// if there is an entry directive - create new symbol with "entry"
void handleDirectiveEntry() {



}


//To handle the .extern directive
// if there is an entry directive - create new symbol with "external"
void handleDirectiveExtern() {

}


//To handle the .data directive
void handleDirectiveData(machineCode* dataMachineCode,  char** arrayOfArgs, int lengthOfArr, int* pToDataCounter) {

	int i;

	char* pToBin;

	printf(" Words to insert:\n ");

	// iterate on all the array of arguments just for params and enter each in new Machine code word
	for (i = 1; i < lengthOfArr; i++) {

		pToBin = malloc(sizeof(char) * LENGTH_OF_BIN_NUMBER);

		// Binary Representation of the number
		if (pToBin!=NULL)
			strcpy(pToBin, convertNumberToBinaryString(atoi(arrayOfArgs[i])));
		
		insertNewCodeWordDirectiveValue(dataMachineCode, pToBin, *pToDataCounter);

		*pToDataCounter = (*pToDataCounter) + 1;
	}


}


//To handle the .string directive
void handleDirectiveString(machineCode* dataMachineCode, char* stringFromCodeArray, int* pToDataCounter) {
	
	int lengthOfStringToEnter, i;
	char currChar;
	char* stringToEnter;
	char* pToBin;

	// this is the length due the final char that signals end of string
	lengthOfStringToEnter = strlen(stringFromCodeArray) - 1;
	
	stringToEnter = subString(stringFromCodeArray,1,strlen(stringFromCodeArray)-1);
	
	strncat(stringToEnter,"\0", 1);

	for (i = 0; i < lengthOfStringToEnter; i++) {

		currChar = stringToEnter[i];

		pToBin = malloc(sizeof(char) * LENGTH_OF_BIN_NUMBER);

		if (pToBin != NULL)
			strcpy(pToBin, convertNumberToBinaryString((int)currChar));

		insertNewCodeWordDirectiveValue(dataMachineCode, pToBin, *pToDataCounter);

		*pToDataCounter = (*pToDataCounter) + 1;
	}

}


// Handle scenraio of action Row 
void handleActionRowScenario(machineCode* actionsMachineCode, symbolList* symbolTable, char** arrayOfArgs, int lengthOfArr, int* pToActionsCounter) {

	// there are 3 goups of action: 0 args, 1 args, 2 args - those will be the groupFlags
	
	int i, groupOfAction = -1, opCode, amountOfArgs,isValidArgsNumber ;
	char* currRegCode = NULL;

	// Check if the Opcode of this actin is exist
	opCode = getOpcodeAction(arrayOfArgs[0]);
	//printf("Opcode: %d", opCode);

	// handle the action - first cell of array
	// apply all validations of the name
	if (opCode == -1) {
		printf("ERROR - Not valid Action Entered");
		return;
	}

	// handle the action in the code
	insertNewOpCodeWord(actionsMachineCode, arrayOfArgs[0], opCode, *pToActionsCounter);
	
	(*pToActionsCounter) = (*pToActionsCounter) + 1;

	//handle the argument validations
	amountOfArgs = lengthOfArr - 1;

	// check for valid param number for this Action
	isValidArgsNumber = isValidParamNumber(lengthOfArr - 1, opCode);

	if (isValidArgsNumber > 0) {
		// will be 2 or 1
		// insert second word for hole row code
		insertNewFullCodeWord(actionsMachineCode, symbolTable, arrayOfArgs, (*pToActionsCounter), isValidArgsNumber);
		(*pToActionsCounter) = (*pToActionsCounter) + 1;

		// handle the additional rows for each argument
		insertAdditionalWords(actionsMachineCode, symbolTable, arrayOfArgs, amountOfArgs, pToActionsCounter);
	}

}




// OPEN ------ MUST !
// functin that will get the line from the file and split it to different strings in a new array
void analyzeCodeRow(symbolList* symbolTable, machineCode* actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int* instructCounter, int* dataCounter, int* validationFlag) {

	char* newSymbolName = NULL;
	char* restOfRowFromCode = NULL;
	char newSymbolAttribute[MAX_LENGTH_OF_ATTRBIUTE];
	char** arrayOfArgumentFromCode = NULL;

	int	i, localValidationFlag, lengthOfArr,
		whiteSpaceLine, commentLine, rowHasSymbol, actionRow, directiveRow, typeOfDirective, commaLocation;

	int* localActionsCounter = malloc(sizeof(int));

	//localActionsCounter = instructCounter;

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
		printf("\nSymbol Name:%s	;", newSymbolName);
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

	//printf("\nAction - %d; Directive - %d ;Symbol - %d\n Counters: ic: %d	\t dc:%d\n ", actionRow, directiveRow, rowHasSymbol, instructCounter, dataCounter);

	//Get the array of arguments from the current Row
	arrayOfArgumentFromCode = buildArrayOfRowParams(restOfRowFromCode, &lengthOfArr);

	// validate the all array
	localValidationFlag = validateRowOfCode(arrayOfArgumentFromCode, lengthOfArr);

	// Edit the validation Flag for this file
	(*validationFlag) = localValidationFlag;

	// handle an directive row 
	if (directiveRow) {		

		typeOfDirective = isDirectiveLine(rowFromCode);

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
			
			// Insert a new data machine code words accordingly
			if (typeOfDirective == 1) {
				printf("\n Insert data machine code ");
				handleDirectiveData(dataMachineCode, arrayOfArgumentFromCode, lengthOfArr, dataCounter);
			}
			else {
				printf("\n Insert String machine code ");
				handleDirectiveString(dataMachineCode, arrayOfArgumentFromCode[1], dataCounter);
			}
		}
	}
	// handle an action row
	if (actionRow) { 		

		if (rowHasSymbol == TRUE) {
			//Handle action scenario
			handleSymbolScenario(&symbolTable, newSymbolName, "code", instructCounter);
		}
		printf("\n\BEfore inserting in analyze code - actionsCounter: %d\n\n", *instructCounter);

		// Handle the rest of the logic for action
		handleActionRowScenario(actionsMachineCode, symbolTable, arrayOfArgumentFromCode, lengthOfArr, instructCounter);

		//handleActionRowScenario(actionsMachineCode, symbolTable, arrayOfArgumentFromCode, lengthOfArr, localActionsCounter);

		//printf("\n\nAfter inserting in analyze code - actionsCounter: %d\n\n", *instructCounter);

		//printf("\n\nAfter inserting in analyze code - actionsCounter: %d\n\n", *localActionsCounter);

	}
	//&instructCounter = (*localActionsCounter);


	free(arrayOfArgumentFromCode);
}

