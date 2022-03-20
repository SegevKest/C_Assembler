#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "helperFunctions.h"

#define TRUE 1
#define FALSE 0



int isCommentLine(char* rowFromCode);
int isWhiteSpacesLine(char* rowFromCode);
int isDirectiveLine(char* rowFromCode);
int isActionLine(char* rowFromCode);
int isSymbolArgmnt(char* argmntFromLine);
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

	if (strlen(trimmedRow) == 0)
		return TRUE;
	
	return FALSE;
}

// Check if the current line is a WhiteSpaces - return TRUE if yes, FALSE if not
int isWhiteSpacesLine(char* rowFromCode) {

	return 0;
}


// Check if the current line is Directive line - return TRUE if yes, FALSE if not
int isDirectiveLine(char* rowFromCode) {

	//is .data - line
	// is .string line
	//is .entry
	// is .extern
	return 0;
}


// Check if the current line is Action / Instruct line - return TRUE if yes, FALSE if not
int isActionLine(char* rowFromCode) {

	//is .data - line
	// is .string line
	//is .entry
	// is .extern
	return 0;
}




// this method will check if the argument is a Symbol or not and check its name and 
int isValidSymbolArgmnt(char* argmntFromLine) {


	return FALSE;

}

// Validations necessary

// check if the symbol that was located has a valid name
int isValidNameOfSymbol(char* symbolFromLine) {

	return FALSE;
}

int isValidRegister(char* argmntFromLine) {

	// first - check if the argmt is a register

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



