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

	return (machineCode*)malloc(sizeof(machineCode);
}

// -----Open
// Add a new OpCode word - with the turned bit - initialize the word with all 0
machineCode* insertNewOpCodeWord() {

	machineCode newWord = createWordInMemory();
	initializeCodeWord(newWord);

	machineCode* pNewWord;

	if (newWord) {

		pNewWord = newWord;

		// insert the opcode of the action
		// search the action in the constant table and turn on 
		// the current bit in the new word - by the value returned from the anaylsis
		
		
		return pNewWord;
	}
	else
		printf("Not enoght memory - error in Insert new OPCODE");
}


// -----Open
// Add a new FullCodeWord - with funct - register and adress (Destination + origin)
machineCode* insertNewFullCodeWord() {

	machineCode newWord = createWordInMemory();
	initializeWithNotCompletedCodeWord(newWord);	

	machineCode* pNewWord;

	if (newWord) {

		pNewWord = newWord;

		// Insert the funct
		//Insert Address + register destination
		// Insert the Address + register origin
		//Insert the A,R,E letters
		
		
		return pNewWord;
	}
	else
		printf("Not enoght memory - error in Insert new OPCODE");
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
void registersAdresses(char directionFlag, char* registerCode, char* adrCode) {

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
		(*machCode).wordBinary[18] = turnedBit;
		break;

	case 'R':
		(*machCode).wordBinary[17] = turnedBit;
		break;

	case 'E':
		(*machCode).wordBinary[16] = turnedBit;
		break;

	default:
		break;
	}
}

// Initialize the word array with all 0 values- for the Opcode word
void initializeCodeWord(machineCode* machCode) {

	int i;

	for (i = 0; i<WORD_LENGTH; i++)
		(*machCode).wordBinary[i] = 0;

}

// Initialize the word array with all -1 value- for regular word - with funct, addresses and registers
void initializeWithNotCompletedCodeWord(machineCode* machCode) {

	int i;

	for (i = 0; i < WORD_LENGTH - 1; i++)
		(*machCode).wordBinary[i] = -1;

	// Change cell 19 to 0 - always
	(*machCode).wordBinary[i] = 0;
}

// This function checks if the full word in memory contains non fill value- and change the value accordingly
void checkForWordFullyCompleted(machineCode* machCode) {

	int i;

	for (i = 0; i < WORD_LENGTH; i++)
		if ((*machCode).wordBinary[i] == -1) {
			(*machCode).isCompleted = FALSE;
			return;
		}
			
	(*machCode).isCompleted = TRUE;
}

// Cleans the word from the memory
void deleteWordFromMemory(machineCode* machCode) {
	free(machCode);
}


// Operations:
// Print Current Word - in Hexadecimal format
// 
// 