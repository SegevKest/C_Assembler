#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "symbol.h"

#define SYMBOL_MAX_LENGTH 31
#define OFFSET_CALCULATE 16


#define TRUE 1
#define FALSE 0

typedef struct symbolNode
{
	char symbolName[SYMBOL_MAX_LENGTH];
	int value;
	int baseAddress;
	int offset;
	char* attributes[];

	struct symbolNode* nextSymbol;

};


// Allocate memory to symbol and return pointer to it
symbolList* createNewSymbol() {

	return (symbolList*)malloc(sizeof(symbolList));
}

// Function to create a new symbol from given parameters
// It will calculate the BaseAddress + Offset and will add it to the new Symbol
// Then - iterate until end of symbolTable and insert the newSybol at the end 
symbolList* insertNewSymbol(symbolList* symbolTable, char symbolName[], int valueOfSymbol, char* attribute[]) {

	int symbolExist = FALSE, newSymbolOffset, newSymbolBaseAdd;
	symbolList newSymbol;


	if (isSymbolAlreadyExist(&symbolName))
		symbolExist = TRUE;
	else
		symbolExist = FALSE;

	if (!symbolExist) {
		newSymbol = createNewSymbol();

		if (newSymbol) {

			//Calculate offset + baseAdress
			newSymbolOffset = valueOfSymbol % OFFSET_CALCULATE;
			newSymbolBaseAdd = valueOfSymbol - newSymbolOffset;

			newSymbol.value = valueOfSymbol;
			newSymbol.baseAddress = newSymbolBaseAdd;
			newSymbol.offset = newSymbolOffset;

		}
		else
			printf("Not enoght memory - error in Insert new Symbol");

	}
	else
		printf("The symbol already exists in the SymbolTable");
	
	// copy the symbolName Param to the SymbolName of the new Symbol

}

// this method checks if a symbol is already in the symbol table - return true if yes, false if no
int isSymbolAlreadyExist(symbolList* symbolTable, char symbolName[]) {

	symbolList *ptr = symbolTable;
	int namesAreEqual, foundMatch = FALSE;

	while (ptr.nextSymbol != NULL && !foundMatch ) {

		namesAreEqual = strcmp( (ptr.symbolName) , symbolName);
		if (!namesAreEqual)		// return 0 if equal
			foundMatch = TRUE;
		else
			ptr = ptr->nextSymbol;
	}

	return foundMatch;
}


// Operations:
// 1. Add new Symbol - adding symbol name, value, attributes + calculate the Base address and Offset in method
// 2. Add new attribute to existing symbol
// 3. Search a symbol in SymbolTable - by char array represent the Symbol Name - return true or false