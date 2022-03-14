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


// Add a new OpCod word - with the turned bit
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


// Add a new FullCodeWord - with funct - register and adress (Destination + origin)
machineCode* insertNewFullCodeWord() {

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
// this function updates the Funct range inside the wordInCode
void updateFunctValue(char* functCode) {

	int functIndex = 15;	//modify cells 15-12




	// modify 
}


// -----Open
// this function gets the values to update for each cell
// Origin - Register + address - will be signaled in 'O'
// Destination - Register + address will be signaled in 'D'

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

	//Enter the register and Addresses codes in the word array.

}


void updateCodeWordARE(machineCode* machCode, char areValueForWord) {

	int turnedBit = 1;

	switch (areValueForWord)
	{
	case 'A':
		machCode[18] = turnedBit;
		break;

	case 'R':
		machCode[17] = turnedBit;
		break;

	case 'E':
		machCode[16] = turnedBit;
		break;

	default:
		break;
	}
}

void initializeCodeWord(machineCode* machCode) {

	int i;

	for (i = 0; i<WORD_LENGTH; i++)
		(*machCode).wordBinary[i] = 0;

}







// Operations:
// 1. Insert to every part of the Word in the Memory - by the indexes + only if empty.
// 2. Insert full number to 16 cells - if needed in Addressing mode 0
// Print Current Word - in Hexadecimal format
// 
// 