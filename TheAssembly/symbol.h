#pragma once
#ifndef __SYMBOL_H
#define __SYMBOL_H

#define SYMBOL_MAX_LENGTH 31

typedef struct symbolNode symbolList;

void insertNewSymbolData(symbolList** symbolTable, char symbolNameParam[], int* valueOfSymbol, char* attributeParam);
void isSymbolAlreadyExist(symbolList* symbolTable, char symbolName[], symbolList** ret);
void displaySymbol(symbolList* symbol);
void insertEmptySymbolWithSavedLines(symbolList** symbolTable, char* symbolName, int* savedLinesOfSymbol);
void printSymList(symbolList* head);

#endif //__SYMBOL_H