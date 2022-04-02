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


void scndPassOnFile(machineCode** actionsMachineCodeHead, machineCode** dataMachineCodeHead, symbolList** symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter) {

	FILE* filePointer;

	filePointer = fopen(filePath, "r");

	char currLine[LINE_LENGTH];


	while (fgets(currLine, LINE_LENGTH, filePointer)) {

		//printf("%s", currLine);

		analyzeCodeRowSecondPass(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, getTrimmedCodeRow(currLine), instructCounter, dataCounter, validationFlag);

		printf("\nDone with this row!\n");

	}
}
