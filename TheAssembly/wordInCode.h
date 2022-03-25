#pragma once
#ifndef __WORDINCODE_H
#define __WORDINCODE_H


typedef struct wordInCode machineCode;

void insertNewOpCodeWord(machineCode* machCodeTable, char actionName[]);
void insertNewFullCodeWord(machineCode* machCodeTable);
void displayWord(machineCode* machCode);

int getOpcodeAction(char actionName[]);


void insertNewCodeWordDirectiveValue(machineCode* machCodeTable, char* binaryNumber, int valueForNewWord);
#endif //__WORDINCODE_H