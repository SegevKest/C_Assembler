#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "symbol.h"

#define SYMBOL_MAX_LENGTH 31
#define OFFSET_CALCULATE 16
#define MAX_ATTRIBUTES_LENGTH 15
#define MAX_SAVED_LINES_LENGTH 2


#define TRUE 1
#define FALSE 0


void isSymbolAlreadyExist(symbolList* symbolTable, char symbolName[], symbolList* ret);
void insertNewSymbolData(symbolList** symbolTable, char symbolNameParam[], int valueOfSymbol, char* attributeParam);
void insertSymbolToEndOfList(symbolList** symbolTable, symbolList* newSymbolToInsert);
void printSymList(symbolList* head);

void insertEmptySymbolWithSavedLines(symbolList** symbolTable, char* symbolName, int* savedLinesOfSymbol);


typedef struct symbolNode
{
	char symbolName[SYMBOL_MAX_LENGTH];
	int value;
	int baseAddress;
	int offset;
	int noOfAttributes;

	/*char* attributes[MAX_ATTRIBUTES_VALUE];*/

	int* savedLinesInCode;	// the saved lines in the code
	char* attributes;	// the attributes of the current symbol

	struct symbolNode* nextSymbol;
};


// Allocate memory to symbol and return pointer to it
symbolList* createNewSymbol() {


	symbolList* newSym = (symbolList*)malloc(sizeof(symbolList));
	newSym->attributes = (char*)malloc(sizeof(char) * MAX_ATTRIBUTES_LENGTH);
	newSym->savedLinesInCode = (int*)calloc(MAX_SAVED_LINES_LENGTH, sizeof(int));

	return newSym;
}

// this method checks if a symbol is already in the symbol table - return the pointer if yes, null if no
void isSymbolAlreadyExist(symbolList** symbolTable, char symbolName[], symbolList* ret) {

	symbolList* ptr = *symbolTable;
	char* p;
	int namesAreEqual;

	//displaySymbol(ptr);

	if (ptr != NULL) {

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


// this function will be used to insert a new symbol to the end of the symbol table that exist
void insertSymbolToEndOfList(symbolList** symbolTable, symbolList* newSymbolToInsert) {

	symbolList* pSymbol;

	if (*symbolTable == NULL) {

		*symbolTable = newSymbolToInsert;
		(*symbolTable)->nextSymbol = NULL;
	}
	else
	{
		pSymbol = *symbolTable;

		while (pSymbol->nextSymbol != NULL)
			pSymbol = pSymbol->nextSymbol;

		pSymbol->nextSymbol = newSymbolToInsert;
	}

}


// -----Open - issue with inserting
// Function to create a new symbol from given parameters
// It will calculate the BaseAddress + Offset and will add it to the new Symbol
// Then - iterate until end of symbolTable and insert the newSybol at the end 
void insertNewSymbolData(symbolList** symbolTable, char symbolNameParam[], int valueOfSymbol, char* attributeParam) {

	printf("\nName of symbol: %s, value:  %d ", symbolNameParam, valueOfSymbol);

	int i, j;
	int symbolExist = FALSE, newSymbolOffset, newSymbolBaseAdd;
	symbolList* newSymbol = NULL;
	symbolList* ret = NULL;

	//symbolList* pToSymbolinTable = symbolTable;

	isSymbolAlreadyExist(symbolTable, symbolNameParam, ret);

	if (ret!=NULL)
		symbolExist = TRUE;
	else
		symbolExist = FALSE;
	

	// if the symbol not located on table
	if (!symbolExist) {
		newSymbol = createNewSymbol();

		if (newSymbol) {

			//displaySymbol(newSymbol);
			// insert the name of the symbol

			//(*valueOfSymbol) = (*valueOfSymbol) + 1;

			strcpy(newSymbol->symbolName, symbolNameParam);

			//Calculate offset + baseAdress
			newSymbolOffset = valueOfSymbol % OFFSET_CALCULATE;
			newSymbolBaseAdd = valueOfSymbol - newSymbolOffset;

			newSymbol->value = valueOfSymbol;
			newSymbol->baseAddress = newSymbolBaseAdd;
			newSymbol->offset = newSymbolOffset;
			
			// Attributes array will be initialized -
			newSymbol->noOfAttributes = 1;
			newSymbol->nextSymbol = NULL;

			//The part is not working!!
			//strcpy(newSymbol->attributes[0], attributeParam);

			strcpy(newSymbol->attributes, attributeParam);
			{
				//The part is not working!!
				 //INsert to the existing table at the end
				/*while (pToSymbolinTable != NULL)
					pToSymbolinTable = pToSymbolinTable->nextSymbol;

				pToSymbolinTable->nextSymbol = newSymbol;
				pToSymbolinTable = pToSymbolinTable->nextSymbol;
				pToSymbolinTable->nextSymbol = NULL;*/

			}

			insertSymbolToEndOfList(symbolTable, newSymbol);

			printf("All values fixed - inserted new symbol");
			printSymList(*symbolTable);
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
	
	//free(pToSymbolinTable);

}


// the method will print the stymbol to machine code format - binary
void printToMachineCode(symbolList* symbolTable) {

}
// Operations:
// 1. Add new Symbol - adding symbol name, value, attributes + calculate the Base address and Offset in method
// 2. Add new attribute to existing symbol
// 3. Search a symbol in SymbolTable - by char array represent the Symbol Name - return true or false


// this function will insert a symbol without any values - only the name of the symbol and the saved lines indexes
void insertEmptySymbolWithSavedLines(symbolList** symbolTable, char* symbolName, int* savedLinesOfSymbol) {

	symbolList* newEmptySymbol = NULL;
	int i, noNewLines = 2;

	newEmptySymbol = createNewSymbol();
	// insert the new symbol name
	strcpy(newEmptySymbol->symbolName, symbolName);

	// copy the saved Lines to the savedLines
	for (i = 0; i < noNewLines; i++) {
		newEmptySymbol->savedLinesInCode[i] = savedLinesOfSymbol[i];
	}

	// insert the current empty symbol to the symbol table
	insertSymbolToEndOfList(symbolTable, newEmptySymbol);

}


void displaySymbol(symbolList* symbol) {

	symbolList* ptr = symbol;
	symbolList** currSymbolAttr;

	int i;
	if (ptr == NULL)
		printf("\Symbol list is empty.\n");
	else
	{
		printf("\nSr. No.\t\symbolName\t\tvalue\t\tOffset\t\tBase\t\t\n");
		printf("\n%d\t\%s\t\t%d\t\t%d\t\t%d\t\t\n", ptr->symbolName,ptr->value, ptr->offset, ptr->baseAddress);
		currSymbolAttr = ptr->attributes;

		printf("\nAttirbutes:\n");

	/*	for (i = 0; i < ptr->noOfAttributes; i++) {
			printf("%s", currSymbolAttr[i]);
		}*/
	}
	free(ptr);

}



void printSymList(symbolList* head) {

	printf("\n The linked list of machine code is\n");

	while (head != NULL)
	{
		printf(" %d ", head->value);
		head = head->nextSymbol;
	}
}


