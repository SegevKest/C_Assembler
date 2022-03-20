#pragma once
#ifndef __helperFunctions_H
#define __helperFunctions_H


// return the 
int returnFirstIndexOfChar(char* stringToCheck, char charToFind);
char* subString(char* sourceString, int strtIndex, int endIndex);
int returnLastIndexOfChar(char* stringToCheck, char charToFind);

//Trim row
char* getTrimmedCodeRow(char* rowFromCode);

void analyzeCodeRow(symbolList* symbolTable, machineCode* actionsMachineCode, machineCode* dataMachineCode, char* rowFromCode, int instructCounter, int dataCounter);


#endif //__helperFunctions_H