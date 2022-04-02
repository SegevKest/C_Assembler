#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "wordInCode.h"
#include "symbol.h"
#include "validations.h"
#include "helperFunctions.h"

#define TRUE 1      
#define FALSE 0
#define LINE_LENGTH 81

void firstPassOnFile(machineCode** actionsMachineCodeHead, machineCode** dataMachineCodeHead, symbolList** symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter);

// The main function of the first pass - contains a loop on all the rows and handling each row
void firstPassOnFile(machineCode** actionsMachineCodeHead, machineCode** dataMachineCodeHead, symbolList** symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter ) {


	FILE* filePointer;

	filePointer= fopen(filePath, "r");

	char currLine[LINE_LENGTH];


	if (filePointer == NULL) {
		printf("File pointer received is an ERROR");
		*validationFlag = FALSE;
	}

	// Split the content by a new line delimeter
	while (fgets(currLine, LINE_LENGTH, filePointer)) {

		// Analyze the current Row from code
		analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, getTrimmedCodeRow(currLine),  instructCounter, dataCounter , validationFlag);
	
	}
}
