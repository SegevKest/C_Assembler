#pragma once
#ifndef __MACRONODE_H
#define __MACRONODE_H


typedef struct macroNode macroTable;


void insertNewMacroName(macroTable** head, char* macroName);
void insertNewMacroContent(macroTable** head, char* macroName, char* macroRow);
macroTable* returnMacro(macroTable** head, char* macroName);
char* getContentOfMacro(macroTable** head, char* macroName);
void displayMacroTable(const macroTable* head);



#endif //__MACRONODE_H


