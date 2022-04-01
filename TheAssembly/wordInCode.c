#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "wordInCode.h"
#include "constantTables.h"
#include "helperFunctions.h"
#include "symbol.h"



#define WORD_LENGTH 20
#define NO_OF_ACTIONS 16
#define LENGTH_OF_SAVED_WORDS 2
#define TRUE 1
#define FALSE 0



// This struct will represent a single word in the machine memory
typedef struct wordInCode
{
	int programWordValue;
	int wordBinary[WORD_LENGTH];	// Initialize with -1 in all cells
	int isCompleted;

	struct wordInCode* nextWord;

};



void initializeCodeWord(machineCode* machCode);
void initializeWithNotCompletedCodeWord(machineCode* machCode);
void insertNewWordToEndOfTable(machineCode** machCodeTable, machineCode* newMachineCodeWord);
void checkForWordFullyCompleted(machineCode* machCode);
void updateCodeWordARECells(machineCode* machCode, char areValueForWord);
int getOpcodeAction(char actionName[]);
char* getFunctOfAction(char actionName[], int opCodeOfAction);
void insertNewOpCodeWord(machineCode** machCodeTable, char actionName[], int opCodeToTurnOn, int valueOfAction);
void insertNewFullCodeWord(machineCode** machCodeTable, symbolList* symbolTable, char** arrayOfArgs, int valueForNewWord, int numOfArgs);
void insertNewCodeWordDirectiveValue(machineCode** machCodeTable, char* binaryNumber, int valueForNewWord);
void insertEmptyRowForNewWordsOfSymbol(machineCode** machCodeTable, int valueForNewWord);
void insertAdditionalWords(machineCode** actionsMachineCode, symbolList** symbolTable, char** argsFromLine, int numOfArgs, int* pToActionsCounter);

void registersAdresses(machineCode* machCode, char directionFlag, char* registerCode, char* adrCode);

void printList(machineCode* head);

// allocate memory of a new word
machineCode* createWordInMemory() {

	return (machineCode*)malloc(sizeof(machineCode));
}

// Initialize the word array with all 0 values- for the Opcode word
void initializeCodeWord(machineCode* machCode) {

	//int i;
	machCode->isCompleted = FALSE;
	machCode->programWordValue = -1;

	//machCode->nextWord = (machineCode*)malloc(sizeof(machineCode));

	machCode->nextWord = NULL;

	//for (i = 0; i<WORD_LENGTH; i++)
	//	machCode->wordBinary[i] = 0;

	memset(machCode->wordBinary, 0, WORD_LENGTH);
}


// Initialize the word array with all -1 value- for regular word - with funct, addresses and registers
void initializeWithNotCompletedCodeWord(machineCode* machCode) {

	//int i;

	machCode->isCompleted = FALSE;
	machCode->programWordValue = -1;

	machCode->nextWord = (machineCode*)malloc(sizeof(machineCode));

	/*for (i = 0; i < WORD_LENGTH - 1; i++)
		machCode->wordBinary[i] = -1;*/

	memset(machCode->wordBinary, (-1), WORD_LENGTH);

	// Change cell 19 to 0 - always
	machCode->wordBinary[0] = 0;
}


// ------------Doesnot work!!! 
// This method will insert a new Word to the end of the current Machine Code Table - after it was built
void insertNewWordToEndOfTable(machineCode** machCodeTable, machineCode* newMachineCodeWord) {

	//machineCode* pNewWord = (machineCode*)malloc(sizeof(machineCode));

	machineCode* pWord ;

	if (*machCodeTable == NULL)
	{
		//delete the comments below
		{
			// Insert the first MachineCode to the table
		/*	pWord = (machineCode*)malloc(sizeof(machineCode));
			pWord->programWordValue = newMachineCodeWord->programWordValue;*/

			//pWord->wordBinary = newMachineCodeWord->wordBinary;

			/*pWord->isCompleted = newMachineCodeWord->isCompleted;
			pWord->nextWord = NULL;

			machCodeTable = pWord;*/
			//pWord = newMachineCodeWord;
			//pWord->nextWord = NULL;
			// 
			//machCodeTable = (machineCode*)malloc(sizeof(machineCode));
		}

		*machCodeTable = newMachineCodeWord;		
		(* machCodeTable)->nextWord = NULL;
	}
	else
	{
		pWord = *machCodeTable;

		while (pWord ->nextWord != NULL)
			pWord = pWord->nextWord;
		
		pWord->nextWord = newMachineCodeWord;

		//delete the comments below
		{
			//pWord->nextWord = (machineCode*)malloc(sizeof(machineCode));
			//pWord = (machineCode*)malloc(sizeof(machineCode));

			/*pWord->nextWord = NULL;
			pWord = pWord->nextWord;*/
			//pNewWord->nextWord = (machineCode*)malloc(sizeof(machineCode));
			//pWord->nextWord = NULL;
		}
	}

	//printf("\nAfter insert inside function: ");
	//printList(*machCodeTable);
	//free(pWord);
}


// This function checks if the full word in memory contains non fill value- and change the value accordingly
void checkForWordFullyCompleted(machineCode* machCode) {

	int i;

	for (i = 0; i < WORD_LENGTH; i++)
		if (machCode->wordBinary[i] == -1) {
			machCode->isCompleted = FALSE;
			return;
		}

	machCode->isCompleted = TRUE;
}


// The function gets the pointer to the word + the char to enter - A,R,E and turn on bit in the relevant cells in word
void updateCodeWordARECells(machineCode* machCode, char areValueForWord) {

	int turnedBit = 1;


	// Binary array fields: 19=0,18=1,17=2,16=3... 1=18,0=19
	switch (areValueForWord)
	{
	case 'A':
		machCode->wordBinary[1] = turnedBit;
		break;

	case 'R':
		machCode->wordBinary[2] = turnedBit;
		break;

	case 'E':
		machCode->wordBinary[3] = turnedBit;
		break;

	default:
		break;
	}
}


// This function will turn on the bit of the Opcode Machine word - according to the action relevant opccode
int getOpcodeAction(char actionName[]) {

	int		i, indexOfFirstComma, indexOfFirstColon, lineLength,
		cmpResult, bitToTurnOn = -1, lengthOfOpcode, opCodeOfAction;

	char** pToActionsOpCode = returnActionsByOpcodeTable();
	char* currAction;
	char* currActionName;
	char* currOpCodeOfAction;

	for (i = 0; i < NO_OF_ACTIONS && bitToTurnOn == (-1); i++) {

		currAction = pToActionsOpCode[i];	// get current action from the table

		//lineLength = strlen(currAction);	// Calculate the curr action length in table

		indexOfFirstComma = returnFirstIndexOfChar(currAction, ',');	// Find the first delimeter index from action name to action data
		indexOfFirstColon = returnFirstIndexOfChar(currAction, ':');	// Find the first colon index, before the opcode value of action

		currActionName = subString(currAction, 0, indexOfFirstComma );	// Substring the current action name
		currOpCodeOfAction = subString(currAction, indexOfFirstColon + 1, indexOfFirstColon + 3);	// Substring the opcode of the action from the table - could be 1 or 2 chars

		// Convert the opCode string to integer
		opCodeOfAction = atoi(currOpCodeOfAction);

		// Compare the 2 names of the given action with the current from iteration
		cmpResult = strcmp(actionName, currActionName);

		if (cmpResult == 0)
			bitToTurnOn = opCodeOfAction;
	}

	return bitToTurnOn;
}


// Add a new OpCode word - with the turned bit - initialize the word with all 0
void insertNewOpCodeWord(machineCode** machCodeTable, char actionName[],int opCodeToTurnOn, int valueOfAction) {

	int bitToTurnOn, i;

	machineCode* newWord = createWordInMemory();

	if (newWord) {
		initializeCodeWord(newWord);

		//Test
		// Turn on Relevant bit in the array in the new word
		
 		newWord->programWordValue = valueOfAction;
		//bitToTurnOn = getOpcodeAction(actionName);
		bitToTurnOn = opCodeToTurnOn;

		if (bitToTurnOn > -1)
			newWord->wordBinary[WORD_LENGTH - 1 - bitToTurnOn] = 1;
		else
		{
			printf("The Action wasnt found in the constant actions table");
		}

		// init all other cells to 0
		for (i = 0; i < WORD_LENGTH; i++)
		{
			if (newWord->wordBinary[i] != 0 && newWord->wordBinary[i] != 1)
				newWord->wordBinary[i] = 0;
		}

		// Upadte the A,R,E Values in the new word
		updateCodeWordARECells(newWord, 'A');

		newWord->isCompleted = TRUE;

		//displayWord(newWord);

		//Insert to machineCodeTable in the end
		insertNewWordToEndOfTable(machCodeTable, newWord);
		
		
		//printf("\nAfter insert outside insert function: ");
		//printList(*machCodeTable);

	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}
}


// This function will return the funct value as a string - before the insertion
char* getFunctOfAction(char actionName[], int opCodeOfAction) {

	int i, foundFunct = FALSE, indexOfLastColon, indexOfFirstComma, lineLength, cmpResult;
	char* functToReturn;

	char** pToActionsOpCode = returnActionsByOpcodeTable();
	char* currAction;
	char* currActionName;
	char* currFunctOfAction;

	if (opCodeOfAction == 2 || opCodeOfAction == 5 || opCodeOfAction == 9) {

		for (i = 0; i < NO_OF_ACTIONS && !foundFunct; i++) {

			currAction = pToActionsOpCode[i];	// get current action from the table

			lineLength = strlen(currAction);	// Calculate the curr action length in table

			indexOfFirstComma = returnFirstIndexOfChar(currAction, ',');	// Find the first delimeter index from action name to action data
			indexOfLastColon = returnLastIndexOfChar(currAction, ':');	// Find the first colon index, before the opcode value of action

			currActionName = subString(currAction, 0, indexOfFirstComma);	// Substring the current action name
			currFunctOfAction = subString(currAction, indexOfLastColon + 1, lineLength);	// Substring the Funct

			//printf("\nThe Funct value of %s is %s", currActionName, currFunctOfAction);

			// Compare the 2 names of the given action with the current from iteration
			cmpResult = strcmp(actionName, currActionName);

			if (cmpResult == 0)
				foundFunct = TRUE;
		}

		return currFunctOfAction;
	}
	else {
		return "0000\0";
	}

}


// the function get the word Pointer + gets the action itself - add,mov ext.
// this function updates the Funct range inside the wordInCode
void updateFunctValue(machineCode* machCode, char actionName[]) {

	char* functOfAction;
	int functIndex = 4, endFunctIndex = 8, opCodeOfAction;	//modify cells 4-7


	opCodeOfAction = getOpcodeAction(actionName);

	functOfAction = getFunctOfAction(actionName, opCodeOfAction);


	//Insert the given char to machinecode 4-7'
	while (functIndex < endFunctIndex)
	{
		machCode->wordBinary[functIndex++] = (*functOfAction)-'0';
		functOfAction++;
	}
}


//void insertNewFullCodeWord(machineCode* machCodeTable, char actionName[], int valueForNewWord) {
void insertNewFullCodeWord(machineCode** machCodeTable, symbolList* symbolTable, char** arrayOfArgs, int valueForNewWord, int numOfArgs) {

	int i, indexOfFirstArg, indexOfScndArg;

	char* firstArgVal = NULL;
	char* firstArgMiun = NULL;
	char* secondArgVal = NULL;
	char* secondArgMiun = NULL;

	machineCode* newWord = createWordInMemory();
	indexOfFirstArg = 1;
	indexOfScndArg = 2;

	if (newWord) {
		initializeCodeWord(newWord);

		newWord->programWordValue = valueForNewWord;

		// the first cell is the action
		updateFunctValue(newWord, arrayOfArgs[0]);	// Update the func value inside the word

		// update ARE cells
		updateCodeWordARECells(newWord,'A');

		// calculate the values to enter in each of the dest or origin fields
		if (numOfArgs == 2) 
		{
			// find the register code and miun value to insert for both origin and dest
			firstArgVal = getRegisterCode(arrayOfArgs[indexOfFirstArg]);
			secondArgVal = getRegisterCode(arrayOfArgs[indexOfScndArg]);

			firstArgMiun = findMatchedMiun(arrayOfArgs[indexOfFirstArg], symbolTable);
			secondArgMiun = findMatchedMiun(arrayOfArgs[indexOfScndArg], symbolTable);

		}
		else if (numOfArgs == 1)
		{
			// find the register code and miun value to insert for  dest only
			firstArgVal = "0000\0";
			secondArgVal = getRegisterCode(arrayOfArgs[indexOfFirstArg]);

			firstArgMiun = "00\0";
			secondArgMiun = findMatchedMiun(arrayOfArgs[indexOfFirstArg], symbolTable);
		}

		// Add the origin register and miun method no.
		registersAdresses(newWord, 'O', firstArgVal, firstArgMiun);

		// Add the destination register and miun method no.
		registersAdresses(newWord, 'D', secondArgVal, secondArgMiun);


		// init all other cells to 0
		for (i = 0; i < WORD_LENGTH; i++)
		{
			if (newWord->wordBinary[i] != 0 && newWord->wordBinary[i] != 1)
				newWord->wordBinary[i] = 0;
		}

		// change the isCompleted to true - done inserting this row
		newWord->isCompleted = TRUE;

		// TEST
		//displayWord(newWord);

		// insert the new word to the machine code table
		insertNewWordToEndOfTable(machCodeTable, newWord);
	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}
}


// Add a new CodeWord - for string or data values 
void insertNewCodeWordDirectiveValue(machineCode** machCodeTable, char* binaryNumber, int valueForNewWord) {

	int i, wordIndexToInsert = 4;
	machineCode* newWord = createWordInMemory();

	if (newWord) {
		initializeCodeWord(newWord);

		newWord->programWordValue = valueForNewWord;	// add new Word value from data counter
		updateCodeWordARECells(newWord, 'A');	// set the Bit

		// insert the binary number to the array - in order
		for (i = 0; i < LENGTH_OF_BIN_NUMBER; i++, wordIndexToInsert++) {
			newWord->wordBinary[wordIndexToInsert] = (binaryNumber[i]-'0');
		}

		newWord->isCompleted = TRUE;

		displayWord(newWord);

		insertNewWordToEndOfTable(machCodeTable, newWord);
	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}
}


// On first Pass - enter empty rows - for symbols values need to be inserted in second pass
void insertEmptyRowForNewWordsOfSymbol(machineCode** machCodeTable, int valueForNewWord) {

	machineCode* newWord = createWordInMemory();

	if (newWord) {

		// insert new word as not completed
		initializeCodeWord(newWord);

		// insert the value of the row only!
		newWord->programWordValue = valueForNewWord;
		newWord->nextWord = NULL;
		
		// insert the new word to end of table
		insertNewWordToEndOfTable(machCodeTable, newWord);

		displayWord(newWord);
	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}
	
}


//To handle the .entry directive
void insertAdditionalWords(machineCode** actionsMachineCode, symbolList** symbolTable, char** argsFromLine, int numOfArgs, int* pToActionsCounter)
{
	symbolList* searchedSymbol = NULL;
	char* resultOfMiunCheck;
	char* symbolNameToSearch = NULL;
	char* binNumberToInsert = malloc(sizeof(char) * LENGTH_OF_BIN_NUMBER);
	char* newSymbolNameWithEmptyLines = NULL;
	int savedWordValues[LENGTH_OF_SAVED_WORDS] = { (*pToActionsCounter) + 1 , (*pToActionsCounter) + 2 };

	int i, noOfNewWords, numberToConvertForWord, indexToCut, insertedWords, indexOfSymbolName;

	// iterate on all arguments that exist
	for (i = 1; i <= numOfArgs; i++) {

		resultOfMiunCheck = findMatchedMiun(argsFromLine[i], symbolTable);

		if (strcmp(resultOfMiunCheck, "00\0") == 0) {	// miun 0 - single new word

			//Split the content of the number value 
			indexToCut = returnFirstIndexOfChar(argsFromLine[i], '#');
			numberToConvertForWord = atoi(subString(argsFromLine[i], indexToCut + 1, strlen(argsFromLine[i])));

			strcpy(binNumberToInsert,convertNumberToBinaryString(numberToConvertForWord));
			
			// raise the counter +1
			(*pToActionsCounter) = (*pToActionsCounter) + 1;

			// insert new Row with extracted number
			insertNewCodeWordDirectiveValue(actionsMachineCode, binNumberToInsert, (*pToActionsCounter));
		

		}
		else if (strcmp(resultOfMiunCheck, "01\0") == 0 || strcmp(resultOfMiunCheck, "10\0") == 0) {
			// get the Symbol name from argument in each scenario
			// Check which of the arguments is the symbol name and extarct it - for the insertion
			if (strcmp(resultOfMiunCheck, "01\0") == 0) {
				// miun 1 - will be only string
				if (isString(argsFromLine[1]) == TRUE)
					indexOfSymbolName = 1;
				else
					indexOfSymbolName = 2;

				newSymbolNameWithEmptyLines = malloc(sizeof(char) * SYMBOL_MAX_LENGTH);
				
				if (newSymbolNameWithEmptyLines!=NULL)
					strcpy(newSymbolNameWithEmptyLines,  argsFromLine[indexOfSymbolName]);
			}
			else
			{
				// miun 2 - will contain [Reg_No]
				if (strstr(argsFromLine[1],"[") == TRUE)
					indexOfSymbolName = 1;
				else
					indexOfSymbolName = 2;

				// split the symbol name from the argument
				indexToCut= returnFirstIndexOfChar(argsFromLine[indexOfSymbolName], '[');
				newSymbolNameWithEmptyLines = subString(argsFromLine[indexOfSymbolName], 0, indexToCut);
			}

			//Insert the newEmpty symbol to list
			insertEmptySymbolWithSavedLines(symbolTable, newSymbolNameWithEmptyLines,savedWordValues);



			// raise the counter +1
			(*pToActionsCounter) = (*pToActionsCounter) + 1;

			// insert new Row  - not completed
			insertEmptyRowForNewWordsOfSymbol(actionsMachineCode, (*pToActionsCounter));

			// raise the counter +1
			(*pToActionsCounter) = (*pToActionsCounter) + 1;

			// insert the second argument
			insertEmptyRowForNewWordsOfSymbol(actionsMachineCode, (*pToActionsCounter));

			{
				//printList(*actionsMachineCode);
				//printList(*actionsMachineCode);
				//indexToCut = returnFirstIndexOfChar(argsFromLine[i], '[');
				//symbolNameToSearch = subString(argsFromLine[i], 0, indexToCut);
				//
				//isSymbolAlreadyExist(symbolTable, symbolNameToSearch, searchedSymbol);
				//if (searchedSymbol != NULL) {
				//	// found the symbol
				//}
				//else
				//	printf("Error while searching for symbol in the symbol list");
			}
		}
		else
		{	// miun 3 - no new words
			noOfNewWords = 0;
		}

	}
}



//------------OPEN - PASS 2
// this method  will edit the found machine code accordingly to the symbol values
void updateEmptyRowForNewWordsOfSymbol(machineCode* machCodeTable) {



}


//-----------OPEN - PASS 2
// this method will search for the relevant row of the current argument in the machine code and return a pointer to it
machineCode* findRowOfSymbolInMachineCode() {

	machineCode* foundSymbol = NULL;


	return foundSymbol;
}


// this function gets Char ('O' or 'D') for indicating which address and register to update
// Origin - Register + address - will be signaled in 'O'
// Destination - Register + address will be signaled in 'D'
// registerCode will be 4 digit 
void registersAdresses(machineCode* machCode, char directionFlag, char* registerCode, char* adrCode) {

	int regIndex, adrIndex, rangeToInsertReg,
		rangeToInsertAdr, currRangeReg , currRangeAdr;

	// amount of cells we iterate to enter each value
	rangeToInsertAdr = 2;
	rangeToInsertReg = 4;
	
	switch (directionFlag)
	{
	case 'O':
		regIndex = 8;	// 8-11
		adrIndex = 12;	// 12-13
		break;

	case 'D':
		regIndex = 14;	// 14-17
		adrIndex = 18;	// 18-19
		break;

	default:
		break;
	}

	// insert to relevant cells in word the register code
	for (currRangeReg = 0; currRangeReg < rangeToInsertReg; currRangeReg++) {

		machCode->wordBinary[regIndex] = registerCode[currRangeReg] - '0';
		regIndex++;
	}
	//printf("Reg index Done at : %d", regIndex);

	// insert to relevant cells in word the Miun code
	for (currRangeAdr = 0; currRangeAdr < rangeToInsertAdr; currRangeAdr++) {

		machCode->wordBinary[adrIndex] = adrCode[currRangeAdr] - '0';
		adrIndex++;
	}
	//printf("Miun index Done at : %d", adrIndex);
}


// Cleans the word from the memory
void deleteWordFromMemory(machineCode* machCode) {
	free(machCode);
}


// Operations:
// Print Current Word - in Hexadecimal format

void displayWord(machineCode* machCode) {

	machineCode* ptr = machCode;


	int i = 1,j;
	if (ptr == NULL)
		printf("\Word is empty.\n");
	else
	{
		printf("\nSr. No.\t\PrgramWordValue\t\tIsCompleted\t\tLink\n");
			printf("\n%d.\t \t%d\t \t%d\t \n", i, ptr->programWordValue, ptr->isCompleted);
			
			i++;

			printf("\Word Code.\n");
			
			for (j = 0; j < WORD_LENGTH; j++) {
				if (j > 9)
					printf("| %d |", (WORD_LENGTH-j-1));
				else
					printf("| %d|", (WORD_LENGTH - j-1));
			}
			printf("\n");
			for (j = 0; j < WORD_LENGTH; j++) {
				printf("| %d |", ptr->wordBinary[j]);
			}

	}
	//free(ptr);

}


void printList(machineCode* head) {

	printf("\n The linked list of machine code is\n");

	while (head != NULL)
	{
		printf(" %d - isCom:%d  ", head->programWordValue, head->isCompleted);
		//displayWord(head->wordBinary);
		head = head->nextWord;
		
	}


}