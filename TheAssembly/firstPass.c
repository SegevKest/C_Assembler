#include <stdlib.h>
#include <stdio.h>
#include<string.h>



#include "wordInCode.h"
#include "symbol.h"
#include "validations.h"
#include "helperFunctions.h"






int main() {


	//initil
	int ic = 100 , dc = 0;
	
	machineCode* actionsMachineCodeHead = NULL; // the linked list for the instructions machine code
	machineCode* dataMachineCodeHead = NULL;	// the linked list for the data lines 

	symbolList* symbolHead = NULL;

	//Anaylize File
	//Read file
	//read each row - and send all parameters of the row to the relevant function ()  




	// Get a new Line from the assembly code
	char line[7] = "inc r6";

	char* att[] = {
		".code", ".data"
		};

	//printf("%d\n", isActionLine("	.string	"));

	//printf("%s\n",line);
	
	//printf("\n%d",isValidRegister("r"));
	// 
	//analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, "SEGEV      : .data7,-57		, +17,,	", ic, 100);

	analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, ".data 100,-9,-8,199,12,, 144	", ic, 100);

	//analyzeCodeRow(symbolHead, actionsMachineCodeHead, dataMachineCodeHead, "			 .string 	", ic, 100);
	
	
	// Symbol Validations
	/*insertNewSymbolData(symbolHead, "Segev", ic, "entry");
	displaySymbol(symbolHead);*/

	// Machine code validations
	//insertNewOpCodeWord(machineCodeHead, subString(line, 0,4));
	//displayWord(machineCodeHead);




	//analyze row - split all arguments - and trim them

	// then - check for valid syntax and preform all validation on valid row


	return 0;
}

