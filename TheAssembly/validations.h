#pragma once
#ifndef __validations_H
#define __validations_H


#include "symbol.h"

int isCommentLine(char* rowFromCode);
int isWhiteSpacesLine(char* rowFromCode);

int isRowContainSymbol(char* rowFromCode);
int isValidNameOfSymbol(char* symbolFromLine);

int isDirectiveLine(char* rowFromCode);
int isActionLine(char* rowFromCode);

int isRegsiter(char* argFromLine);
int isValidRegister(char* argmntFromLine);
int isValidParamNumber(int amountOfArgs, int opCode);


int validateRowOfCode(char** arrayOfArgumentFromCode, int lengthOfArr);


//Miun Functions
int isMiunZero(char* argmntFromLine);
int isMiunOne(char* argmntFromLine, symbolList* symbolTable);
int isMiunTwo(char* argmntFromLine, symbolList* symbolTable);
int isMiunThree(char* argmntFromLine);

#endif