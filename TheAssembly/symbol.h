#pragma once
#ifndef __SYMBOL_H
#define __SYMBOL_H


typedef struct symbolNode symbolList;

symbolList* insertNewSymbol(symbolList* symbolTable, char symbolName[], int valueOfSymbol, char* attribute[]);
void displaySymbol(symbolList* symbol);




#endif //__SYMBOL_H