#pragma once
#ifndef __helperFunctions_H
#define __helperFunctions_H

#include "wordInCode.h"
#include "symbol.h"

#define REGISTERS_NO 16
#define MAX_LENGTH_OF_PARAM 12
#define LENGTH_OF_BIN_NUMBER 16

// return the 
int returnFirstIndexOfChar(char* stringToCheck, char charToFind);
char* subString(char* sourceString, int strtIndex, int endIndex);
int returnLastIndexOfChar(char* stringToCheck, char charToFind);

//Trim row
char* getTrimmedCodeRow(char* rowFromCode);
void handleSymbolScenario(symbolList** symbolTable, char* symbolName, char* symbolAttributes, int* symbolValue);
void analyzeCodeRow(symbolList* symbolTable, machineCode** actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int* instructCounter, int* dataCounter, int* validationFlag);
void handleActionRowScenario(machineCode** actionsMachineCode, symbolList* symbolTable, char** arrayOfArgs, int lengthOfArr, int* pToActionsCounter);

char* convertNumberToBinaryString(int numberToConvert);
char* getRegisterCode(char* argFromLine);
char* findMatchedMiun(char* argmntFromLine, symbolList* symbolTable);

int isString(char* stringToCheck);

#endif //__helperFunctions_H