#pragma once
#ifndef __FIRSTPASS_H
#define __FIRSTPASS_H


#include "wordInCode.h"
#include "symbol.h"


// This function will handle the first pass algo' on the file
void firstPassOnFile(machineCode** actionsMachineCodeHead, machineCode* dataMachineCodeHead, symbolList* symbolHead, char* filePath, int* validationFlag, int* dataCounter, int* instructCounter);


#endif //____FIRSTPASS_H