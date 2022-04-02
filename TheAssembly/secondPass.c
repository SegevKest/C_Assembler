#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#include "validations.h"
#include "wordInCode.h"
#include "symbol.h"
#include "helperFunctions.h"



#define TRUE 1
#define FALSE 0
#define LINE_LENGTH 81


void scndPassOnFile(machineCode** actionsMachineCodeHead, machineCode** dataMachineCodeHead, symbolList** symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter);

// The main function of the second pass - contains a loop on all the rows and handling each row
// if contains a empty symbols rows in the list
void scndPassOnFile(machineCode** actionsMachineCodeHead, machineCode** dataMachineCodeHead, symbolList** symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter) {

	FILE* filePointer;

	filePointer = fopen(filePath, "r");

	char currLine[LINE_LENGTH];

	if (filePointer == NULL) {
		printf("\nFile pointer received is an ERROR - PASS 2");
		*validationFlag = FALSE;
	}

	// Split the content by a new line delimeter
	while (fgets(currLine, LINE_LENGTH, filePointer)) {

		// Analyze the current Row from code
		analyzeCodeRowSecondPass(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, getTrimmedCodeRow(currLine), instructCounter, dataCounter, validationFlag);

	}
}
