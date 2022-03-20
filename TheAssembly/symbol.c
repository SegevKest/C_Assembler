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
	int noOfAttributes;

	char* attributes[MAX_ATTRIBUTES_VALUE];

	struct symbolNode* nextSymbol;

};


// Allocate memory to symbol and return pointer to it
symbolList* createNewSymbol() {

	return (symbolList*)malloc(sizeof(symbolList));
}

// this method checks if a symbol is already in the symbol table - return the pointer if yes, null if no
void isSymbolAlreadyExist(symbolList* symbolTable, char symbolName[], symbolList* ret) {

	symbolList* ptr = symbolTable;
	char* p;
	int namesAreEqual;

	displaySymbol(ptr);

	if (symbolTable != NULL) {

		while (ptr->nextSymbol != NULL && ret) {

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
}

// Function to create a new symbol from given parameters
// It will calculate the BaseAddress + Offset and will add it to the new Symbol
// Then - iterate until end of symbolTable and insert the newSybol at the end 
void insertNewSymbolData(symbolList* symbolTable, char symbolNameParam[], int valueOfSymbol, char* attributeParam) {

	printf("%s, val:  %d, , ", symbolNameParam, valueOfSymbol);

	int i, j;
	int symbolExist = FALSE, newSymbolOffset, newSymbolBaseAdd;
	symbolList *newSymbol=NULL,*ret=NULL;

	symbolList* pToSymbolinTable = symbolTable;

	isSymbolAlreadyExist(symbolTable, symbolNameParam, ret);

	

	if (ret!=NULL)
		symbolExist = TRUE;
	else
		symbolExist = FALSE;
	

	// if the symbol not located on table
	if (!symbolExist) {
		newSymbol = createNewSymbol();

		if (newSymbol) {

			displaySymbol(newSymbol);
			// insert the name of the symbol
			strcpy(newSymbol->symbolName, symbolNameParam);

			//Calculate offset + baseAdress
			newSymbolOffset = valueOfSymbol % OFFSET_CALCULATE;
			newSymbolBaseAdd = valueOfSymbol - newSymbolOffset;

			newSymbol->value = valueOfSymbol;
			newSymbol->baseAddress = newSymbolBaseAdd;
			newSymbol->offset = newSymbolOffset;
			
			// Attributes array will be initialized -
			newSymbol->noOfAttributes = 1;
			strcpy(newSymbol->attributes[0], attributeParam);



			// INsert to the existing table at the end
			while (pToSymbolinTable->nextSymbol != NULL) 
				pToSymbolinTable = pToSymbolinTable->nextSymbol;
			
			pToSymbolinTable->nextSymbol = newSymbol;
			pToSymbolinTable = pToSymbolinTable->nextSymbol;
			pToSymbolinTable->nextSymbol = NULL;

			printf("All values fixed - inserted new symbol");
		}
		else
			printf("Not enoght memory - error in Insert new Symbol");

	}
	// located in the table - insert the values received as params to existing 1
	else    
	{
		printf("The symbol already exists in the SymbolTable - insert data");
		//Calculate offset + baseAdress

		// Will happen only if they change the values from 0 to something else
		if (valueOfSymbol > 0) {

			newSymbolOffset = valueOfSymbol % OFFSET_CALCULATE;
			newSymbolBaseAdd = valueOfSymbol - newSymbolOffset;

			ret->value = valueOfSymbol;
			ret->baseAddress = newSymbolBaseAdd;
			ret->offset = newSymbolOffset;
		}
		if (strlen(attributeParam) > 0)
		{
			// Attributes array will be initialized -
			newSymbol->noOfAttributes++;
			strcpy(newSymbol->attributes[newSymbol->noOfAttributes - 1], attributeParam);
		}
	}
	
	free(pToSymbolinTable);

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
		printf(" %s \n", ptr->symbolName);
	}
	free(ptr);

}