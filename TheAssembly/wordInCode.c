#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "wordInCode.h"
#include "constantTables.h"
#include "helperFunctions.h"



#define WORD_LENGTH 20
#define NO_OF_ACTIONS 16

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
void insertNewOpCodeWord(machineCode* machCodeTable, char actionName[], int opCodeToTurnOn, int valueOfAction);
void insertNewFullCodeWord(machineCode* machCodeTable);
void insertNewCodeWordDirectiveValue(machineCode* machCodeTable, char binaryNumber[], int valueForNewWord);



// allocate memory of a new word
machineCode* createWordInMemory() {

	return (machineCode*)malloc(sizeof(machineCode));
}

// Initialize the word array with all 0 values- for the Opcode word
void initializeCodeWord(machineCode* machCode) {

	//int i;
	machCode->isCompleted = FALSE;
	machCode->programWordValue = -1;

	machCode->nextWord = (machineCode*)malloc(sizeof(machineCode));

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


// This method will insert a new Word to the end of the current Machine Code Table - after it was built
void insertNewWordToEndOfTable(machineCode* machCodeTable, machineCode* newMachineCodeWord) {

	machineCode* pNewWord = (machineCode*)malloc(sizeof(machineCode));

	if (machCodeTable == NULL)
	{
		// Insert the first MachineCode to the table
		machCodeTable = newMachineCodeWord;
		 //machCodeTable->nextWord = (machineCode*)malloc(sizeof(machineCode));
		machCodeTable->nextWord = NULL;
	}
	else
	{
		pNewWord = machCodeTable;
		while (pNewWord->nextWord != NULL)
			pNewWord = pNewWord->nextWord;


		
		pNewWord->nextWord = newMachineCodeWord;
		pNewWord = pNewWord->nextWord;
		//pNewWord->nextWord = (machineCode*)malloc(sizeof(machineCode));
		pNewWord->nextWord = NULL;
	}

	free(pNewWord);
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
void insertNewOpCodeWord(machineCode* machCodeTable, char actionName[],int opCodeToTurnOn, int valueOfAction) {

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

		//Insert to machineCodeTable in the end
		insertNewWordToEndOfTable(machCodeTable , newWord);

		newWord->isCompleted = TRUE;

		displayWord(newWord);
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
	char* currAction, currActionName, currFunctOfAction;

	if (opCodeOfAction == 2 || opCodeOfAction == 5 || opCodeOfAction == 9) {

		for (i = 0; i < NO_OF_ACTIONS && !foundFunct; i++) {

			currAction = pToActionsOpCode[i];	// get current action from the table

			lineLength = strlen(currAction);	// Calculate the curr action length in table

			indexOfFirstComma = returnFirstIndexOfChar(currAction, ',');	// Find the first delimeter index from action name to action data
			indexOfLastColon = returnLastIndexOfChar(currAction, ':');	// Find the first colon index, before the opcode value of action

			currActionName = subString(currAction, 0, indexOfFirstComma + 1);	// Substring the current action name
			currFunctOfAction = subString(currAction, indexOfLastColon + 1, lineLength);	// Substring the Funct

			printf("The Funct value of %s is %d", currAction, currFunctOfAction);

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



// -----Open
// Add a new FullCodeWord - with funct - register and adress (Destination + origin)

//void insertNewFullCodeWord(machineCode* machCodeTable, char actionName[], int valueForNewWord) {
void insertNewFullCodeWord(machineCode* machCodeTable, char** arrayOfArgs, int valueForNewWord) {

	int i;
	machineCode* newWord = createWordInMemory();

	if (newWord) {
		initializeCodeWord(newWord);

		newWord->programWordValue = valueForNewWord;

		// the first cell is the action
		updateFunctValue(newWord, actionName);	// Update the func value inside the word

		updateCodeWordARECells(newWord,'A');


		//Insert Address + register destination
		// Insert the Address + register origin
		//Insert the A,R,E letters
		
		
		// init all other cells to 0
		for (i = 0; i < WORD_LENGTH; i++)
		{
			if (newWord->wordBinary[i] != 0 && newWord->wordBinary[i] != 1)
				newWord->wordBinary[i] = 0;
		}

		insertNewWordToEndOfTable(machCodeTable, newWord);

		displayWord(newWord);
	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}
}


// -----Open
// Add a new CodeWord - for string or data values 
void insertNewCodeWordDirectiveValue(machineCode* machCodeTable, char* binaryNumber, int valueForNewWord) {

	int i, wordIndexToInsert = 4;
	machineCode* newWord = createWordInMemory();

	if (newWord) {
		initializeCodeWord(newWord);

		newWord->programWordValue = valueForNewWord;	// add new Word value from data counter
		updateCodeWordARECells(newWord, 'A');	// set the Bit


		// insert the binary number to the array - in order
		for (i = 0; i < LENGTH_OF_BIN_NUMBER; i++, wordIndexToInsert++) {
			newWord->wordBinary[wordIndexToInsert] = (binaryNumber[i]-'0');
			//printf("%d ", newWord->wordBinary[wordIndexToInsert]);
		}
		//printf("\n");
		insertNewWordToEndOfTable(machCodeTable, newWord);

		newWord->isCompleted = TRUE;
	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}

	free(newWord);
}


// -----Open
// this function gets Char ('O' or 'D') for indicating which address and register to update
// Origin - Register + address - will be signaled in 'O'
// Destination - Register + address will be signaled in 'D'



// -----Open
// registerCode will be 4 digit 
void registersAdresses(machineCode* machCode, char directionFlag, char* registerCode, char* adrCode) {

	int regIndex, adrIndex;

	
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

	// Continue
	//Enter the register andsAddresses codes in the word array.
	// get the registerBinaryValue from table
	// get the adressValue from table

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

		while (ptr != NULL)
		{
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

			ptr = ptr->nextWord;

		}
	}
	free(ptr);

}