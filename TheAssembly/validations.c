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


// 1. '.data' -> 2. '.string' -> 3. '.entry' -> 4. '.extern'
// Check if the current line is Directive line - return TRUE if yes, FALSE if not
// This function will return the number of Directive if it is Found - else 0
int isDirectiveLine(char* rowFromCode) {


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
	}
	
	if (foundMatch == TRUE)
		return FALSE;

	return TRUE;
}


// this method will check if this argument is a Register
int isRegsiter(char* argFromLine) {

	char firstCharOfrgstr = argFromLine[0];

	if (firstCharOfrgstr == 'r')
		return TRUE;
	return FALSE;
}

// Check if this is a valid register
int isValidRegister(char* rgstrFromLine) {

	// first - check if the argmt is a register
	char firstCharOfrgstr = rgstrFromLine[0];
	char* restOfrgstrArg = subString(rgstrFromLine, 1, 3);

	int validRegister = FALSE, strLength, rgstrNo;

	strLength = strlen(rgstrFromLine);
	rgstrNo = atoi(restOfrgstrArg);

	if (rgstrNo < REGISTERS_NO && rgstrNo >= 0 && strLength > 1)
		return TRUE;
	
	return FALSE;
}
  

// the method will check if the seperation of all the arguments are in order
int isValidSeperationBetweenParams(char* paramFromCode) {

	if (strstr(paramFromCode, ",") != NULL) 
		return FALSE;
}

// the method will check if the seperation of all the arguments are in order
// using tab - return 1
//using space - return 0
// not valid - return -1
int isValidSeperationBetweenActionAndParam(char* paramFromCode) {

	// location of action or directive is 0 all the rest are 



}

// -----------OPEN
// Create the new table of relations between action - arg number...
int isValidParamNumber() {

}

// this method checks if the name of the action argument name is exist
int isValidNameOfAction(char* paramFromCode) {

	int resultOfOpCodeSearch = getOpcodeAction(paramFromCode);

	if (resultOfOpCodeSearch == -1)
		return FALSE;	// Didnt find any matched name of action

	return TRUE;		// means that there was a match while searching for the action and found match

}	


//
int validateRowOfCode(char** arrayOfArgumentFromCode, int lengthOfArr) {

	int isDirective = FALSE, isValidActionName = FALSE;
	//int i = getLengthOfArgsArray(arrayOfArgumentFromCode);


	isDirective = isDirectiveLine(arrayOfArgumentFromCode[0]);

	// validation on first Arg - the action or directive
	if (isDirective == 0) {	// is action
		isValidActionName = isValidNameOfAction(arrayOfArgumentFromCode[0]);
		
		if (isValidActionName == FALSE)
		{
			printf("Not a Valid action Name received");
			return FALSE;
		}
	}
	else        // Check for directive correct name
	{
		if (!(isDirective >= 1 && isDirective <= 4))
		{
			printf("Not a Valid Directive Name received");
			return FALSE;
		}
	}
	// check for valid sepatation of first agrs to other

	
	
	//for()


	return 0;

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


