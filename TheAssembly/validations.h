#pragma once
#ifndef __validations_H
#define __validations_H


#include "symbol.h"
#include "macroNode.h"



int isCommentLine(char* rowFromCode);		// the function will check if this row is a comment
int isWhiteSpacesLine(char* rowFromCode);	// the function will check if this a whiteSpaces row

int isRowContainSymbol(char* rowFromCode);	// this function checks if the row contains a symbol
int isValidNameOfSymbol(char* symbolFromLine);		// this function check if the name of the symbol is a valid name

int isDirectiveLine(char* rowFromCode);	// this function checks if the line is directive 
int isActionLine(char* rowFromCode);	// this function checks if the line contains action

int isRegsiter(char* argFromLine);		// this function checks if the argument is a register
int isValidRegister(char* argmntFromLine);	//this function checks if the register name is valid
int isValidParamNumber(int amountOfArgs, int opCode);	// this function checks if the number of arguments for this action are valid


int validateRowOfCode(char** arrayOfArgumentFromCode, int lengthOfArr);		// this function checks if the hole row has valid syntax


//Miun Functions
int isMiunZero(char* argmntFromLine);		// this function checks the miun type 0
int isMiunOne(char* argmntFromLine, symbolList* symbolTable);	// this function checks the miun type 1
int isMiunTwo(char* argmntFromLine, symbolList* symbolTable);	// this function checks the miun type 2
int isMiunThree(char* argmntFromLine);		// this function checks the miun type 3


// File and Macro's handling
int isExistMacro(macroTable** headOfMacroTable, char* argFromLine);		// this function checks the macro already exist in the macroList

#endif