#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "wordInCode.h"
#include "constantTables.h"



#define WORD_LENGTH 20

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


// allocate memory of a new word
machineCode* createWordInMemory() {

	return (machineCode*)malloc(sizeof(machineCode));
}



// Initialize the word array with all 0 values- for the Opcode word
void initializeCodeWord(machineCode* machCode) {

	//int i;

	//for (i = 0; i<WORD_LENGTH; i++)
		//machCode->wordBinary[i] = 0;

	memset(machCode->wordBinary, 0, WORD_LENGTH);
}


// Initialize the word array with all -1 value- for regular word - with funct, addresses and registers
void initializeWithNotCompletedCodeWord(machineCode* machCode) {

	int i;

	/*for (i = 0; i < WORD_LENGTH - 1; i++)
		machCode->wordBinary[i] = -1;*/

	memset(machCode->wordBinary, (-1), WORD_LENGTH);

	// Change cell 19 to 0 - always
	machCode->wordBinary[0] = 0;
}


// This method will insert a new Word to the end of the current Machine Code Table - after it was built
void insertNewWordToEndOfTable(machineCode* machCodeTable, machineCode* newMachineCodeWord) {

	machineCode* pNewWord;

	if (machCodeTable == NULL)
	{
		// Insert the first MachineCode to the table
		machCodeTable = newMachineCodeWord;
		machCodeTable->nextWord = NULL;
	}
	else
	{
		pNewWord = machCodeTable;
		while (pNewWord->nextWord != NULL)
			pNewWord = pNewWord->nextWord;

		pNewWord->nextWord = newMachineCodeWord;
		pNewWord = pNewWord->nextWord;
		pNewWord->nextWord = NULL;
	}
}


// -----Open
// Add a new OpCode word - with the turned bit - initialize the word with all 0
void insertNewOpCodeWord(machineCode* machCodeTable) {

	machineCode* newWord = createWordInMemory();

	if (newWord) {
		initializeCodeWord(newWord);

		// Add all the values to the newWord 
		// insert the opcode of the action
		// search the action in the constant table and turn on 
		// the current bit in the new word - by the value returned from the anaylsis

		insertNewWordToEndOfTable(machCodeTable , newWord);
	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}
}


// -----Open
// Add a new FullCodeWord - with funct - register and adress (Destination + origin)
void insertNewFullCodeWord(machineCode* machCodeTable) {

	machineCode* newWord = createWordInMemory();

	if (newWord) {
		initializeWithNotCompletedCodeWord(newWord);

		// Insert the funct
		//Insert Address + register destination
		// Insert the Address + register origin
		//Insert the A,R,E letters
		
		
		insertNewWordToEndOfTable(machCodeTable, newWord);
	}
	else
	{
		printf("Not enoght memory - error in Insert new OPCODE");
		return NULL;
	}
}


// -----Open
// the function get the word Pointer + gets the action itself - add,mov ext.
// this function updates the Funct range inside the wordInCode
void updateFunctValue(machineCode* machCode, char* actionNameFromLine) {

	int functIndex = 15;	//modify cells 15-12

	// get the opcode of the action from the contant table
	// check if it is - 2,5,9 - enter the funct value to the fields 15-12
	// else	- enter all zeros



	// modify 
}


// -----Open
// this function gets Char ('O' or 'D') for indicating which address and register to update
// Origin - Register + address - will be signaled in 'O'
// Destination - Register + address will be signaled in 'D'


// registerCode will be 4 digit 
void registersAdresses(machineCode* machCode, char directionFlag, char* registerCode, char* adrCode) {

	int regIndex, adrIndex;

	
	switch (directionFlag)
	{
	case 'O':
		regIndex = 11;	// 11-8
		adrIndex = 7;	// 7-6
		break;

	case 'D':
		regIndex = 5;	// 5-2
		adrIndex = 1;	// 1-0
		break;

	default:
		break;
	}

	// Continue
	//Enter the register and Addresses codes in the word array.
	// get the registerBinaryValue from table
	// get the adressValue from table

}




// The function gets the pointer to the word + the char to enter - A,R,E and turn on bit in the relevant cells in word
void updateCodeWordARECells(machineCode* machCode, char areValueForWord) {

	int turnedBit = 1;

	switch (areValueForWord)
	{
	case 'A':
		machCode->wordBinary[18] = turnedBit;
		break;

	case 'R':
		machCode->wordBinary[17] = turnedBit;
		break;

	case 'E':
		machCode->wordBinary[16] = turnedBit;
		break;

	default:
		break;
	}
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



// Cleans the word from the memory
void deleteWordFromMemory(machineCode* machCode) {
	free(machCode);
}


// Operations:
// Print Current Word - in Hexadecimal format
// 
// 