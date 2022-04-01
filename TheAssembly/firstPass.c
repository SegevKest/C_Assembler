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



void firstPassOnFile(machineCode** actionsMachineCodeHead, machineCode** dataMachineCodeHead, symbolList** symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter ) {


	FILE* filePointer;

	filePointer= fopen(filePath, "r");

	char currLine[LINE_LENGTH];


	if (filePointer == NULL) {
		printf("File pointer received is an ERROR");
		*validationFlag = FALSE;
	}


	//while (fgets(currLine, LINE_LENGTH, filePointer)) {

	//	printf("%s", currLine);

	//	//printf("\nDone with this row!\n");

	//}

	while (fgets(currLine, LINE_LENGTH, filePointer)) {

		//printf("%s", currLine);

		analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, getTrimmedCodeRow(currLine),  instructCounter, dataCounter , validationFlag);
		//printf("\n\nAt first pass outer - actionsCounter: %d\n\n", *instructCounter);
	
		printf("\nDone with this row!\n");

	}


}

//int main() {
//
//	initil
//	int ic = 100 , dc = 0, i;
//	
//	machineCode* actionsMachineCodeHead = NULL; // the linked list for the instructions machine code
//	machineCode* dataMachineCodeHead = NULL;	// the linked list for the data lines 
//
//	symbolList* symbolHead = NULL;
//
//	//Anaylize File
//	//Read file
//	//read each row - and send all parameters of the row to the relevant function ()  
//	
//	analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, "lea STR, r6", ic, dc);
//
//	//analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, " .string \"abcd\" ", ic, 100);
//
//	//analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, ".extern 100,-9,-8,199,12, 144	", ic, 100);
//
//	//analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, "	.data  6,-9,-100,31", ic, 100);
//	
//	
//	// Symbol Validations
//	/*insertNewSymbolData(symbolHead, "Segev", ic, "entry");
//	displaySymbol(symbolHead);*/
//
//	// Machine code validations
//	//insertNewOpCodeWord(actionsMachineCodeHead, subString(line, 0,4));
//	//displayWord(machineCodeHead);
//	return 0;
//}

