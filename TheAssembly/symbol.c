#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "symbol.h"

#define SYMBOL_MAX_LENGTH 31
#define OFFSET_CALCULATE 16
#define MAX_ATTRIBUTES_VALUE 6


#define TRUE 1
#define FALSE 0

typedef struct symbolNode
{
	char symbolName[SYMBOL_MAX_LENGTH];
	int value;
	int baseAddress;
	int offset;
	char* attributes[MAX_ATTRIBUTES_VALUE];

	struct symbolNode* nextSymbol;

};


// Allocate memory to symbol and return pointer to it
symbolList* createNewSymbol() {

	return (symbolList*)malloc(sizeof(symbolList));
}

// this method checks if a symbol is already in the symbol table - return the pointer if yes, null if no
void isSymbolAlreadyExist(symbolList* symbolTable, char symbolName[], symbolList* ret) {

	symbolList* ptr = NULL;
	int namesAreEqual;

	ptr = symbolTable;

	while (ptr->nextSymbol && ret) {

		namesAreEqual = strcmp((ptr->symbolName), symbolName);
		if (!namesAreEqual)		// return 0 if equal
		{
			ret = ptr;
		}
		else
		{
			ptr = ptr->nextSymbol;
		}
	}
}

// ----- Open 
// Function to create a new symbol from given parameters
// It will calculate the BaseAddress + Offset and will add it to the new Symbol
// Then - iterate until end of symbolTable and insert the newSybol at the end 
symbolList* insertNewSymbol(symbolList* symbolTable, char symbolName[], int valueOfSymbol, char* attribute[]) {

	int symbolExist = FALSE, newSymbolOffset, newSymbolBaseAdd;
	symbolList *newSymbol=NULL,*ret=NULL;

	isSymbolAlreadyExist(symbolTable, symbolName, ret);

	if (ret!=NULL)
		symbolExist = TRUE;
	else
		symbolExist = FALSE;

	if (!symbolExist) {
		newSymbol = createNewSymbol();

		if (newSymbol) {

			//Calculate offset + baseAdress
			newSymbolOffset = valueOfSymbol % OFFSET_CALCULATE;
			newSymbolBaseAdd = valueOfSymbol - newSymbolOffset;

			newSymbol->value = valueOfSymbol;
			newSymbol->baseAddress = newSymbolBaseAdd;
			newSymbol->offset = newSymbolOffset;

		}
		else
			printf("Not enoght memory - error in Insert new Symbol");

	}
	else
		printf("The symbol already exists in the SymbolTable");
	
	// copy the symbolName Param to the SymbolName of the new Symbol
	return NULL;
}


// this function will check if this symbol needs an update to its values - if yes - will update it
int shoudAddValueAddrsOffset(symbolList* symbolTable) {

	return 0;
}

// the method will print the stymbol to machine code format - binary
void printToMachineCode(symbolList* symbolTable) {

}
// Operations:
// 1. Add new Symbol - adding symbol name, value, attributes + calculate the Base address and Offset in method
// 2. Add new attribute to existing symbol
// 3. Search a symbol in SymbolTable - by char array represent the Symbol Name - return true or false







void displaySymbol(symbolList* symbol) {

	symbolList* ptr = symbol;


	int i = 1;
	if (ptr == NULL)
		printf("\Symbol list is empty.\n");
	else
	{
		printf("\nSr. No.\t\PrgramWordValue\t\tIsCompleted\t\tLink\n");

		while (ptr != NULL)
		{
			printf("\n%d.\t \t%d\t \t%s\t \t%d\t %d\n\t %d\n\t %d\n", i, ptr, ptr->baseAddress, ptr->value, ptr->symbolName, ptr->offset,
				ptr->nextSymbol);
			ptr = ptr->nextSymbol;
			i++;

		}
	}
	free(ptr);

}