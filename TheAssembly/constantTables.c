#include <stdlib.h>
#include <stdio.h>
#include<string.h>



#define REGISTERS_NO 16

char** returnActionsByOpcodeTable();
char** returnRegistersValues();

// Saved names in program Table
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

//all the action - with their binary values of opcode and funct
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

// the table contains all actions with thier integer opcode values + their binary funct
// name:NameOfAction,opcode:opcodeValue, funct:functOfAction
static char *actionsOpcodes[] =
{
	"mov,opcode:0",
	"cmp,opcode:1",
	"add,opcode:2,funct:1010",
	"sub,opcode:2,funct:1011",
	"lea,opcode:4",
	"clr,opcode:5,funct:1010",
	"not,opcode:5,funct:1011",
	"inc,opcode:5,funct:1100",
	"dec,opcode:5,funct:1101",
	"jmp,opcode:9,funct:1010",
	"bne,opcode:9,funct:1011",
	"jsr,opcode:9,funct:1100",
	"red,opcode:12",
	"prn,opcode:13",
	"rts,opcode:14",
	"stop,opcode:15"
};

// contains all the possible miuns
// " NoOfMiun:NoOfNewWords, value:ValueOfMiun"
static char *addressesNewWordsAndValues[] =
{
	"0:1,value:00",
	"1:2,value:01",
	"2:2,value:10",
	"3:0,value:11"
};

// this table contains all the register + binary values
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
char** returnRegistersValues() {

	return registersValues;
}

// return the addressesNewWordsAndValues table
char* returnAddressesNewWordsAndValuesTable() {

	return addressesNewWordsAndValues;
}

// return the actionsByOpcode table
char** returnSavedNamesTable() {

	return savedNamesInProgram;
}

// return length of the action by Opcode table
int sizeOfActionsByOpcodeTable() {

	return (sizeof(actionsOpcodes) / sizeof(char*));
}
