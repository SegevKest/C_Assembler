#pragma once
#ifndef __SYMBOL_H
#define __SYMBOL_H


typedef struct symbolNode symbolList;

void insertNewSymbolData(symbolList* symbolTable, char symbolNameParam[], int valueOfSymbol, char* attributeParam);
void isSymbolAlreadyExist(symbolList* symbolTable, char symbolName[], symbolList* ret);
void displaySymbol(symbolList* symbol);


#endif //__SYMBOL_H