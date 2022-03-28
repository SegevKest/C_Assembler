#include <stdlib.h>
#include <stdio.h>
#include<string.h>

#include "symbol.h"
#include "helperFunctions.h"
#include "wordInCode.h"
#include "constantTables.h"
#include "macroNode.h"

#define TRUE 1
#define FALSE 0
#define TOTAL_SAVED_NAMES_IN_PROG 36
#define MAX_LENGTH_OF_SAVE_NAME 9

// Common Validations
int isCommentLine(char* rowFromCode);
int isWhiteSpacesLine(char* rowFromCode);
int isDirectiveLine(char* rowFromCode);
int isActionLine(char* rowFromCode);
int isRowContainSymbol(char* rowFromCode);
int isValidSymbolArgmnt(char* argmntFromLine);
int isRegsiter(char* argFromLine);
int isValidRegister(char* argmntFromLine);
int isValidNameOfSymbol(char* symbolFromLine);
int isValidSeperationBetweenActionAndParam(char* rowFromCode);
int isValidSeperationBetweenParams(char* rowFromCode);
int validateRowOfCode(char** arrayOfArgumentFromCode, int lengthOfArr);
int isValidParamNumber(int amountOfArgs, int opCode);

//Miun Functions
int isMiunZero(char* argmntFromLine);
int isMiunOne(char* argmntFromLine, symbolList* symbolTable);
int isMiunTwo(char* argmntFromLine, symbolList* symbolTable);
int isMiunThree(char* argmntFromLine);


// File and Macro validations
int isExistMacro(macroTable** headOfMacroTable, char* argFromLine);



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

	if (firstCharOfrgstr == 'r' || strstr(argFromLine, "[") != NULL )
		return TRUE;
	return FALSE;
}

// Check if this is a valid register
int isValidRegister(char* rgstrFromLine) {

	// first - check if the argmt is a register
	char firstCharOfrgstr = rgstrFromLine[0];
	char* restOfrgstrArg;

	int validRegister = FALSE, strLength, rgstrNo, indexOfStartBrace, indexOfLastBrace;

	if (strstr(rgstrFromLine, "[") != NULL) {
		indexOfStartBrace = returnFirstIndexOfChar(rgstrFromLine, '[');
		indexOfLastBrace = returnFirstIndexOfChar(rgstrFromLine, ']');
		restOfrgstrArg = subString(rgstrFromLine, indexOfStartBrace + 1, indexOfLastBrace);
	}
	else
		restOfrgstrArg = subString(rgstrFromLine, 1, 3);




	strLength = strlen(rgstrFromLine);
	rgstrNo = atoi(restOfrgstrArg);

	if (rgstrNo < REGISTERS_NO && rgstrNo >= 0 && strLength > 1)
		return TRUE;
	
	return FALSE;
}
  

// the method will check if the seperation of all the arguments are in order
int isValidSeperationBetweenParams(char* paramFromCode) {

	if (strstr(paramFromCode, ",") != NULL) {
		printf("Found not valid seperation between arguments");
		return FALSE;
	}

	return TRUE;
}

// Add more???
// the method will check if the seperation of all the arguments are in order
// using tab - return 1
//using space - return 0
// not valid - return -1
int isValidSeperationBetweenActionAndParam(char* paramFromCode) {

	int isContainDirective = isDirectiveLine(paramFromCode);

	// location of action or directive is 0 all the rest are 
	if (strstr(paramFromCode, ",") != NULL || isContainDirective != 0 ) {

		if (isContainDirective == 1 && strlen(paramFromCode) > 6) {
			printf("The split between the first and second argument was not successfull");
		}
		else if ((isContainDirective == 2 || isContainDirective == 4) && strlen(paramFromCode) > 8) {
			printf("The split between the first and second argument was not successfull");
		}
		else if (isContainDirective == 3 && strlen(paramFromCode) > 7) {
			printf("The split between the first and second argument was not successfull");
		}
		else
		{
			// Means there was a directive 
			return TRUE;
		}
		return FALSE;
	}
	if (strstr(paramFromCode, "\t") != NULL) {
		printf("The split between the first and second argument was not successfull due TAB ");
		return FALSE;
	}
	return TRUE;

}



// This method will return 2,1,0 if the amount of arguments were valid and matched the group
// will return -1 if there was a error, after printing the error to user
int isValidParamNumber(int amountOfArgs, int opCode) {

	int result = -1;

	if (amountOfArgs >= 0) {

		// 2 arguments
		if (amountOfArgs == 2) {
			//Group 2	-- mov,cmp,add,sub,lea
			// the first argument is origin argument
			// the second argument is destination argument
			if (opCode == 0 || opCode == 1 || opCode == 2 || opCode == 4) {
				result = 2;
			}
			else
			{
				printf("ERROR: Not valid amount of arguments(%d) for action (OpCode:%d)", amountOfArgs, opCode);
				result = -1;
			}
		}
		else if (amountOfArgs == 1) {
			//Group 1 -- clr, not, inc, dec, jmp, bne, jsr, red, prn
			// the first argument is the destination argument
			if (opCode == 5 || opCode == 9 || opCode == 12 || opCode == 13) {
				result = 1;
			}
			else
			{
				printf("ERROR: Not valid amount of arguments(%d) for action (OpCode:%d)", amountOfArgs, opCode);
				result = -1;
			}
		}
		else
			result = 0;
	}
	else
	{
		printf("Error while getting the number of arguments ");
		result = -1;
	}

	return result;
}

// this method checks if the name of the action argument name is exist
int isValidNameOfAction(char* paramFromCode) {

	int resultOfOpCodeSearch = getOpcodeAction(paramFromCode);

	if (resultOfOpCodeSearch == -1)
		return FALSE;	// Didnt find any matched name of action

	return TRUE;		// means that there was a match while searching for the action and found match

}	


//Apply and combine all validations on all arguments - regarding the syntax
int validateRowOfCode(char** arrayOfArgumentFromCode, int lengthOfArr) {

	int i, isDirective = FALSE, isValidActionName = FALSE, isValidSeparation = FALSE, foundUnValidSeparation = FALSE;
	//int  = getLengthOfArgsArray(arrayOfArgumentFromCode);


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
	isValidSeparation = isValidSeperationBetweenActionAndParam(arrayOfArgumentFromCode[0]);
	
	if (isValidSeparation == FALSE)
		return FALSE;

	// Check every argument
	for (i = 1; i < lengthOfArr &&  !foundUnValidSeparation; i++) {

		isValidSeparation = isValidSeperationBetweenParams(arrayOfArgumentFromCode[i]);
		
		if (isValidSeparation == FALSE)
			foundUnValidSeparation = TRUE;
	}

	if (foundUnValidSeparation == TRUE)
		return FALSE;


	return TRUE;

}


// Methods to check the type of the Miun of an argument

//identify miun 0 exc, - the A,R,E of it will be - A!
int isMiunZero(char* argmntFromLine) {

	// the operand will be in format : "#{int}"

	if (strstr(argmntFromLine, "#") != NULL)
		return TRUE;
	
	return FALSE;


	//return *argmntFromLine == '#' ? TRUE : FALSE;
}

// if the argument is a symbol
int isMiunOne(char* argmntFromLine, symbolList* symbolTable) {

	// check if the argument is a Symbol
	symbolList* foundSymbol = NULL;

	isSymbolAlreadyExist(symbolTable, argmntFromLine,foundSymbol);

	if (foundSymbol == NULL)
			return FALSE;
	
	return TRUE;

}

// if containa  name of a symbol and concat  [{register}]
int isMiunTwo(char* argmntFromLine, symbolList* symbolTable) {

	int indexOfBrace;
	char* foundSymbol;

	/*symbolList* foundSymbolObj = NULL;*/

	if (strstr(argmntFromLine, "[") != NULL && strstr(argmntFromLine, "]") != NULL) {
		// found the braces - check if the symbol exist
		return TRUE;
	}
	return FALSE;

}

// if the argument is a register name
int isMiunThree(char* argmntFromLine) {

	if (isRegsiter(argmntFromLine) && isValidRegister(argmntFromLine))
		return TRUE;
	
	return FALSE;
}



// File and Macro validations

// this function checks if the current name from line is a macro
int isExistMacro(macroTable** headOfMacroTable, char* argFromLine) {

	if (returnMacro(headOfMacroTable, argFromLine) == NULL)
		return FALSE;
	return TRUE;
}