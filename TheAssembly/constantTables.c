#include <stdlib.h>
#include <stdio.h>
#include<string.h>





static char *savedNamesInProgram[] = 
	{
		// All Registers - from 0 -15
		"r0","r1","r2","r3","r4",
		"r5","r6","r7","r8","r9","r10",
		"r11","r12","r13","r14","r15",
		//The Actions - from 16 - 31
		"mov","cmp","add","sub","lea",
		"clr","not","inc","dec","jmp",
		"bne","jsr","red","prn","rts","stop",
		//The commands - from 32 - 35
		".data",".string",".entry",".extern"
	};

static char *actionsByBinary[] =
{
	"name:mov,opcodebinary:0000",
	"name:cmp,opcodebinary:0001",
	"name:add,opcodebinary:0010,funct:1010",
	"name:sub,opcodebinary:0010,funct:1011",
	"name:lea,opcodebinary:0100",
	"name:clr,opcodebinary:0101,funct:1010",
	"name:not,opcodebinary:0101,funct:1011",
	"name:inc,opcodebinary:0101,funct:1100",
	"name:dec,opcodebinary:0101,funct:1101",
	"name:jmp,opcodebinary:1001,funct:1010",
	"name:bne,opcodebinary:1001,funct:1011",
	"name:jsr,opcodebinary:1001,funct:1100",
	"name:red,opcodebinary:1100",
	"name:prn,opcodebinary:1101",
	"name:rts,opcodebinary:1110",
	"name:stop,opcodebinary:1111"
};

// name:NameOfAction,opcode:opcodeValue, funct:functOfAction
static char *actionsOpcodes[] =
{
	"name:mov,opcode:0",
	"name:cmp,opcode:1",
	"name:add,opcode:2,funct:1010",
	"name:sub,opcode:2,funct:1011",
	"name:lea,opcode:4",
	"name:clr,opcode:5,funct:1010",
	"name:not,opcode:5,funct:1011",
	"name:inc,opcode:5,funct:1100",
	"name:dec,opcode:5,funct:1101",
	"name:jmp,opcode:9,funct:1010",
	"name:bne,opcode:9,funct:1011",
	"name:jsr,opcode:9,funct:1100",
	"name:red,opcode:12",
	"name:prn,opcode:13",
	"name:rts,opcode:14",
	"name:stop,opcode:15"
};


// " NoOfMiun:NoOfNewWords, value:ValueOfMiun"
static char *addressesNewWordsAndValues[] =
{
	"0:1,value:00",
	"1:2,value:01",
	"2:2,value:10",
	"3:0,value:11"
};


//	nameOfRegister:noOfRegisterInBinary
static char *registersValues[] =
{
	"r0:0000",
	"r1:0001",
	"r2:0010",
	"r3:0011",
	"r4:0100",
	"r5:0101",
	"r6:0110",
	"r7:0111",
	"r8:1000",
	"r9:1001",
	"r10:1010",
	"r11:1011",
	"r12:1100",
	"r13:1101",
	"r14:1110",
	"r15:1111",
};




// return the actionsByOpcode table
char** returnActionsByOpcodeTable() {

	return actionsOpcodes;
}

// return the registersValues table
char* returnRegistersValues() {

	return registersValues;
}

// return the addressesNewWordsAndValues table
char* returnAddressesNewWordsAndValuesTable() {

	return addressesNewWordsAndValues;
}

// return the actionsByOpcode table
char* returnSavedNamesTable() {

	return savedNamesInProgram;
}

// return length of the action by Opcode table
int sizeOfActionsByOpcodeTable() {

	return (sizeof(actionsOpcodes) / sizeof(char*));
}
