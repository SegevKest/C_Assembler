#pragma once
#ifndef __SECONDPASS_H
#define __SECONDPASS_H


#include "wordInCode.h"
#include "symbol.h"


// This function will handle the second pass algo' on the file
void scndPassOnFile(machineCode** actionsMachineCodeHead, machineCode** dataMachineCodeHead, symbolList** symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter);


#endif //__SECONDPASS_H