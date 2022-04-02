#pragma once
#ifndef __helperFunctions_H
#define __helperFunctions_H

#include "wordInCode.h"
#include "symbol.h"

#define REGISTERS_NO 16
#define MAX_LENGTH_OF_PARAM 12
#define LENGTH_OF_BIN_NUMBER 16


int returnFirstIndexOfChar(char* stringToCheck, char charToFind);		// this function will return the first Index of the char from the string
char* subString(char* sourceString, int strtIndex, int endIndex);		// this functino will return the subString from the sourceString between the start and end index  
int returnLastIndexOfChar(char* stringToCheck, char charToFind);	// this function will return the last Index of the char from the string

//Trim row
char* getTrimmedCodeRow(char* rowFromCode);		// this function will trim the row of code from both sides
void handleSymbolScenario(symbolList** symbolTable, char* symbolName, char* symbolAttributes, int* symbolValue); // this function will handle the symbol scenraio if found
// this function will handle the action scenraio if found
void handleActionRowScenario(machineCode** actionsMachineCode, symbolList* symbolTable, char** arrayOfArgs, int lengthOfArr, int* pToActionsCounter); 
char* convertNumberToBinaryString(int numberToConvert);	// this method will convert an integer number to the binary string 
char* getRegisterCode(char* argFromLine);		// this method will return the register binary code from the constant table
char* findMatchedMiun(char* argmntFromLine, symbolList* symbolTable);		// this method will return the miun binary code from the constant table

int isString(char* stringToCheck);	// this function  checks if the string is an argument is a string or contain some digits

// this function will be responsible for analyzing each code of row - from the file
void analyzeCodeRow(symbolList* symbolTable, machineCode** actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int* instructCounter, int* dataCounter, int* validationFlag);
// This function will be responsible for analyzing each code of row from file in second pass
void analyzeCodeRowSecondPass(symbolList** symbolTable, machineCode** actionsMachineCode, machineCode** dataMachineCode, char* rowFromCode, int* instructCounter, int* dataCounter, int* validationFlag);

#endif //__helperFunctions_H