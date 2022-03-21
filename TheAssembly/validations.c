#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "helperFunctions.h"
#include "wordInCode.h"
#include "symbol.h"
#include "constantTables.h"


#define TRUE 1
#define FALSE 0
#define TOTAL_SAVED_NAMES_IN_PROG 36
#define MAX_LENGTH_OF_SAVE_NAME 9

int isCommentLine(char* rowFromCode);
int isWhiteSpacesLine(char* rowFromCode);
int isDirectiveLine(char* rowFromCode);
int isActionLine(char* rowFromCode);
int isRowContainSymbol(char* rowFromCode);
int isValidSymbolArgmnt(char* argmntFromLine);

int isValidRegister(char* argmntFromLine);
int isValidNameOfSymbol(char* symbolFromLine);
int isValidSeperationBetweenActionAndParam(char* rowFromCode);
int isValidSeperationBetweenParams(char* rowFromCode);

//Miun Functions
int isMiunZero(char* argmntFromLine);
int isMiunOne(char* argmntFromLine);
int isMiunZTwo(char* argmntFromLine);
int isMiunThree(char* argmntFromLine);



// method that will be responsible for validating the line and the arguments



// Check if the current line is a comment - return TRUE if yes, FALSE if not
int isCommentLine(char* rowFromCode) {

	char* trimmedRow = getTrimmedCodeRow(rowFromCode);

	if (trimmedRow[0] == ';')
		return TRUE;

	return FALSE;

}

// Check if the current line is a WhiteSpaces - return TRUE if yes, FALSE if not
int isWhiteSpacesLine(char* rowFromCode) {

	char* trimmedRow = getTrimmedCodeRow(rowFromCode);

	if (strlen(trimmedRow) == 0)
		return TRUE;

	return FALSE;

}


// Check if the current line is Directive line - return TRUE if yes, FALSE if not
// This function will return the number of Directive if it is Found - else 0
int isDirectiveLine(char* rowFromCode) {

	// 1. '.data' -> 2. '.string' -> 3. '.entry' -> 4. '.extern'

	int directiveNo = 0;

	if ( strstr(rowFromCode, ".data") != NULL)
		directiveNo = 1;
	else if (strstr(rowFromCode, ".string") != NULL)
		directiveNo = 2;
	else if (strstr(rowFromCode, ".entry") != NULL)
		directiveNo = 3;
	else if (strstr(rowFromCode, ".extern") != NULL)
		directiveNo = 4;
	
	return directiveNo;
}


// Check if the current line is Action / Instruct line - return TRUE if yes, FALSE if not
int isActionLine(char* rowFromCode) {

	// if this line is not a directive (and not empty or comment ) - this is an Action line
	if (!isDirectiveLine(rowFromCode))
		return TRUE;

	return FALSE;
}


// Check if the row of code contains a colon - represnt the end of declaring a symbol
int isRowContainSymbol(char* rowFromCode) {

	//check for existing symbol at the sta
	int indexOfColon = returnFirstIndexOfChar(rowFromCode, ':');

	// only if found a 
	if (indexOfColon >= 0 && indexOfColon <= strlen(rowFromCode))
		return TRUE;

	return FALSE;
}

// Should remove??
// this method will check if the argument is a Symbol or not and check its name and 
int isValidSymbolArgmnt(char* argmntFromLine) {


	return FALSE;

}


// Validations necessary

//--------open 
// check if the symbol that was located has a valid name
int isValidNameOfSymbol(char* symbolFromLine) {

	int i, rsltOfCompare=0, foundMatch = FALSE;
	char** currSavedName = malloc (TOTAL_SAVED_NAMES_IN_PROG * sizeof(char* ));
	char** savedNamesTable = returnSavedNamesTable();

	for (i = 0; i < TOTAL_SAVED_NAMES_IN_PROG && !foundMatch; i++) {
		
		currSavedName[i] = malloc(MAX_LENGTH_OF_SAVE_NAME+1 * sizeof(char));
		strcpy(currSavedName[i], savedNamesTable[i]);
		//currSavedName = savedNamesTable[i];
		rsltOfCompare = strcmp(currSavedName[i], symbolFromLine);

		// if the result is 0 - means there was a match in the saved names
		if (rsltOfCompare == 0)
			foundMatch = TRUE;

		/*free(currSavedName[i]);*/
	}
	
	if (foundMatch == TRUE)
		return FALSE;

	return TRUE;
}


int isValidRegister(char* rgstrFromLine) {

	// first - check if the argmt is a register
	char firstCharOfrgstr = rgstrFromLine[0];
	char* restOfrgstrArg;


	int validRegister = FALSE;

	if (firstCharOfrgstr == 'r')
	// only if true - check if it exist in the contant table

	return FALSE;
}

// the method will check if the seperation of all the arguments are in order
int isValidSeperationBetweenParams(char* rowFromCode) {

}

// the method will check if the seperation of all the arguments are in order
int isValidSeperationBetweenActionAndParam(char* rowFromCode) {

}




// Methods to check the type of the Miun of an argument

//identify miun 0 exc,
int isMiunZero(char* argmntFromLine) {

	// the operand will be in format : "#{int}"
	return *argmntFromLine == '#' ? TRUE : FALSE;
}

int isMiunOne(char* argmntFromLine) {

	// check if the argument is a Symbol
	return FALSE;


}
int isMiunZTwo(char* argmntFromLine) {

	// if containa  name of a symbol and concat  [{register}]
	return FALSE;

}
int isMiunThree(char* argmntFromLine) {
	return FALSE;

}



