#pragma once
#ifndef __SYMBOL_H
#define __SYMBOL_H

#define SYMBOL_MAX_LENGTH 31

typedef struct symbolNode symbolList;

// this function will insert new symbol if it is not exist - or add new data to the symbol that exist
void insertNewSymbolData(symbolList** symbolTable, char symbolNameParam[], int* valueOfSymbol, char* attributeParam);
void isSymbolAlreadyExist(symbolList* symbolTable, char symbolName[], symbolList** ret);	// check if the symbol exist in the list
void displaySymbol(symbolList* symbol);		// function to print the symbol
void insertEmptySymbolWithSavedLines(symbolList** symbolTable, char* symbolName, int* savedLinesOfSymbol);	// function to insert a symbol with empty values - but the saved lines and names
void printSymList(symbolList* head);	// this functino print the all symbol list

#endif //__SYMBOL_H