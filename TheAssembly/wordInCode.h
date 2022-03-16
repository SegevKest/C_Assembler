#pragma once
#ifndef __WORDINCODE_H
#define __WORDINCODE_H


typedef struct wordInCode machineCode;

void insertNewOpCodeWord(machineCode* machCodeTable);
void insertNewFullCodeWord(machineCode* machCodeTable);

#endif //__WORDINCODE_H