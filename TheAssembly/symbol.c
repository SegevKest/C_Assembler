#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"

#define SYMBOL_MAX_LENGTH 31


typedef struct symbolNode
{
	char symbolName[SYMBOL_MAX_LENGTH];
	int value;
	int baseAddress;
	int offset;
	char* attributes[];

	struct symbolNode* nextSymbol;

};


// Operations:
// 1. Add new Symbol - adding symbol name, value, attributes + calculate the Base address and Offset in method
// 2. Add new attribute to existing symbol
// 3. Search a symbol in SymbolTable - by char array represent the Symbol Name - return true or false