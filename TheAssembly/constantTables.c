#include <stdlib.h>
#include <stdio.h>
#include<string.h>




// return the actionsByOpcode table
char* returnActionsByOpcodeTable() {

	return actionsOpcodes;
}

// return length of the action by Opcode table
int sizeOfActionsByOpcodeTable() {

	return (sizeof(actionsOpcodes) / sizeof(char*));
}



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
	"name:add,opcodebinary:0010,func:1010",
	"name:sub,opcodebinary:0010,func:1011",
	"name:lea,opcodebinary:0100",
	"name:clr,opcodebinary:0101,func:1010",
	"name:not,opcodebinary:0101,func:1011",
	"name:inc,opcodebinary:0101,func:1100",
	"name:dec,opcodebinary:0101,func:1101",
	"name:jmp,opcodebinary:1001,func:1010",
	"name:bne,opcodebinary:1001,func:1011",
	"name:jsr,opcodebinary:1001,func:1100",
	"name:red,opcodebinary:1100",
	"name:prn,opcodebinary:1101",
	"name:rts,opcodebinary:1110",
	"name:stop,opcodebinary:1111"
};

static char* actionsOpcodes[] =
{
	"name:mov,opcode:0",
	"name:cmp,opcode:1",
	"name:add,opcode:2",
	"name:sub,opcode:2,func:1011",
	"name:lea,opcode:4",
	"name:clr,opcode:5,func:1010",
	"name:not,opcode:5,func:1011",
	"name:inc,opcode:5,func:1100",
	"name:dec,opcode:5,func:1101",
	"name:jmp,opcode:9,func:1010",
	"name:bne,opcode:9,func:1011",
	"name:jsr,opcode:9,func:1100",
	"name:red,opcode:12",
	"name:prn,opcode:13",
	"name:rts,opcode:14",
	"name:stop,opcode:15"
};



static int *addressesMethods[] =
{
	"0:1",
	"1:2",
	"2:2",
	"3:0"
};
