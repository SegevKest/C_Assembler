#pragma once
#ifndef __WORDINCODE_H
#define __WORDINCODE_H

#include "symbol.h"

typedef struct wordInCode machineCode;



void insertNewOpCodeWord(machineCode** machCodeTable, char actionName[], int opCodeToTurnOn, int valueOfAction);  // this function insert the new first row of the action - OPCODE row
void insertNewFullCodeWord(machineCode** machCodeTable, symbolList* symbolTable, char** arrayOfArgs, int valueForNewWord, int numOfArgs);	 // this function insert the new second row of the action - FUNCT, origin and destination addresses
void displayWord(machineCode* machCode);	// This function print the current word of the machineCode

int getOpcodeAction(char actionName[]);		// get the opcode number of the action

void insertNewCodeWordDirectiveValue(machineCode** machCodeTable, char* binaryNumber, int valueForNewWord);		 // this function insert the row of the directive
void insertEmptyRowForNewWordsOfSymbol(machineCode** machCodeTable, int valueForNewWord);	// this function insert the new empty rows of the arguments symbol
void insertAdditionalWords(machineCode** actionsMachineCode, symbolList** symbolTable, char** argsFromLine, int numOfArgs, int* pToActionsCounter);		// insert additional rows for the arguments in the row

void printList(machineCode* head);		// this function will print the all list of machinedCodes

// Second PASS
// this function is handling the edit of the empty rows of symbols in the machine code.
// it will mofidy those words as required, after getting all their new data
void editEmptyRowsOfSymbol(machineCode** actionsMachineCode, symbolList** symbolTable, char** argsFromLine, int numOfArgs);


#endif //__WORDINCODE_H