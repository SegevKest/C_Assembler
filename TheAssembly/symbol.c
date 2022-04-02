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


void isSymbolAlreadyExist(symbolList** symbolTable, char symbolName[], symbolList** ret);
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
void isSymbolAlreadyExist(symbolList** symbolTable, char symbolName[], symbolList** ret) {

	symbolList* ptr = *symbolTable;
	char* p;
	int namesAreEqual;

	if (ptr != NULL) {

		while (ptr != NULL && !(* ret)) {

			namesAreEqual = strcmp((ptr->symbolName), symbolName);

			if (!namesAreEqual)		// return 0 if equal
			{
				*ret = ptr;
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

	symbolList* pSymbol = createNewSymbol();

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


// Function to create a new symbol from given parameters
// It will calculate the BaseAddress + Offset and will add it to the new Symbol
// Then - iterate until end of symbolTable and insert the newSybol at the end 
void insertNewSymbolData(symbolList** symbolTable, char symbolNameParam[], int valueOfSymbol, char* attributeParam) {

	int i, j;
	int symbolExist = FALSE, newSymbolOffset, newSymbolBaseAdd;
	symbolList* newSymbol = NULL;
	symbolList* ret = NULL;

	isSymbolAlreadyExist(symbolTable, symbolNameParam, &ret);

	if (ret!=NULL)
		symbolExist = TRUE;
	else
		symbolExist = FALSE;
	

	// if the symbol not located on table
	if (!symbolExist) {
		newSymbol = createNewSymbol();

		if (newSymbol) {

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
			newSymbol->nextSymbol = NULL;

			// insert the new attributes
			strcpy(newSymbol->attributes, attributeParam);

			insertSymbolToEndOfList(symbolTable, newSymbol);
		}
		else
			printf("Not enoght memory - error in Insert new Symbol");

	}
	// located in the table - insert the values received as params to existing 1
	else    
	{
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
			//check if need to init the noOfAttributes
			if (ret->noOfAttributes < 0 || ret->noOfAttributes > 2) {
				ret->noOfAttributes = 1;
				strcpy(ret->attributes, attributeParam);
			}
			else
			{
				ret->noOfAttributes++;
				strcat(ret->attributes, ",");
				strcat(ret->attributes, attributeParam);
			}			
		}
	}
}


// the method will print the stymbol to machine code format - binary
void printToMachineCode(symbolList* symbolTable) {

}


// Operations:
// 2. Add new attribute to existing symbol

// this function will insert a symbol without any values - only the name of the symbol and the saved lines indexes
void insertEmptySymbolWithSavedLines(symbolList** symbolTable, char* symbolName, int* savedLinesOfSymbol) {

	symbolList* newEmptySymbol = NULL;
	int i, noNewLines = 2;


	isSymbolAlreadyExist(symbolTable,symbolName,&newEmptySymbol);

	if (newEmptySymbol != NULL) {
		// means that the symbol was found on the list

		// copy the saved Lines to the savedLines
		for (i = 0; i < noNewLines; i++) {
			newEmptySymbol->savedLinesInCode[i] = savedLinesOfSymbol[i];
		}

	}
	else {
		// there is no such symbol in the list

		newEmptySymbol = createNewSymbol();
		// insert the new symbol name
		strcpy(newEmptySymbol->symbolName, symbolName);
		newEmptySymbol->nextSymbol = NULL;

		// copy the saved Lines to the savedLines
		for (i = 0; i < noNewLines; i++) {
			newEmptySymbol->savedLinesInCode[i] = savedLinesOfSymbol[i];
		}

		// insert the current empty symbol to the symbol table
		insertSymbolToEndOfList(symbolTable, newEmptySymbol);
	}

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


// This function will prin the all symbol list
void printSymList(symbolList* head) {

	printf("\n The linked list of Symbols is\n");

	while (head != NULL)
	{
		printf(" %s - v:%d, base:%d, off:%d, att: %s\n",head->symbolName, head->value, head->baseAddress, head->offset, head->attributes);
		head = head->nextSymbol;
	}
}


// this method will return the Type of Symbol -if External of other
char getTheTypeOfSymbol(symbolList** symbolTable, char* symbolName) {
	
	symbolList* ret = NULL;

	isSymbolAlreadyExist(symbolTable, symbolName, &ret);

	if (strstr(ret->attributes, "extern") != NULL)
		return 'E';
	else
		return 'O';
}

// this method will return the baseAddress of the symbol as integer
int getBaseAddressOfSymbol(symbolList** symbolTable, char* symbolName){

	symbolList* ret = NULL;

	isSymbolAlreadyExist(symbolTable, symbolName, &ret);

	return ret->baseAddress;

}

// this method will return the Offset of the symbol as integer
int getOffsetOfSymbol(symbolList** symbolTable, char* symbolName) {

	symbolList* ret = NULL;

	isSymbolAlreadyExist(symbolTable, symbolName, &ret);

	return ret->offset;

}

 // this method will return the Saved Lines of the symbol as integer
int* getSavedRowsOfSymbol(symbolList** symbolTable, char* symbolName) {

	symbolList* ret = NULL;

	isSymbolAlreadyExist(symbolTable, symbolName, &ret);

	return ret->savedLinesInCode;

}