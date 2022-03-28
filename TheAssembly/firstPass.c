#include <stdlib.h>
#include <stdio.h>
#include<string.h>



#include "wordInCode.h"
#include "symbol.h"
#include "validations.h"
#include "helperFunctions.h"






//int main() {
//
//	//initil
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

