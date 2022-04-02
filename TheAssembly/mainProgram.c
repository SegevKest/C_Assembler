#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "wordInCode.h"
#include "symbol.h"
#include "validations.h"
#include "helperFunctions.h"
#include "firstPass.h"
#include "secondPass.h"
#include "preProcessor.h"


#define TRUE 1      
#define FALSE 0



int main(int argc, char* argv[]) {

	char* currentFileName;

	// Define the machine code for actions
	machineCode* actionsMachineCode = NULL;

	// Define the machine code for data
	machineCode* dataMachineCode = NULL;

	// Define the symbol Table
	symbolList* symbolTable = NULL;

	int dataCounter = 0;
	int actionCounter = 99;	// All the machine code will be inserted from 100 
	int validationFlag = TRUE; 	// Define the validation Flag to TRUE;



	// Validation on number of arguments received from the cmd
	if (argc < 2) {
		printf("ERROR: got not enough arguments from user");
		return;
	}


	for (char** pToArgv = argv + 1; *pToArgv != argv[argc]; pToArgv++) {

		// Pre Processor - return the new file name to start pass
		currentFileName = handleSingleFile(*pToArgv);

		// first pass
		firstPassOnFile(&actionsMachineCode, &dataMachineCode, &symbolTable, currentFileName, &validationFlag, &dataCounter, &actionCounter);

		// check the validationFlag - if it is not valid - Finish this run
		if (validationFlag != FALSE)
		{
			//Print All the Machine code - 
			{
				printf("\n\nActions Machine Code: \n");
				printList(actionsMachineCode);
				printf("\n\nData Machine Code: \n");
				printList(dataMachineCode);
				printf("\n\nSymbols List: \n");
				printSymList(symbolTable);
			}

			// Second Pass
			scndPassOnFile(&actionsMachineCode, &dataMachineCode, &symbolTable, currentFileName, &validationFlag, &dataCounter, &actionCounter);

			//Print All the Machine code - 
			{
				printf("\n\nActions Machine Code: \n");
				printList(actionsMachineCode);
				printf("\n\nData Machine Code: \n");
				printList(dataMachineCode);
				printf("\n\nSymbols List: \n");
				printSymList(symbolTable);
			}

		}
		if (validationFlag != FALSE)
		{

			//Create the output files - MISSING!
		}

		// reset all parameters for next iteration on next file
		actionsMachineCode = NULL;
		dataMachineCode = NULL;
		symbolTable = NULL;

		dataCounter = 0;
		actionCounter = 99;
		validationFlag = TRUE;
	}
}