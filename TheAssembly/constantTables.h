#pragma once
#ifndef __CONSTANTTABLES_H
#define __CONSTANTTABLES_H

#define REGISTERS_NO 16


char** returnActionsByOpcodeTable();		// Method to return the actionsByOpCode table pointer
char** returnSavedNamesTable();		// Method to return the savedNames table pointer
char** returnRegistersValues();		// Method to return the Register values table pointer

int sizeOfActionsByOpcodeTable();		// method that will return the size of the actionsByOpcode Table


#endif //__SYMBOL_H