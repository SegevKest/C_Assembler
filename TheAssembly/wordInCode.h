#pragma once
#ifndef __WORDINCODE_H
#define __WORDINCODE_H

#include "symbol.h"

typedef struct wordInCode machineCode;

void insertNewOpCodeWord(machineCode* machCodeTable, char actionName[], int opCodeToTurnOn, int valueOfAction);
void insertNewFullCodeWord(machineCode* machCodeTable, symbolList* symbolTable, char** arrayOfArgs, int valueForNewWord, int numOfArgs);
void displayWord(machineCode* machCode);

int getOpcodeAction(char actionName[]);


void insertNewCodeWordDirectiveValue(machineCode* machCodeTable, char* binaryNumber, int valueForNewWord);
void insertEmptyRowForNewWordsOfSymbol(machineCode* machCodeTable, int valueForNewWord);
void insertAdditionalWords(machineCode* actionsMachineCode, symbolList* symbolTable, char** argsFromLine, int numOfArgs, int* pToActionsCounter);



#endif //__WORDINCODE_H