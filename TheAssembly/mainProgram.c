#include <stdlib.h>
#include <stdio.h>
#include<string.h>


#include "wordInCode.h"
#include "symbol.h"
#include "validations.h"
#include "helperFunctions.h"
#include "firstPass.h"
#include "preProcessor.h"


#define TRUE 1      
#define FALSE 0


int main(){
//int main(int argc, char* argv[]) {



	// Define the machine code for actions
	machineCode* actionsMachineCode = NULL;

	// Define the machine code for data
	machineCode* dataMachineCode = NULL;

	// Define the symbol Table
	symbolList* symbolTable = NULL;

	char* currentFileName;

	int dataCounter = 0;
	int actionCounter = 100;
	int validationFlag = TRUE; 	// Define the validation Flag to TRUE;

	//int* dataCounterAd = &dataCounter;
	//int* actionCounterAd = &actionCounter;

	//if (argc < 2) {
	//	printf("ERROR: got not enough arguments from user");
	//	return;
	//}

	firstPassOnFile(actionsMachineCode, dataMachineCode, symbolTable, "test.am", &validationFlag, &dataCounter, &actionCounter);


	// first pass

	//for (char** pToArgv = argv + 1; *pToArgv != argv[argc]; pToArgv++) {

	//	// Pre Processor - return the new file name to start pass
	//	currentFileName = handleSingleFile(*pToArgv);

	//	// First Pass - enter all elements
	//	firstPassOnFile(actionsMachineCode, dataMachineCode, symbolTable, currentFileName, &validationFlag, &dataCounter, &actionCounter);


	//	// check the validationFlag - if it is not valid - Finish this run
	//	if (validationFlag != FALSE)
	//	{
	//		// validation were valid - continue to second pass and output

	//		// Second Pass


	//		// Create output files

	//	}
	//	//else -  End this file and do not move to second pass and Output


	//	// reset all parameters for next iteration on next file
	//	dataCounter = 0;
	//	actionCounter = 100;
	//	validationFlag = TRUE;
 //	}


	
}